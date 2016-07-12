#pragma once

#include <vector>
#include <hscore/pattern/singleton.h>
#include <hscore/files/filesys.h>

namespace hscore
{

class WorkingDir : public hscore::Singleton<WorkingDir>
{
public:
	inline std::string getFilePath(std::string path) const;
	inline void addDataDir(const std::string& path);
	inline const std::vector<std::string>& getWorkingDirs();

private:
	SETUP_SINGLETON(WorkingDir);
	WorkingDir() {};
	~WorkingDir() {};
	std::vector<std::string> m_workingDirs;
};

std::string WorkingDir::getFilePath(std::string path) const
{
	std::string fullPath;
	if (hscore::FileSys::instance().fileExists(path))
	{
		return path;
	}
	else
	{
		for (const std::string& workingDirPath : m_workingDirs)
		{
			auto files = hscore::FileSys::instance().listFilesRecursive(workingDirPath);
			
			for (std::string& fullpath : files)
			{
				if (fullpath.find(path) != std::string::npos)
				{
					return fullpath;
				}
			}
		}
	}
	return "";
}

void WorkingDir::addDataDir(const std::string& path)
{
	m_workingDirs.push_back(path);
}

const std::vector<std::string>& WorkingDir::getWorkingDirs()
{
	return m_workingDirs;
}

}
