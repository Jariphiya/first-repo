#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

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

// Service operations
void AddService(Service services[], int *count);
void DeleteService(Service services[], int *count);
void SearchService(Service services[], int count);
void UpdateService(Service services[], int count);
void DisplayAll(Service services[], int count);
void Menu(void);

#endif
