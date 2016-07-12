#ifndef HSCORE_FILESYS_H
#define HSCORE_FILESYS_H

#include <string>
#include <vector>
#include <map>
#include <hscore/pattern/singleton.h>
#include <hscore/files/instream.h>

#pragma once
namespace hscore
{
	class FileSys : public Singleton<FileSys>
	{
	public:
		bool fileExists(const std::string& path) const;
		bool pathExists(const std::string& path) const;

		void listFilesAndDirs(const std::string& path, std::vector<std::string>* files, std::vector<std::string>* dirs) const;

		std::vector<std::string> listFiles(const std::string& path) const;
		std::vector<std::string> listFilesRecursive(const std::string& path) const;

		std::vector<std::string> listDirectories(const std::string& path) const;

		std::vector<std::string> getFilesWithSuffix(const std::string& dir, const std::string& fileSuffix) const;
		std::vector<std::string> getFilesWithSuffixRecursive(const std::string& dir, const std::string& fileSuffix) const;

		void registerFolder(const std::string& key, const std::string& path);

		std::shared_ptr<InStream> getInFileStream(const std::string& path);

	private:
		std::vector<std::string> extractWithSuffix(const std::vector<std::string>& files, const std::string& fileSuffix) const;
		SETUP_SINGLETON(FileSys);
		FileSys();
		~FileSys();
		std::map<std::string, std::vector<std::string>> m_folders;

	};

}

#endif