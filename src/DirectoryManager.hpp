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
    static void displayTree(const std::string& directoryPath, int indent = 0);
    static std::uintmax_t calculateSize(const std::string& directoryPath);
};

#endif