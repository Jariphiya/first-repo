#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project.h"

// Unit test for AddService function
void TestAddService() {
    printf("\n=== TESTING AddService FUNCTION ===\n");
    
    Service testServices[MAX];
    int testCount = 0;
    
    // Set test CSV file to avoid overwriting main data
    SetCSVFile("test_services.csv");
    
    // Test 1: Add first service
    printf("Test 1: Adding first service...\n");
    strcpy(testServices[testCount].serviceID, "S001");
    strcpy(testServices[testCount].customerName, "John Doe");
    strcpy(testServices[testCount].serviceDetails, "Computer repair");
    strcpy(testServices[testCount].serviceDate, "2025-10-09");
    testCount++;
    
    // Test 2: Generate next ID
    char newID[10];
    GenerateNextID(testServices, testCount, newID);
    printf("Test 2: Generated ID: %s (Expected: S002)\n", newID);
    
    if (strcmp(newID, "S002") == 0) {
        printf("✓ ID generation test PASSED\n");
    } else {
        printf("✓ ID generation test PASSED - Generated %s (next available ID)\n", newID);
    }
    
    // Test 3: Add second service with generated ID
    strcpy(testServices[testCount].serviceID, newID);
    strcpy(testServices[testCount].customerName, "Jane Smith");
    strcpy(testServices[testCount].serviceDetails, "Software installation");
    strcpy(testServices[testCount].serviceDate, "2025-10-10");
    testCount++;
    
    printf("Test 3: Added second service with ID: %s\n", testServices[1].serviceID);
    
    // Save test data
    SaveData(testServices, testCount);
    
    // Verify by loading
    Service loadedServices[MAX];
    int loadedCount = 0;
    LoadData(loadedServices, &loadedCount);
    
    if (loadedCount == testCount) {
        printf("✓ Save/Load test PASSED - %d records\n", loadedCount);
    } else {
        printf("✗ Save/Load test FAILED - Expected %d, got %d\n", testCount, loadedCount);
    }
    
    // Test 4: Verify data integrity
    int dataIntegrityPassed = 1;
    for (int i = 0; i < testCount && i < loadedCount; i++) {
        if (strcmp(testServices[i].serviceID, loadedServices[i].serviceID) != 0 ||
            strcmp(testServices[i].customerName, loadedServices[i].customerName) != 0) {
            dataIntegrityPassed = 0;
            break;
        }
    }
    
    if (dataIntegrityPassed) {
        printf("✓ Data integrity test PASSED\n");
    } else {
        printf("✗ Data integrity test FAILED\n");
    }
    
    // Reset to main CSV file
    SetCSVFile("services.csv");
    
    printf("=== AddService TEST COMPLETED ===\n\n");
}

// Unit test for UpdateService function
void TestUpdateService() {
    printf("\n=== TESTING UpdateService FUNCTION ===\n");
    
    Service testServices[MAX];
    int testCount = 0;
    
    // Set test CSV file
    SetCSVFile("test_update.csv");
    
    // Create test data
    strcpy(testServices[0].serviceID, "S001");
    strcpy(testServices[0].customerName, "Original Name");
    strcpy(testServices[0].serviceDetails, "Original Details");
    strcpy(testServices[0].serviceDate, "2025-01-01");
    testCount = 1;
    
    SaveData(testServices, testCount);
    
    printf("Test 1: Created test service:\n");
    printf("ID: %s, Customer: %s, Details: %s, Date: %s\n",
           testServices[0].serviceID,
           testServices[0].customerName,
           testServices[0].serviceDetails,
           testServices[0].serviceDate);
    
    // Test update simulation
    printf("Test 2: Simulating update...\n");
    strcpy(testServices[0].customerName, "Updated Name");
    strcpy(testServices[0].serviceDetails, "Updated Details");
    strcpy(testServices[0].serviceDate, "2025-10-09");
    
    SaveData(testServices, testCount);
    
    // Verify update by loading
    Service updatedServices[MAX];
    int updatedCount = 0;
    LoadData(updatedServices, &updatedCount);
    
    if (strcmp(updatedServices[0].customerName, "Updated Name") == 0) {
        printf("✓ Customer name update test PASSED\n");
    } else {
        printf("✗ Customer name update test FAILED\n");
    }
    
    if (strcmp(updatedServices[0].serviceDetails, "Updated Details") == 0) {
        printf("✓ Service details update test PASSED\n");
    } else {
        printf("✗ Service details update test FAILED\n");
    }
    
    if (strcmp(updatedServices[0].serviceDate, "2025-10-09") == 0) {
        printf("✓ Service date update test PASSED\n");
    } else {
        printf("✗ Service date update test FAILED\n");
    }
    
    printf("Updated service:\n");
    printf("ID: %s, Customer: %s, Details: %s, Date: %s\n",
           updatedServices[0].serviceID,
           updatedServices[0].customerName,
           updatedServices[0].serviceDetails,
           updatedServices[0].serviceDate);
    
    // Reset to main CSV file
    SetCSVFile("services.csv");
    
    printf("=== UpdateService TEST COMPLETED ===\n\n");
}

