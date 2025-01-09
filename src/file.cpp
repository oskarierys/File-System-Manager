/*
 * Copyright (c) 2024 Oskar Kierys, Kacper Śliwa
 */

#include "FileManager.hpp"
#include "DirectoryManager.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/**
 * @brief Constructs a File object with the specified path.
 * 
 * @param path The path of the file.
 */

File::File(const std::string& path) : m_filePath(path) {};

/**
 * @brief Creates the file at the specified path.
 * 
 * @return true if the file was created successfully, false otherwise.
 */

bool File::createFile()
{
    std::ofstream file(m_filePath);
    if (file)
    {
        file.close();
        std::cout << "File created successfully: " << m_filePath << std::endl;
        openInEditor();
        return true;
    }
    else
    {
        std::cerr << "Error! Failed to create file: " << m_filePath << std::endl;
        return false;
    }
}

/**
 * @brief Writes content to the file.
 * 
 * @param content The content to write to the file.
 * @return true if the content was written successfully, false otherwise.
 */

bool File::writeFile(const std::string& content)
{
    std::ofstream file(m_filePath, std::ios::app);
    if (file)
    {
        file << content << std::endl;
        file.close();
        std::cout << "Text written to file: " << m_filePath << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Error! Failed to write to file: " << m_filePath << std::endl;
        return false;
    }
}

/**
 * @brief Reads the content of the file.
 * 
 * @return The content of the file as a string.
 */

std::string File::readFile()
{
    std::ifstream file(m_filePath);
    std::string content;
    std::string line;

    if (file)
    {
        while (std::getline(file, line))
        {
            content += line + "\n";
        }
        file.close();
        std::cout << "Content read from file: " << m_filePath << std::endl;
    }
    else
    {
        std::cerr << "Failed to read file: " << m_filePath << std::endl;
    }
    return content;
}

/**
 * @brief Deletes the file.
 * 
 * @return true if the file was deleted successfully, false otherwise.
 */

bool File::deleteFile()
{
    char confirmation;
    std::cout << "Are you sure you want to delete this file? [y/n]: ";
    std::cin >> confirmation;

    confirmation = tolower(confirmation);

    if (confirmation == 'y')
    {
        if (std::filesystem::remove(m_filePath))
        {
            std::cout << "File deleted succesfully! " << m_filePath << std::endl;
            return true; 
        }
        else 
        {
            std::cerr << "Failed to delete file! " << m_filePath << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Canceled!" << std::endl;
        return false;
    }
}

/**
 * @brief Opens the file in the default editor.
 */

void File::openInEditor() 
{
#ifdef _WIN32
    ShellExecute(0, 0, m_filePath.c_str(), 0, 0, SW_SHOW);
#endif
}
