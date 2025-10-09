#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define DEFAULT_FILENAME "services.csv"

typedef struct {
    char serviceID[10];
    char customerName[50];
    char serviceDetails[100];
    char serviceDate[15];
} Service;

// Utility functions
void ReplaceComma(char *str);
void RestoreComma(char *str);
void GenerateNextID(Service services[], int count, char *newID);

// Core data functions
void LoadData(Service services[], int *count);
void SaveData(Service services[], int count);
void SetCSVFile(const char *filename); 

// Service operations
void AddService(Service services[], int *count);
void DeleteService(Service services[], int *count);
void SearchService(Service services[], int count);
void UpdateService(Service services[], int count);
void DisplayAll(Service services[], int count);
void Menu(void);

// Unit test functions (from unit_test.c)
void TestAddService(void);
void TestUpdateService(void);
void TestDeleteService(void);
void RunUnitTests(void);

// E2E test functions (from e2e.c)
void TestE2E(void);
void RunAllTests(void);

#endif
