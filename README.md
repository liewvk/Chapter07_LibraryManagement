# Chapter 07 - Library Management System

A C++ library management system demonstrating core programming concepts including object-oriented design, data structures, and file handling.

## Overview

This project implements a complete library management system with features for managing books, patrons, and lending operations. It serves as an educational resource for understanding software design patterns and practical C++ development.

## Features

- **Book Management**: Add, update, and remove books from the library catalog
- **Patron Management**: Register and manage library patrons
- **Lending System**: Track book checkouts and returns
- **Search Functionality**: Query books by title, author, or ISBN
- **Reporting**: Generate library statistics and reports

## Project Structure

```
Chapter07_LibraryManagement/
├── CMakeLists.txt          # CMake build configuration
├── src/                    # Source files
│   ├── main.cpp           # Main program entry point
│   ├── library.cpp        # Library core implementation
│   ├── book.cpp           # Book class implementation
│   └── patron.cpp         # Patron class implementation
├── include/               # Header files
│   ├── library.h          # Library interface
│   ├── book.h             # Book class definition
│   └── patron.h           # Patron class definition
└── README.md             # This file
```

## Requirements

- **C++**: C++11 or later
- **CMake**: Version 3.10 or higher
- **Build Tools**: GCC, Clang, or MSVC

## Building the Project

### Using CMake

```bash
# Create a build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build the project
cmake --build .

# Run the executable
./LibraryManagement
```

### Alternative: Direct Compilation

```bash
# Compile with g++
g++ -std=c++11 -o library_management src/*.cpp -I./include
```

## Usage

Run the compiled executable to start the library management system:

```bash
./LibraryManagement
```

The program provides an interactive menu for:
- Adding and removing books
- Registering patrons
- Processing checkouts and returns
- Viewing library statistics

## Implementation Details

### Core Classes

- **Book**: Represents a single book with properties (title, author, ISBN, availability)
- **Patron**: Represents a library member with borrowing history
- **Library**: Main system managing the collection and patron interactions

### Key Algorithms

- Search operations use efficient lookup mechanisms
- Lending tracking maintains integrity with audit logs
- Reporting generates summaries from transaction history

## Educational Value

This project demonstrates:
- Object-oriented programming principles
- Class design and inheritance hierarchies
- Container usage (vectors, maps)
- File I/O operations
- Error handling and validation
- Basic algorithm design

## Future Enhancements

- Database integration for persistent storage
- GUI interface using Qt or similar framework
- Reservation system for unavailable books
- Fine calculation for overdue books
- Advanced search with filters

## License

This project is part of an educational curriculum and is provided as-is for learning purposes.

## Author

**liewvk**

---

Last Updated: July 6, 2026
