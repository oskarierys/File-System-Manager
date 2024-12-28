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
            files.push_back(entry.path().filename().string());                    
        }     
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Error!" << e.what() << std::endl;
    }
    return files;
}

bool DirectoryManager::fileExists(const std::string& fileName) const
{
    return std::filesystem::exists(m_currentDirectory + "/" + fileName);
}

void DirectoryManager::displayTree(const std::string& directoryPath, int indent)
{
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
        {
            for (int i = 0; i < indent; i++)
            {
                std::cout << " ";
            }
            std::cout << "|-- " << entry.path().filename().string() << std::endl;

            if (entry.is_directory())
            {
                displayTree(entry.path().string(), indent + 1);
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// file_iterator, kazde wywolanie listtuje pojedyncze