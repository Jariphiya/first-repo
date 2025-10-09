#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "project.h"  

// ==================== COLOR DEFINITIONS ====================
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

char *test_filename = "test_services.csv"; //the file name is wrong btw I have no fuckin idea why it works

// ==================== ASSERTION HELPERS ====================
int test_failures = 0;

void assert_equal_int(int expected, int actual, const char *message)
{
    if (expected == actual)
        printf(GREEN "✅ PASS: %s (Expected: %d, Got: %d)\n" RESET, message, expected, actual);
    else
    {
        printf(RED "❌ FAIL: %s (Expected: %d, Got: %d)\n" RESET, message, expected, actual);
        test_failures++;
    }
}

void assert_equal_string(const char *expected, const char *actual, const char *message)
{
    if (strcmp(expected, actual) == 0)
        printf(GREEN "✅ PASS: %s (\"%s\")\n" RESET, message, actual);
    else
    {
        printf(RED "❌ FAIL: %s\n" RESET, message);
        printf(YELLOW "   Expected: \"%s\"\n   Got:      \"%s\"\n" RESET, expected, actual);
        test_failures++;
    }
}

int file_exists(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f)
    {
        fclose(f);
        return 1;
    }
    return 0;
}

int count_csv_lines(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return 0;
    int lines = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f))
        lines++;
    fclose(f);
    return lines;
}

// ==================== END-TO-END TEST CASE ====================

void test_complete_service_management_workflow()
{
    SetCSVFile(test_filename);

    printf(BLUE "\n=== END-TO-END TEST CASE 1: Complete Service Management Workflow ===" RESET "\n");
    printf("📋 Scenario: Add Service → Save CSV → Reload CSV → Verify Data\n\n");

    printf("🔹 ARRANGE: Setting up test environment\n");
    const char *test_filename = "test_services.csv";
    Service services[MAX];
    int count = 0;

    remove(test_filename); // clean previous test

    struct
    {
        const char *customerName;
        const char *serviceDetails;
        const char *serviceDate;
    } test_services[] = {
        {"John Doe", "Air conditioner cleaning", "2025-10-09"},
        {"Jane Smith", "Refrigerator repair", "2025-10-10"},
        {"Alice Brown", "Washing machine maintenance", "2025-10-11"}};

    int expected_count = 3;
    printf("   - Test file: %s\n", test_filename);
    printf("   - Number of services: %d\n", expected_count);

    // ==================== ACT ====================
    printf("\n🔹 ACT: Performing End-to-End Workflow\n");

    // Step 1: Add services
    printf("   Step 1: Adding services to memory\n");
    for (int i = 0; i < expected_count; i++)
    {
        GenerateNextID(services, count, services[count].serviceID);
        strcpy(services[count].customerName, test_services[i].customerName);
        strcpy(services[count].serviceDetails, test_services[i].serviceDetails);
        strcpy(services[count].serviceDate, test_services[i].serviceDate);
        ReplaceComma(services[count].customerName);
        ReplaceComma(services[count].serviceDetails);
        count++;

        printf("      - Added: %s (%s)\n", test_services[i].customerName, test_services[i].serviceDetails);
    }

    // Step 2: Save CSV
    printf("   Step 2: Saving data to CSV\n");
    SaveData(services, count);

    // Step 3: Clear memory
    printf("   Step 3: Clearing memory\n");
    memset(services, 0, sizeof(services));
    count = 0;

    // Step 4: Load CSV
    printf("   Step 4: Reloading data from CSV\n");
    LoadData(services, &count);

    // ==================== ASSERT ====================
    printf("\n🔹 ASSERT: Validating test results\n");

    assert_equal_int(1, file_exists(test_filename), "CSV file created successfully");
    assert_equal_int(expected_count, count, "Correct number of services reloaded");

    for (int i = 0; i < expected_count; i++)
    {
        char label[100];
        sprintf(label, "Service %d - Customer", i + 1);
        assert_equal_string(test_services[i].customerName, services[i].customerName, label);

        sprintf(label, "Service %d - Details", i + 1);
        assert_equal_string(test_services[i].serviceDetails, services[i].serviceDetails, label);

        sprintf(label, "Service %d - Date", i + 1);
        assert_equal_string(test_services[i].serviceDate, services[i].serviceDate, label);
    }

    int csv_lines = count_csv_lines(test_filename);
    assert_equal_int(expected_count, csv_lines, "CSV file line count matches records");

    // Cleanup
    remove(test_filename);


    if (test_failures == 0)
        printf(GREEN "\n✅ END-TO-END TEST CASE 1: COMPLETED SUCCESSFULLY\n" RESET);
    else
        printf(RED "\n❌ END-TO-END TEST CASE 1: FAILED with %d error(s)\n" RESET, test_failures);

    remove("test_service.csv");
}





