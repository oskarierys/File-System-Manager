# File Management Library

This project is a console application designed for managing directories and `.txt` files. It provides functionalities such as browsing directories, displaying directory trees, creating, modifying, reading, and deleting files.

## Features

### Directory Management
- **Change Directory**: Navigate between directories.
- **List Files**: Display files and directories in the current path.
- **Display Directory Tree**: Show directory structures with indentation.
- **Calculate Directory Size**: Compute the total size of files in a directory.

### File Management
- **Create File**: Create new `.txt` files and open them in the default editor (Windows only).
- **Read File**: Read the content of a `.txt` file.
- **Write File**: Append content to a `.txt` file.
- **Delete File**: Delete a `.txt` file after user confirmation.
- **Open in Editor**: Open a `.txt` file in the default editor (Windows only).

## Project Structure
- **`DirectoryManager.hpp/cpp`**: Handles directory-related operations.
- **`FileManager.hpp/cpp`**: Handles file-related operations.
- **`main.cpp`**: Entry point of the application and implements the user interface.

## User Interface
The application features a console-based menu with the following options:

- **a**: Display the current directory.
- **c**: Change the current directory.
- **n**: Create a new `.txt` file.
- **l**: List files in the current directory.
- **t**: Display the directory tree.
- **r**: Read the content of a `.txt` file.
- **m**: Append content to a `.txt` file.
- **d**: Delete a `.txt` file.
- **q**: Exit the application.

## Sample Usage

1. **Creating a File**:
   - Select option `n`.
   - Enter the file name with the `.txt` extension.
   - The file will open in the default editor (Windows only).

2. **Displaying a Directory Tree**:
   - Select option `t` to view the directory structure with indentations.

3. **Reading a File**:
   - Select option `r` and provide the file name to read its contents.

## Supported Platforms
- File opening in the default editor (`openInEditor` method) is available only on Windows. On other systems, this functionality is ignored.

## Compilation and Execution

### Requirements
- A compiler supporting **C++20** standard.

### Compilation Command
```bash
g++ -std=c++20 main.cpp file.cpp directory.cpp -o fileman
```

### Execution Command
```bash
./fileman
```

### Author
- Oskar Kierys
