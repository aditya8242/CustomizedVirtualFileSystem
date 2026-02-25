# CustomizedVirtualFileSystem

CustomizedVirtualFileSystem (CVFS) is a virtual file system implementation designed to demonstrate how file systems work internally in operating systems.

The project emulates core file system data structures and system calls in a controlled, in-memory environment to provide a clear understanding of file subsystem architecture.

## Project Objective

The primary goal of this project is to:

* Understand internal file system architecture.
* Study how operating systems manage files using inodes and file descriptors.
* Implement core file operations from scratch.
* Gain hands-on experience with system-level programming concepts.

This project provides a simplified overview of the UNIX File System (UFS) model.

## Architecture Overview

The system recreates essential file subsystem data structures, including:

* Super Block
* Inode Table
* Disk Inode List Block
* File Table
* User File Descriptor Table (UFDT)
* UAREA
* Data Blocks
* Boot Block

All data structures are implemented manually and stored in primary memory (RAM). No actual disk operations are performed.

## Implemented File Operations

The project provides custom implementations of common file system commands and system calls:

* `creat`
* `open`
* `unlink`
* `read`
* `write`
* `ls`
* `stat`

Each operation uses internally managed data structures inspired by UNIX file system algorithms.

## Key Features

* Fully virtual (RAM-based) file system
* Custom inode and file table implementation
* File descriptor management
* Read/Write permission handling
* File offset management (Lseek support)
* Limited inode count and file size (simulated constraints)
* Command-line interface
* Structured error handling

## Technology Stack

* Language: C++
* Compiler: g++
* Platform: Linux (CLI-based)

## Build Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/aditya8242/CustomizedVirtualFileSystem.git
cd CustomizedVirtualFileSystem
```

### 2. Compile the Project

```bash
g++ cvfs.cpp main.cpp -o Main
```

### 3. Run the Application

```bash
./Main
```

## Design Constraints

* The file system operates entirely in RAM.
* Data is not persistent (lost after program termination).
* Limited number of inodes.
* Limited file size.
* No directory hierarchy (flat structure).
* Single-user simulation.
* CLI-only interface.

## Learning Outcomes

By completing this project, one can understand:

* How inodes store file metadata.
* How file descriptor tables are managed.
* How read/write offsets work.
* How permissions are validated.
* How memory allocation is handled in file systems.
* The internal flow of file operations in UNIX-like systems.

## Limitations

* No persistent storage support.
* No directory structure.
* No multi-user environment.
* No advanced security model.
* Not intended for production use.

## Future Improvements

* Add directory hierarchy support.
* Implement persistent disk storage.
* Introduce multi-user access control.
* Enhance security model.
* Provide GUI-based interface.
* Add concurrent file operation support.

## License

This project is licensed under GNU GENERAL PUBLIC LICENSE Version 3.

This project is intended for academic and educational purposes.