//================== ALL FUNCTION TEST CASE ===================
// void test_full_service_management_flow() {
//     printf(BLUE "\n=== END-TO-END TEST CASE 2: Full Service Management System ===\n" RESET);

//     // Use test file
//     const char *test_filename = "test_service.csv";
//     SetCSVFile(test_filename);
//     remove(test_filename);

//     Service services[MAX];
//     int count = 0;

//     // ---------- STEP 1: Add Services ----------
//     printf("\n🔹 Step 1: Adding Initial Services\n");
//     const char *names[] = {"Alice", "Bob", "Charlie"};
//     const char *details[] = {"Aircon clean", "Fridge repair", "Microwave install"};
//     const char *dates[] = {"2025-10-09", "2025-10-10", "2025-10-11"};
//     for (int i = 0; i < 3; i++) {
//         GenerateNextID(services, count, services[count].serviceID);
//         strcpy(services[count].customerName, names[i]);
//         strcpy(services[count].serviceDetails, details[i]);
//         strcpy(services[count].serviceDate, dates[i]);
//         ReplaceComma(services[count].customerName);
//         ReplaceComma(services[count].serviceDetails);
//         count++;
//     }
//     SaveData(services, count);
//     assert_equal_int(1, file_exists(test_filename), "CSV created after Add");

//     // ---------- STEP 2: Reload to Confirm ----------
//     printf("\n🔹 Step 2: Reloading Services\n");
//     memset(services, 0, sizeof(services));
//     count = 0;
//     LoadData(services, &count);
//     assert_equal_int(3, count, "Loaded 3 records correctly");

//     // ---------- STEP 3: Search ----------
//     printf("\n🔹 Step 3: Searching Services\n");
//     int idx = SearchByName(services, count, "Bob");
//     assert_equal_int(1, idx, "SearchByName() found Bob at index 1");

//     idx = SearchByID(services, count, "S002");
//     assert_equal_int(1, idx, "SearchByID() found S002");

//     // ---------- STEP 4: Edit ----------
//     printf("\n🔹 Step 4: Editing a Record (Bob’s Service)\n");
//     UpdateService(services, count, "S002", "Refrigerator maintenance", "2025-10-15");
//     SaveData(services, count);

//     memset(services, 0, sizeof(services));
//     count = 0;
//     LoadData(services, &count);
//     assert_equal_string("Refrigerator maintenance", services[1].serviceDetails, "Edited service detail persisted");

//     // ---------- STEP 5: Delete ----------
//     printf("\n🔹 Step 5: Deleting a Record (Charlie)\n");
//     DeleteService(services, &count, "S003");
//     SaveData(services, count);

//     memset(services, 0, sizeof(services));
//     count = 0;
//     LoadData(services, &count);
//     assert_equal_int(2, count, "Charlie deleted successfully");

//     // ---------- STEP 6: Add Again (Next ID) ----------
//     printf("\n🔹 Step 6: Adding Another Record (Check Next ID)\n");
//     GenerateNextID(services, count, services[count].serviceID);
//     strcpy(services[count].customerName, "David");
//     strcpy(services[count].serviceDetails, "Dishwasher setup");
//     strcpy(services[count].serviceDate, "2025-10-20");
//     count++;
//     SaveData(services, count);

//     memset(services, 0, sizeof(services));
//     count = 0;
//     LoadData(services, &count);
//     assert_equal_string("S004", services[2].serviceID, "New ID assigned after deletion correctly");

//     // ---------- STEP 7: Cleanup ----------
//     remove(test_filename);
//     printf(GREEN "\n✅ END-TO-END TEST CASE 2 COMPLETED SUCCESSFULLY\n" RESET);
// }


// ==================== MAIN FOR TEST ====================
int main()
{
    test_complete_service_management_workflow();
    // test_full_service_management_workflow();
    return 0;
}