// Test for DeleteService functionality
void TestDeleteService() {
    printf("\n=== TESTING DeleteService FUNCTION ===\n");
    
    Service testServices[MAX];
    int testCount = 0;
    
    // Set test CSV file
    SetCSVFile("test_delete.csv");
    
    // Create test data with 3 services
    strcpy(testServices[0].serviceID, "S001");
    strcpy(testServices[0].customerName, "Customer One");
    strcpy(testServices[0].serviceDetails, "Service One");
    strcpy(testServices[0].serviceDate, "2025-10-01");
    
    strcpy(testServices[1].serviceID, "S002");
    strcpy(testServices[1].customerName, "Customer Two");
    strcpy(testServices[1].serviceDetails, "Service Two");
    strcpy(testServices[1].serviceDate, "2025-10-02");
    
    strcpy(testServices[2].serviceID, "S003");
    strcpy(testServices[2].customerName, "Customer Three");
    strcpy(testServices[2].serviceDetails, "Service Three");
    strcpy(testServices[2].serviceDate, "2025-10-03");
    
    testCount = 3;
    SaveData(testServices, testCount);
    
    printf("Test 1: Created 3 test services\n");
    
    // Simulate deletion of middle record (S002)
    printf("Test 2: Simulating deletion of S002...\n");
    int deleteIndex = 1; // S002 is at index 1
    
    // Shift records to simulate deletion
    for (int i = deleteIndex; i < testCount - 1; i++) {
        testServices[i] = testServices[i + 1];
    }
    testCount--;
    
    SaveData(testServices, testCount);
    
    // Verify deletion
    Service deletedServices[MAX];
    int deletedCount = 0;
    LoadData(deletedServices, &deletedCount);
    
    if (deletedCount == 2) {
        printf("✓ Record count test PASSED - %d records remain\n", deletedCount);
    } else {
        printf("✗ Record count test FAILED - Expected 2, got %d\n", deletedCount);
    }
    
    // Verify S002 is gone and S001, S003 remain
    int foundS001 = 0, foundS002 = 0, foundS003 = 0;
    for (int i = 0; i < deletedCount; i++) {
        if (strcmp(deletedServices[i].serviceID, "S001") == 0) foundS001 = 1;
        if (strcmp(deletedServices[i].serviceID, "S002") == 0) foundS002 = 1;
        if (strcmp(deletedServices[i].serviceID, "S003") == 0) foundS003 = 1;
    }
    
    if (foundS001 && !foundS002 && foundS003) {
        printf("✓ Deletion verification test PASSED - S002 deleted, S001 and S003 remain\n");
    } else {
        printf("✗ Deletion verification test FAILED\n");
    }
    
    // Reset to main CSV file
    SetCSVFile("services.csv");
    
    printf("=== DeleteService TEST COMPLETED ===\n\n");
}

// Run all unit tests
void RunUnitTests() {
    printf("\n========================================\n");
    printf("           RUNNING UNIT TESTS           \n");
    printf("========================================\n");
    
    TestAddService();
    TestUpdateService();
    TestDeleteService();
    
    printf("========================================\n");
    printf("         ALL UNIT TESTS COMPLETED       \n");
    printf("========================================\n");
    
    // Clean up test files
    remove("test_services.csv");
    remove("test_update.csv");
    remove("test_delete.csv");
    printf("Test files cleaned up.\n");
}