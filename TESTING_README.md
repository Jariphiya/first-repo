# Customer Service Management System - Testing

## Files Structure

- `main.c` - Main program entry point with menu system
- `project.c` - Core business logic and data operations  
- `project.h` - Header file with function declarations and structures
- `unit_test.c` - Unit tests for individual functions
- `e2e.c` - End-to-end tests for complete workflows
- `services.csv` - Main data file

## Menu Options

1. **Display All Services** - Show all service records
2. **Add Service** - Add a new service record
3. **Search Service** - Search by ID or customer name
4. **Delete Service** - Remove a service record
5. **Update Service** - Modify an existing service record
6. **Run Unit Tests** - Execute unit tests for core functions
7. **Run E2E Tests** - Execute end-to-end workflow tests
8. **Run All Tests** - Execute both unit and E2E tests
9. **Exit** - Close the program

## Unit Tests (`unit_test.c`)

Tests individual functions in isolation:

- **TestAddService()** - Tests service addition, ID generation, and data persistence
- **TestUpdateService()** - Tests service record updates and data integrity
- **TestDeleteService()** - Tests record deletion and array management
- **RunUnitTests()** - Runs all unit tests and cleans up test files

## E2E Tests (`e2e.c`)

Tests complete application workflows:

- **TestE2E()** - Comprehensive end-to-end testing including:
  - Adding multiple services
  - Loading and verifying data
  - Search functionality (by ID and name)
  - Update operations
  - Delete operations
  - ID generation logic
  - Display functionality
  - Edge cases (comma handling, boundary conditions)
- **RunAllTests()** - Runs both unit tests and E2E tests

## Compilation

```bash
gcc main.c project.c unit_test.c e2e.c -o program
```

## Running Tests

The tests use separate CSV files to avoid interfering with your main data:
- Unit tests: `test_services.csv`, `test_update.csv`, `test_delete.csv`
- E2E tests: `e2e_test_services.csv`

All test files are automatically cleaned up after test execution.

## Test Features

- **Isolated Testing** - Tests don't affect main data
- **Comprehensive Coverage** - Tests all major functions
- **Clear Pass/Fail Indicators** - ✓ for passed tests, ✗ for failed tests
- **Automatic Cleanup** - Test files are removed after execution
- **Edge Case Testing** - Tests boundary conditions and special scenarios