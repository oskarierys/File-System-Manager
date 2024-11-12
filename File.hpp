#ifndef FILE_HPP
#define FILE_HPP

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
    static std::vector<std::string> listFilesInDirectory(const std::string& directoryPath);

    void openInEditor();
};

#endif