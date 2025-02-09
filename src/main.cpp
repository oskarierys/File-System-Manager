/*
 * Copyright (c) 2024 Oskar Kierys
 */

#include <iostream>
#include "FileManager.hpp"
#include "DirectoryManager.hpp"
#include <cctype>
#include <string>
#include <chrono>
#include <thread>
#include <filesystem>
#include <ranges>
#include <numeric>

/**
 * @brief Lists the files and directories in the specified directory path.
 * 
 * This function iterates through the contents of the given directory path
 * and prints the names of files and directories. It uses the C++17 filesystem
 * library and C++20 ranges to filter and display the entries.
 * 
 * @param directoryPath The path of the directory to list the contents of.
 */
void listFilesInDirectory(const std::string& directoryPath)
{
    namespace fs = std::filesystem;

    try 
    {
        auto entries = fs::directory_iterator(directoryPath);

        if (entries == fs::directory_iterator()) 
        {
            std::cerr << "No files or directories in library!" << std::endl;
            return;
        }

        std::cout << "Content of the current directory:" << std::endl;

        for (const auto& entry : entries | std::views::filter([](const fs::directory_entry& e) {
                return e.is_regular_file() || e.is_directory();
            })) 
        {
            const auto& fullPath = entry.path();
            std::uintmax_t size = 0;

            if (entry.is_directory()) 
            {
                size = std::accumulate(
                    fs::directory_iterator(fullPath), fs::directory_iterator(),
                    0ULL,
                    [](std::uintmax_t total, const fs::directory_entry& e) {
                        return total + (e.is_regular_file() ? fs::file_size(e) : 0);
                    });
                std::cout << "[DIR] " << fullPath.filename().string() << " | " << size << " bytes" << std::endl;
            } 
            else if (entry.is_regular_file() && fullPath.extension() == ".txt") 
            {
                size = fs::file_size(fullPath);
                std::cout << "[TXT] " << fullPath.filename().string() << " | " << size << " bytes" << std::endl;
            }
        }
    } 
    catch (const fs::filesystem_error& e) 
    {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}

std::uintmax_t DirectoryManager::calculateSize(const std::string& directoryPath)
{
    std::uintmax_t size = 0;

    try
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath))
        {
            if (entry.is_regular_file())
            {
                size += entry.file_size();
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Error calculating size: " << e.what() << std::endl;
    }
    
    return size;
}

int main()
{
    DirectoryManager directoryManager(std::filesystem::current_path().string());
    char userInput;
    std::string directoryPath = directoryManager.getCurrentDirectory();
    std::string filePath;
    std::string userPath;
    
    while(true)
    {
        std::cout << "         MENU of file library\n========================================\n";
        std::cout << "Choose an option!\n"
                  << "a - DISPLAY CURRENT DIRECTORY\n"
                  << "c - CHANGE DIRECTORY\n"
                  << "n - CREATE NEW FILE IN LIBRARY\n"
                  << "l - LIST ALL FILES IN LIBRARY\n"
                  << "t - DISPLAY TREE\n"
                  << "r - READ FILE FROM LIBRARY\n"
                  << "m - MODIFY EXISTING FILE\n"
                  << "d - DELETE .txt FILE\n"
                  << "q - QUIT LIBRARY\n";
        
        std::cout << "Enter your choice: ";
        std::cin >> userInput;
        userInput = tolower(userInput);

        if (userInput == 'n')
        {
            std::cout << "Enter name of the new file (with .txt extension!!!): ";
            std::cin >> filePath;
            File file(directoryPath + "/" + filePath);

            if (file.createFile())
            {
                std::cout << "File created!" << std::endl;
            }
        }
        else if (userInput == 'a')
        {
            std::cout << "Current directory: " << directoryManager.getCurrentDirectory() << std::endl;
        }
        else if (userInput == 'c')
        {
            std::cout << "Enter new directory path: ";
            std::cin >> userPath;
            directoryManager.changeDirectory(userPath);
            directoryPath = directoryManager.getCurrentDirectory();
        }
        else if (userInput == 'l')
        {
            listFilesInDirectory(directoryPath);
        }
        else if (userInput == 't')
        {
            directoryManager.displayTree(directoryPath);
        }
        else if (userInput == 'r')
        {
            std::cout << "Enter name of file you want to read (with .txt extension!!!): ";
            std::cin >> filePath;
            std::cout << std::endl;
        
            File file(directoryPath + "/" + filePath);

            std::string content = file.readFile();
            if (!content.empty())
            {
                std::cout << "Content of file: " << filePath << " is: " << std::endl;
                std::cout << content << std::endl;
            }
            else
            {
                std::cerr << "File is empty!" << std::endl;
            }
        }
        else if (userInput == 'm')
        {
            std::cout << "Enter name of file you want to modify (with .txt extension!!!): ";
            std::cin >> filePath;

            File file(directoryPath + "/" + filePath);

            std::string existingContent = file.readFile();
            if (!existingContent.empty())
            {
                std::cout << "Enter the text you want to append to the file: ";
                std::cin.ignore();
                std::string newContent;
                std::getline(std::cin, newContent);

                if (file.writeFile(newContent))
                {
                    std::cout << "Text successfully appended to " << filePath << "!" << std::endl;
                }
                else
                {
                    std::cerr << "Failed to write to file!" << std::endl;
                }
            }
            else
            {
                std::cerr << "File not found or empty! Try again!" << std::endl;
            }
        }
        else if (userInput == 'd')
        {
            std::cout << "Enter name of file to delete (with .txt extension!!!): ";
            std::cin >> filePath;

            if (filePath.size() >= 4 && filePath.substr(filePath.size() - 4) != ".txt")
            {
                std::cerr << "Error: Only .txt files can be deleted!" << std::endl;
                continue;
            }

            File file(directoryPath + "/" + filePath);
            if (file.deleteFile())
            {
                std::cout << "File deleted!" << std::endl;
            }
            else
            {
                std::cerr << "Failed to delete file!" << std::endl;
            }
        }
        else if (userInput == 'q')
        {
            std::cout << "Exiting library!";
            break;
        }
        else
        {
            std::cerr << "Invalid user input! Please try again after 5 seconds!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::cout << std::endl;
        }
    }

    return 0;
}
