cmake_minimum_required(VERSION 3.10)

project(FileLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
    src/file.cpp
    src/directory.cpp
)

set(HEADERS
    src/FileManager.hpp
    src/DirectoryManager.hpp
    src/PathUtils.hpp
)

add_executable(FileLibrary ${SOURCES} ${HEADERS})

if (UNIX AND NOT APPLE)
    target_link_libraries(FileLibrary stdc++fs)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)