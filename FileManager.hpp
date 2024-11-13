#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <iostream>
#include <vector>

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