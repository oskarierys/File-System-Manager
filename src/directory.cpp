/*
 * Copyright (c) 2024 Oskar Kierys, Kacper Śliwa
 */

#include "DirectoryManager.hpp"
#include <filesystem>
#include <iostream>

/**
 * @brief Constructs a DirectoryManager object with the specified directory path.
 * 
 * @param directoryPath The initial directory path.
 */

DirectoryManager::DirectoryManager(const std::string& directoryPath) : m_currentDirectory(directoryPath) {}

/**
 * @brief Changes the current directory to the specified path.
 * 
 * @param newDirectoryPath The new directory path.
 */

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

/**
 * @brief Gets the current directory path.
 * 
 * @return The current directory path as a string.
 */

std::string DirectoryManager::getCurrentDirectory() const
{
    return m_currentDirectory;
}

/**
 * @brief Lists the files in the specified directory.
 * 
 * @param directoryPath The path of the directory to list the files of.
 * @return A vector of file names in the directory.
 */

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

/**
 * @brief Displays the directory tree starting from the specified path.
 * 
 * @param directoryPath The path of the directory to display the tree of.
 * @param indent The indentation level for displaying the tree. Defaults to 0.
 */

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

// file_iterator, kazde wywolanie listuje pojedyncze