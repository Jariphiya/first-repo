# Customer Service Management System

A comprehensive C-based customer service management system with integrated testing capabilities.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [File Structure](#file-structure)
- [Prerequisites](#prerequisites)
- [Installation & Setup](#installation--setup)
- [How to Compile](#how-to-compile)
- [How to Run](#how-to-run)
- [Menu Options](#menu-options)
- [Testing](#testing)
- [Data File Format](#data-file-format)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)

## 📖 Overview

This system manages customer service records with full CRUD (Create, Read, Update, Delete) operations. It includes comprehensive testing capabilities with both unit tests and end-to-end tests to ensure reliability and functionality.

## ✨ Features

- **Service Management**: Add, view, update, delete service records
- **Search Functionality**: Search by Service ID or Customer Name (case-insensitive)
- **Automatic ID Generation**: Sequential service ID assignment
- **Data Persistence**: CSV file storage with comma protection
- **Comprehensive Testing**: Unit tests and E2E tests with isolated test environments
- **User-Friendly Interface**: Clear menu-driven console interface
- **Data Validation**: Input validation and error handling
- **Cross-Platform**: Works on Windows, Linux, and macOS

## 📁 File Structure

```
first-repo/
├── main.c              # Main program entry point
├── project.c           # Core business logic and functions
├── project.h           # Header file with declarations
├── unit_test.c         # Unit tests for individual functions
├── e2e.c               # End-to-end integration tests
├── services.csv        # Main data storage file
├── README.md           # This file
├── TESTING_README.md   # Detailed testing documentation
└── test_menu.bat       # Windows batch script for testing
```

## 🔧 Prerequisites

- **GCC Compiler**: MinGW on Windows, or native GCC on Linux/macOS
- **Operating System**: Windows 10+, Linux, or macOS
- **Terminal/Command Prompt**: For compilation and execution

### Windows Setup
```bash
# Install MinGW or use Dev-C++/Code::Blocks
# Or install via Chocolatey
choco install mingw
```

### Linux/macOS Setup
```bash
# Ubuntu/Debian
sudo apt update && sudo apt install gcc

# macOS (requires Xcode Command Line Tools)
xcode-select --install
```


## 🔨 How to Compile

### Main Application
```bash
# Standard compilation
gcc main.c project.c unit_test.c e2e.c -o program

# With debugging symbols
gcc -g main.c project.c unit_test.c e2e.c -o program

# With warnings enabled (recommended)
gcc -Wall -Wextra main.c project.c unit_test.c e2e.c -o program
```

### Windows-specific
```cmd
gcc main.c project.c unit_test.c e2e.c -o program.exe
```

### Alternative compilation (separate object files)
```bash
gcc -c main.c project.c unit_test.c e2e.c
gcc main.o project.o unit_test.o e2e.o -o program
```

## ▶️ How to Run

### Standard Execution
```bash
# Linux/macOS
./program

# Windows
program.exe
# or
.\program.exe
```

### Quick Test Run
```bash
# Run and exit immediately (for testing compilation)
echo 9 | ./program
```

## 📱 Menu Options

When you run the program, you'll see this menu:

```
===== Customer Service Management =====
1. Display All Services
2. Add Service  
3. Search Service
4. Delete Service
5. Update Service
6. Run Unit Tests
7. Run E2E Tests
8. Run All Tests
9. Exit
=======================================
```

### Option Details:

1. **Display All Services** - Shows all service records in a formatted table
2. **Add Service** - Creates a new service record with auto-generated ID
3. **Search Service** - Search by Service ID or Customer Name
4. **Delete Service** - Remove a service record by ID
5. **Update Service** - Modify existing service details
6. **Run Unit Tests** - Execute individual function tests
7. **Run E2E Tests** - Run complete workflow tests
8. **Run All Tests** - Execute both unit and E2E tests
9. **Exit** - Close the program safely

## 🧪 Testing

### Testing Options

The system includes comprehensive testing capabilities:

#### Unit Tests (`unit_test.c`)
- **TestAddService()** - Tests service creation and ID generation
- **TestUpdateService()** - Tests service modification
- **TestDeleteService()** - Tests service removal
- Individual function testing in isolation

#### End-to-End Tests (`e2e.c`) 
- **TestE2E()** - Complete workflow testing
- Tests entire application flow from start to finish
- Includes edge cases and error conditions

#### Running Tests

**From Menu (Recommended)**:
1. Compile the program normally
2. Run `./program`
3. Select option 6, 7, or 8

**Direct Test Execution**:
```bash
# Quick test run
echo 6 | ./program  # Unit tests
echo 7 | ./program  # E2E tests  
echo 8 | ./program  # All tests
```

**Windows Batch Script**:
```cmd
test_menu.bat
```

### Test Files Created During Testing
- `test_services.csv` - Unit test data (auto-cleaned)
- `test_update.csv` - Update test data (auto-cleaned) 
- `test_delete.csv` - Delete test data (auto-cleaned)
- `e2e_test_services.csv` - E2E test data (auto-cleaned)

## 💾 Data File Format

The system uses CSV format for data storage:

### services.csv Structure
```csv
ServiceID,CustomerName,ServiceDetails,ServiceDate
S001,John Doe,Computer repair,2025-10-09
S002,Jane Smith,Software installation,2025-10-10
```

### Field Specifications:
- **ServiceID**: Format S001, S002, etc. (auto-generated)
- **CustomerName**: Up to 49 characters
- **ServiceDetails**: Up to 99 characters  
- **ServiceDate**: YYYY-MM-DD format recommended

### Comma Protection
The system automatically handles commas in data by converting them to semicolons during storage and restoring them during display.

## 🔧 Troubleshooting

### Compilation Issues

**Error: `gcc: command not found`**
```bash
# Install GCC compiler first
# Windows: Install MinGW or Dev-C++
# Linux: sudo apt install gcc
# macOS: xcode-select --install
```

**Error: Multiple definition errors**
```bash
# Make sure you're not including .c files in headers
# Compile with: gcc main.c project.c unit_test.c e2e.c -o program
```

### Runtime Issues

**Error: `No existing file found`**
- This is normal on first run
- The program will create `services.csv` automatically

**Error: File permission denied**
- Ensure write permissions in the directory
- On Linux/macOS: `chmod 755 .`

**Error: Tests failing**
- Ensure no other instances are running
- Check if CSV files are locked by other programs
- Try running as administrator (Windows)

### Performance Issues

**Slow loading with many records**
- The system loads all records into memory
- For large datasets (>1000 records), consider database alternatives

## 📊 Usage Examples

### Adding a Service
1. Run program: `./program`
2. Choose option 2
3. Enter customer details when prompted
4. Service ID is auto-generated

### Searching for Services
1. Choose option 3
2. Enter Service ID (e.g., "S001") or Customer Name
3. Results display immediately

### Running Tests
1. Choose option 8 (Run All Tests)
2. Watch comprehensive test execution
3. All tests should show ✓ (pass) indicators

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Make your changes
4. Run all tests: Choose menu option 8
5. Commit changes: `git commit -am 'Add feature'`
6. Push to branch: `git push origin feature-name`
7. Submit a Pull Request

### Code Standards
- Use consistent indentation (4 spaces)
- Add comments for complex logic
- Follow existing naming conventions
- Ensure all tests pass before submitting

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 📞 Support

If you encounter issues:
1. Check the [Troubleshooting](#troubleshooting) section
2. Review [TESTING_README.md](TESTING_README.md) for testing details
3. Create an issue on GitHub with:
   - Your operating system
   - GCC version (`gcc --version`)
   - Error messages
   - Steps to reproduce

---

**Version**: 2.0  
**Last Updated**: October 9, 2025  
**Author**: Jariphiya 
