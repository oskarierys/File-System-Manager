#include "DirectoryManager.hpp"
#include <filesystem>
#include <iostream>

DirectoryManager::DirectoryManager(const std::string& directoryPath) : m_currentDirectory(directoryPath) {}

void DirectoryManager::changeDirectory(const std::string& newDirectoryPath)
{
    if (std::filesystem::exists(newDirectoryPath) && std::filesystem::is_directory(newDirectoryPath)) 
    {
        m_currentDirectory = newDirectoryPath;
        std::cout << "Directory changed to: " << m_currentDirectory << std::endl;
    } 
    else 
    {
        std::cerr << "Invalid directory path!" << std::endl;
    }
}

std::string DirectoryManager::getCurrentDirectory() const
{
    return m_currentDirectory;
}

std::vector<std::string> DirectoryManager::listFilesInDirectory(const std::string& directoryPath)
{
    std::vector<std::string> files;

    try 
    {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
        {
            if (entry.is_regular_file())
            {
                files.push_back(entry.path().filename().string());                    
            }
        }     
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Error!" << e.what() << std::endl;
    }
    return files;
}