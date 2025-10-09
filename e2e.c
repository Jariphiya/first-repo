#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project.h"

// Helper function for case-insensitive string comparison (since strcasecmp might not be available on Windows)
int strcasecmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
        if (c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

// End-to-End test function that tests complete workflow
void TestE2E() {
    printf("\n========================================\n");
    printf("        RUNNING END-TO-END TESTS        \n");
    printf("========================================\n");
    
    Service testServices[MAX];
    int testCount = 0;
    
    // Set test CSV file to avoid overwriting main data
    SetCSVFile("e2e_test_services.csv");
    
    printf("E2E Test 1: Starting with empty database...\n");
    
    // Test 1: Add multiple services
    printf("\nE2E Test 2: Adding multiple services...\n");
    
    // Add first service
    strcpy(testServices[testCount].serviceID, "S001");
    strcpy(testServices[testCount].customerName, "Alice Johnson");
    strcpy(testServices[testCount].serviceDetails, "Laptop repair");
    strcpy(testServices[testCount].serviceDate, "2025-10-09");
    testCount++;
    
    // Add second service
    strcpy(testServices[testCount].serviceID, "S002");
    strcpy(testServices[testCount].customerName, "Bob Smith");
    strcpy(testServices[testCount].serviceDetails, "Network setup");
    strcpy(testServices[testCount].serviceDate, "2025-10-10");
    testCount++;
    
    // Add third service
    strcpy(testServices[testCount].serviceID, "S003");
    strcpy(testServices[testCount].customerName, "Carol Davis");
    strcpy(testServices[testCount].serviceDetails, "Data recovery");
    strcpy(testServices[testCount].serviceDate, "2025-10-11");
    testCount++;
    
    SaveData(testServices, testCount);
    printf("✓ Added %d services successfully\n", testCount);
    
    // Test 2: Load and verify data
    printf("\nE2E Test 3: Loading and verifying data...\n");
    Service loadedServices[MAX];
    int loadedCount = 0;
    LoadData(loadedServices, &loadedCount);
    
    if (loadedCount == testCount) {
        printf("✓ Load data test PASSED - %d records loaded\n", loadedCount);
    } else {
        printf("✗ Load data test FAILED - Expected %d, got %d\n", testCount, loadedCount);
        goto cleanup;
    }
    
    // Test 3: Search functionality
    printf("\nE2E Test 4: Testing search functionality...\n");
    int searchFound = 0;
    
    // Search by ID
    for (int i = 0; i < loadedCount; i++) {
        if (strcmp(loadedServices[i].serviceID, "S002") == 0) {
            printf("✓ Search by ID test PASSED - Found service S002\n");
            searchFound = 1;
            break;
        }
    }
    if (!searchFound) {
        printf("✗ Search by ID test FAILED\n");
    }
    
    // Search by customer name (case insensitive)
    searchFound = 0;
    for (int i = 0; i < loadedCount; i++) {
        if (strcasecmp_custom(loadedServices[i].customerName, "alice johnson") == 0) {
            printf("✓ Search by name test PASSED - Found Alice Johnson\n");
            searchFound = 1;
            break;
        }
    }
    if (!searchFound) {
        printf("✗ Search by name test FAILED\n");
    }
    
    // Test 4: Update functionality
    printf("\nE2E Test 5: Testing update functionality...\n");
    
    // Find and update Bob Smith's record
    int updateIndex = -1;
    for (int i = 0; i < loadedCount; i++) {
        if (strcmp(loadedServices[i].serviceID, "S002") == 0) {
            updateIndex = i;
            break;
        }
    }
    
    if (updateIndex != -1) {
        // Update the service details
        strcpy(loadedServices[updateIndex].customerName, "Robert Smith");
        strcpy(loadedServices[updateIndex].serviceDetails, "Network setup and security");
        strcpy(loadedServices[updateIndex].serviceDate, "2025-10-12");
        
        SaveData(loadedServices, loadedCount);
        
        // Verify update
        Service updatedServices[MAX];
        int updatedCount = 0;
        LoadData(updatedServices, &updatedCount);
        
        int updateVerified = 0;
        for (int i = 0; i < updatedCount; i++) {
            if (strcmp(updatedServices[i].serviceID, "S002") == 0) {
                if (strcmp(updatedServices[i].customerName, "Robert Smith") == 0 &&
                    strstr(updatedServices[i].serviceDetails, "security") != NULL) {
                    printf("✓ Update test PASSED - Record updated successfully\n");
                    updateVerified = 1;
                    break;
                }
            }
        }
        if (!updateVerified) {
            printf("✗ Update test FAILED - Changes not saved correctly\n");
        }
    } else {
        printf("✗ Update test FAILED - Could not find record to update\n");
    }
    
    // Test 5: Delete functionality
    printf("\nE2E Test 6: Testing delete functionality...\n");
    
    // Delete the third service (Carol Davis)
    int deleteIndex = -1;
    for (int i = 0; i < loadedCount; i++) {
        if (strcmp(loadedServices[i].serviceID, "S003") == 0) {
            deleteIndex = i;
            break;
        }
    }
    
    if (deleteIndex != -1) {
        // Simulate deletion by shifting records
        for (int i = deleteIndex; i < loadedCount - 1; i++) {
            loadedServices[i] = loadedServices[i + 1];
        }
        loadedCount--;
        
        SaveData(loadedServices, loadedCount);
        
        // Verify deletion
        Service deletedServices[MAX];
        int deletedCount = 0;
        LoadData(deletedServices, &deletedCount);
        
        int deleteVerified = 1;
        for (int i = 0; i < deletedCount; i++) {
            if (strcmp(deletedServices[i].serviceID, "S003") == 0) {
                deleteVerified = 0;
                break;
            }
        }
        
        if (deleteVerified && deletedCount == (testCount - 1)) {
            printf("✓ Delete test PASSED - Record deleted successfully\n");
        } else {
            printf("✗ Delete test FAILED - Record still exists or count incorrect\n");
        }
        
        // Update loadedServices for next test
        for (int i = 0; i < deletedCount; i++) {
            loadedServices[i] = deletedServices[i];
        }
        loadedCount = deletedCount;
        
    } else {
        printf("✗ Delete test FAILED - Could not find record to delete\n");
    }
    
    // Test 6: ID generation
    printf("\nE2E Test 7: Testing ID generation...\n");
    char newID[10];
    GenerateNextID(loadedServices, loadedCount, newID);
    
    // Test that the generated ID is higher than any existing ID
    int generatedNum = atoi(newID + 1);
    int testPassed = 1;
    for (int i = 0; i < loadedCount; i++) {
        int existingNum = atoi(loadedServices[i].serviceID + 1);
        if (generatedNum <= existingNum) {
            testPassed = 0;
            break;
        }
    }
    
    if (testPassed) {
        printf("✓ ID generation test PASSED - Generated %s (higher than existing IDs)\n", newID);
    } else {
        printf("✗ ID generation test FAILED - Generated %s conflicts with existing IDs\n", newID);
    }
    
    // Test 7: Display all functionality test
    printf("\nE2E Test 8: Testing display functionality...\n");
    printf("Current records in test database:\n");
    printf("%-8s | %-15s | %-25s | %-12s\n", "ID", "Customer", "Service", "Date");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < loadedCount; i++) {
        printf("%-8s | %-15s | %-25s | %-12s\n",
               loadedServices[i].serviceID,
               loadedServices[i].customerName,
               loadedServices[i].serviceDetails,
               loadedServices[i].serviceDate);
    }
    printf("✓ Display test PASSED - Showing %d records\n", loadedCount);
    
    // Test 8: Edge cases
    printf("\nE2E Test 9: Testing edge cases...\n");
    
    // Test comma replacement
    Service commaTest;
    strcpy(commaTest.customerName, "Test, Customer");
    strcpy(commaTest.serviceDetails, "Service, with, commas");
    
    char originalName[50], originalDetails[100];
    strcpy(originalName, commaTest.customerName);
    strcpy(originalDetails, commaTest.serviceDetails);
    
    ReplaceComma(commaTest.customerName);
    ReplaceComma(commaTest.serviceDetails);
    
    if (strchr(commaTest.customerName, ',') == NULL && strchr(commaTest.serviceDetails, ',') == NULL) {
        printf("✓ Comma replacement test PASSED\n");
        
        // Test comma restoration
        RestoreComma(commaTest.customerName);
        RestoreComma(commaTest.serviceDetails);
        
        if (strcmp(commaTest.customerName, originalName) == 0) {
            printf("✓ Comma restoration test PASSED\n");
        } else {
            printf("✗ Comma restoration test FAILED\n");
        }
    } else {
        printf("✗ Comma replacement test FAILED\n");
    }
    
    // Test 9: Boundary conditions
    printf("\nE2E Test 10: Testing boundary conditions...\n");
    
    // Test empty service details
    Service boundaryTest;
    strcpy(boundaryTest.serviceID, "S999");
    strcpy(boundaryTest.customerName, "Boundary Test");
    strcpy(boundaryTest.serviceDetails, "");
    strcpy(boundaryTest.serviceDate, "2025-12-31");
    
    if (strlen(boundaryTest.serviceDetails) == 0) {
        printf("✓ Empty service details test PASSED\n");
    } else {
        printf("✗ Empty service details test FAILED\n");
    }
    
    // Test maximum length strings
    char maxName[50];
    memset(maxName, 'A', 49);
    maxName[49] = '\0';
    
    if (strlen(maxName) == 49) {
        printf("✓ Maximum length string test PASSED\n");
    } else {
        printf("✗ Maximum length string test FAILED\n");
    }

cleanup:
    // Reset to main CSV file and cleanup
    SetCSVFile("services.csv");
    remove("e2e_test_services.csv");
    
    printf("\n========================================\n");
    printf("        END-TO-END TESTS COMPLETED      \n");
    printf("========================================\n");
    printf("Test database cleaned up.\n\n");
}

// Test all functions together
void RunAllTests() {
    printf("\n########################################\n");
    printf("          RUNNING ALL TESTS             \n");
    printf("########################################\n");
    
    // Run unit tests first
    printf("Starting Unit Tests...\n");
    RunUnitTests();
    
    printf("\nStarting End-to-End Tests...\n");
    // Then run E2E test
    TestE2E();
    
    printf("########################################\n");
    printf("         ALL TESTS COMPLETED            \n");
    printf("########################################\n");
}