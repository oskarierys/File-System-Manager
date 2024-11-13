#ifndef DIRECTORY_MANAGER_HPP
#define DIRECTORY_MANAGER_HPP

#include <vector>
#include <string>

class DirectoryManager
{
private:
    std::string m_currentDirectory;

public:
    DirectoryManager(const std::string& directoryPath = ".");

    void changeDirectory(const std::string& newDirectoryPath);
    bool fileExists(const std::string& fileName) const;

    std::string getCurrentDirectory() const;
        static std::vector<std::string> listFilesInDirectory(const std::string& directoryPath);
};

#endif