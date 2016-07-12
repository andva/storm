#include "filesys.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <hscore/log.h>
#include <hscore/assert.h>

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <shlwapi.h>
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "shlwapi.lib")
#endif

namespace
{
	const std::string WinSeparator = "\\";
	const std::string UnixSeparator = "/";
#ifdef WIN32
	const std::string Separator = WinSeparator;
#else
	const std::string Separator = UnixSeparator;
#endif
}

hscore::FileSys::FileSys()
{

}

hscore::FileSys::~FileSys()
{

}

bool hscore::FileSys::fileExists(const std::string& path) const
{
#ifdef WIN32
	return GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES;
#endif
	return false;
}

bool hscore::FileSys::pathExists(const std::string& path) const
{
#ifdef WIN32
	return GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES;
#endif
	return false;
}

void hscore::FileSys::listFilesAndDirs(const std::string& path, std::vector<std::string>* files, std::vector<std::string>* dirs) const
{
#ifdef WIN32
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;
	StringCchCopy(szDir, MAX_PATH, path.c_str());
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		LOG_ERROR(LOG_CORE, "Could not find any files");
		return;
	}

	// List all the files in the directory with some info about them.
	FindNextFile(hFind, &ffd);
	FindNextFile(hFind, &ffd);
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string fullPath = path + "/" + std::string(ffd.cFileName);
			dirs->push_back(fullPath);
		}
		else
		{
			std::string fullPath = path + "/" + std::string(ffd.cFileName);
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			files->push_back(fullPath);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		LOG_ERROR(LOG_CORE, "still files!");
	}

	FindClose(hFind);
#endif
}

std::vector<std::string> hscore::FileSys::listFiles(const std::string& path) const
{
	std::vector<std::string> files;
	std::vector<std::string> dirs;
	listFilesAndDirs(path, &files, &dirs);
	return files;
}

std::vector<std::string> hscore::FileSys::listFilesRecursive(const std::string& path) const
{
	std::vector<std::string> allFiles;
	std::vector<std::string> dirs;
	std::vector<std::string> currFolderFiles;
	listFilesAndDirs(path, &currFolderFiles, &dirs);

	allFiles.insert(allFiles.end(), currFolderFiles.begin(), currFolderFiles.end());
	for (const std::string& d : dirs)
	{
		std::vector<std::string> folderFiles = listFilesRecursive(d);
		allFiles.insert(allFiles.end(), folderFiles.begin(), folderFiles.end());
	}
	return allFiles;
}

std::vector<std::string> hscore::FileSys::listDirectories(const std::string& path) const
{
	std::vector<std::string> files;
	std::vector<std::string> dirs;
	listFilesAndDirs(path, &files, &dirs);
	return files;
}

std::vector<std::string> hscore::FileSys::getFilesWithSuffix(const std::string& dir, const std::string& fileSuffix) const
{
	std::vector<std::string> allFiles = listFiles(dir);
	return extractWithSuffix(allFiles, fileSuffix);
}

std::vector<std::string> hscore::FileSys::getFilesWithSuffixRecursive(const std::string& dir, const std::string& fileSuffix) const
{
	std::vector<std::string> allFiles = listFilesRecursive(dir);
	return extractWithSuffix(allFiles, fileSuffix);

}

void hscore::FileSys::registerFolder(const std::string& key, const std::string& path)
{
	m_folders[key].push_back(path);
}

std::shared_ptr<hscore::InStream> hscore::FileSys::getInFileStream(const std::string& path)
{
	return std::make_shared<InStream>(path);
}

std::vector<std::string> hscore::FileSys::extractWithSuffix(const std::vector<std::string>& files, const std::string& fileSuffix) const
{

	std::vector<std::string> extrFiles;
	for (const std::string& s : files)
	{
		std::string ext;
#ifdef WIN32
		ext = PathFindExtensionA(s.c_str());
#else
		if (s.find_last_of(".") != std::string::npos)
		{
			ext = s.substr(s.find_last_of(".") + 1);
		}
#endif
		if (ext.compare(fileSuffix) == 0)
		{
			extrFiles.push_back(s);
		}

		
	}
	return extrFiles;
}

