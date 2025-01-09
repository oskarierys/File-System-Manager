/*
 * Copyright (c) 2024 Oskar Kierys, Kacper Śliwa
 */

#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <iostream>
#include <vector>

/**
 * @brief Represents a file and provides operations to manipulate it.
 */
class File
{
private:
    std::string m_filePath;

public:
    File(const std::string& path);

    bool createFile();
    bool writeFile(const std::string& content);
    bool deleteFile();

    std::string readFile();

    void openInEditor();
};

#endif