# PIPEX
## Table of Contents
- [About](#about)
- [Usage](#usage)
- [Compilation](#compilation)
- [Key Concepts Learned](#key-concepts-learned)
- [Skills Developed](#skills-developed)
- [Technical Implementation](#technical-implementation)
- [42 School Standards](#42-school-standards)

## About
This repository contains my implementation of the **pipex** project at 42 School.  
Pipex is a foundational Unix project that recreates the behavior of shell pipes in C programming.  
The program mimics the Unix pipe operator `|`, allowing the output of one command to become the input of another, while handling file redirection and process management.

**Program Behavior:**
```bash
# Your program should behave exactly like this shell command:
< file1 cmd1 | cmd2 > file2

# Which is equivalent to:
./pipex file1 cmd1 cmd2 file2
```


## Usage
The program takes 4 arguments and executes commands with input/output redirection:

```bash
# Basic usage
./pipex infile "ls -l" "wc -l" outfile

# This is equivalent to the shell command:
< infile ls -l | wc -l > outfile

# Examples
./pipex input.txt "grep hello" "wc -w" output.txt
./pipex /etc/passwd "cat" "head -5" result.txt
```

**Arguments:**
- `file1`: Input file to read from
- `cmd1`: First command to execute
- `cmd2`: Second command to execute  
- `file2`: Output file to write to


## Compilation
The project follows standard 42 compilation practices:

```bash
# Compile with Makefile
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re
```

**Compilation flags:** `-Wall -Wextra -Werror`


## Key Concepts Learned

### Unix System Programming
- **Pipes and IPC**: Creating and managing inter-process communication channels
- **Process Management**: Using `fork()` to create child processes
- **File Descriptors**: Manipulating stdin, stdout, and file descriptors with `dup2()`
- **Process Execution**: Using `execve()` to replace process images with new programs

### System Calls Mastery
- **pipe()**: Creating unidirectional data channels between processes
- **fork()**: Creating child processes for parallel execution
- **dup2()**: Redirecting file descriptors for input/output management
- **execve()**: Executing shell commands from within C programs
- **waitpid()**: Synchronizing parent and child process execution

### Error Handling & Edge Cases
- **File Permissions**: Handling read/write permissions for input/output files
- **Command Validation**: Checking if commands exist and are executable
- **Path Resolution**: Finding executables in system PATH
- **Memory Management**: Proper allocation and deallocation of resources
- **Signal Handling**: Managing process termination and cleanup


## Skills Developed

- **System-level Programming**: Deep understanding of Unix process model
- **Inter-process Communication**: Implementing pipes for data flow between processes  
- **File I/O Management**: Handling file operations and descriptor manipulation
- **Process Synchronization**: Coordinating parent and child process execution
- **Command Line Parsing**: Processing and validating user input arguments
- **Error Handling**: Robust error checking and graceful failure management
- **Memory Safety**: Preventing leaks and ensuring proper resource cleanup
- **Shell Command Integration**: Executing system commands programmatically


## Technical Implementation

### Core Components

**Process Flow:**
1. **Input Validation**: Check arguments and file accessibility
2. **Pipe Creation**: Establish communication channel between processes
3. **Process Forking**: Create child processes for command execution
4. **File Descriptor Management**: Redirect input/output streams
5. **Command Execution**: Execute commands with proper environment
6. **Process Synchronization**: Wait for child processes to complete

**Key Functions Implemented:**
- File opening and validation
- Path resolution for executables  
- Command parsing and argument preparation
- Pipe setup and file descriptor redirection
- Process creation and execution management
- Error handling and cleanup procedures

**System Calls Used:**
- `pipe()` - Create communication pipe
- `fork()` - Create child processes
- `dup2()` - Duplicate and redirect file descriptors
- `execve()` - Execute commands
- `waitpid()` - Wait for process completion
- `open()`, `close()` - File operations

### Architecture
The program creates two child processes:
- **First child**: Reads from input file, executes cmd1, writes to pipe
- **Second child**: Reads from pipe, executes cmd2, writes to output file
- **Parent process**: Manages coordination and waits for completion


## 42 School Standards

### Norm Requirements
- ✅ Maximum 25 lines per function
- ✅ Maximum 5 functions per file  
- ✅ Proper indentation and formatting
- ✅ No forbidden functions usage
- ✅ Compilation without warnings

### Coding Standards
- ✅ Comprehensive error handling for all system calls
- ✅ No memory leaks (checked with valgrind)
- ✅ Proper resource cleanup (file descriptors, processes)
- ✅ Signal-safe programming practices
- ✅ Defensive programming against edge cases

### Authorized Functions
- `open`, `close`, `read`, `write`
- `malloc`, `free`
- `pipe`, `dup2`, `execve`, `fork`
- `waitpid`, `access`
- `exit`, `perror`, `strerror`
- Custom libft functions


## Contact
- **GitHub**: [@TuroTheReal](https://github.com/TuroTheReal)
- **Email**: arthurbernard.dev@gmail.com
- **LinkedIn**: [Arthur Bernard](https://www.linkedin.com/in/arthurbernard92/)

---
<p align="center">
  <img src="https://img.shields.io/badge/Made%20with-C-blue.svg"/>
  <img src="https://img.shields.io/badge/Unix-System%20Programming-orange.svg"/>
</p>
