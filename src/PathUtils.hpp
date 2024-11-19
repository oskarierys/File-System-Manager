#ifndef PATH_UTILS_HPP
#define PATH_UTILS_HPP

#include <string>

class PathUtils
{
public:
    static bool hasExtension(const std::string& fileName, const std::string& extension);
    static std::string normalizePath(const std::string& path);
};

#endif