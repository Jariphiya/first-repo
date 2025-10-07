#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100 // max service

typedef struct
{
    char serviceID[10];
    char customerName[50];
    char serviceDetails[100];
    char serviceDate[15];
} Service;

void ReplaceComma(char *str);
void RestoreComma(char *str);
void GenerateNextID(Service services[], int count, char *newID);
void LoadData(Service services[], int *count);
void SaveData(Service services[], int count);
void SearchService(Service services[], int count);
void AddService(Service services[], int *count);
void DeleteService(Service services[], int *count);
void DisplayAll(Service services[], int count);
void UpdateService(Service services[], int count);
void Menu(void);

int main()
{
    Service services[MAX];
    int count = 0;

    LoadData(services, &count);

    int choice;
    do
    {
        Menu();
        char buff[10];
        printf("Enter choice: ");
        if (!fgets(buff, sizeof(buff), stdin))
        {
            choice = -1;
        }
        else
        {
            choice = atoi(buff);
        }

        switch (choice)
        {
        case 1:
            DisplayAll(services, count);
            break;
        case 2:
            AddService(services, &count);
            break;
        case 3:
            SearchService(services, count);
            break;
        case 4:
            DeleteService(services, &count);
            break;
        case 5:
            UpdateService(services, count);
            break;
        case 9:
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Choice invalid. Try again.\n");
            break;
        }
        printf("Enter to continue...");
        while (getchar() != '\n');
    } while (1);

    return 0;
}

// Replace commas with semicolons to protect CSV structure
void ReplaceComma(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ',')
        {
            str[i] = ';'; // replace comma with semicolon
        }
    }
}

// Restore semicolons back to commas when displaying data
void RestoreComma(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ';')
        {
            str[i] = ',';
        }
    }
}

void LoadData(Service services[], int *count)
{
    FILE *file = fopen("services.csv", "r");
    if (file == NULL)
    {
        printf("No existing file found.\n");
        return;
    }
    *count = 0;

    // fscanf reads 4 fields separated by commas
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^\n]\n",
                  services[*count].serviceID,
                  services[*count].customerName,
                  services[*count].serviceDetails,
                  services[*count].serviceDate) != EOF)
    {

        (*count)++;
    }

    fclose(file);
    printf("%d records loaded.\n", *count);
}

// save data to csv
void SaveData(Service services[], int count)
{
    FILE *file = fopen("services.csv", "w");
    if (file == NULL)
    {
        printf("Error: could not save file!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s,%s,%s,%s\n",
                services[i].serviceID,
                services[i].customerName,
                services[i].serviceDetails,
                services[i].serviceDate);
    }
    fclose(file);
    printf("Data Saved.\n");
}

// generate new id automatically
void GenerateNextID(Service services[], int count, char *newID)
{
    int maxID = 0;
    for (int i = 0; i < count; i++)
    {
        int num = atoi(services[i].serviceID + 1); // skip 'S'
        if (num > maxID)
        {
            maxID = num;
        }
    }
    sprintf(newID, "S%03d", maxID + 1); // format as S001, S002, etc.
}

void AddService(Service services[], int *count)
{
    char confirm;
    printf("You are about to add a new service record.\n");
    printf("Press Y to continue or 0 to cancel: ");
    scanf(" %c", &confirm);
    getchar(); // clear buffer

    if (confirm == '0')
    {
        printf("Operation cancelled.\n");
        return;
    }

    // Automatically assign a new ID
    GenerateNextID(services, *count, services[*count].serviceID);
    printf("Assigned Service ID: %s\n", services[*count].serviceID);

    // Now collect other data
    printf("Enter customer name: ");
    fgets(services[*count].customerName, sizeof(services[*count].customerName), stdin);
    services[*count].customerName[strcspn(services[*count].customerName, "\n")] = '\0';
    ReplaceComma(services[*count].customerName);

    printf("Enter service details: ");
    fgets(services[*count].serviceDetails, sizeof(services[*count].serviceDetails), stdin);
    services[*count].serviceDetails[strcspn(services[*count].serviceDetails, "\n")] = '\0';
    ReplaceComma(services[*count].serviceDetails);

    printf("Enter service date (YYYY-MM-DD): ");
    scanf("%s", services[*count].serviceDate);

    // Show confirmation summary
    printf("\nYou entered:\n");
    printf("Service ID: %s\n", services[*count].serviceID);
    printf("Customer: %s\n", services[*count].customerName);
    printf("Details: %s\n", services[*count].serviceDetails);
    printf("Date: %s\n", services[*count].serviceDate);

    printf("\nConfirm add? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y')
    {
        (*count)++;
        SaveData(services, *count);
        printf("Service added and saved successfully!\n");
    }
    else
    {
        printf("Addition cancelled.\n");
    }
}

// search for services by ID or Name P.S. It works now :D
void SearchService(Service services[], int count)
{
    char input[100];
    printf("Enter Service ID or Customer Name to search: ");
    scanf(" %[^\n]", input);
    // getchar();
    // fgets(input, sizeof(input),stdin);

    // input[strcspn(input, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(services[i].serviceID, input) == 0 ||
            strcasecmp(services[i].customerName, input) == 0)
        {
            printf("Service Found:\n");
            printf("ID: %s\nCustomer: %s\nDetails: %s\nDate: %s\n\n",
                   services[i].serviceID,
                   services[i].customerName,
                   services[i].serviceDetails,
                   services[i].serviceDate);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No matching service found.\n");
    }
}

// delete record
void DeleteService(Service services[], int *count)
{
    char id[50];
    char confirm[4];
    int found;

    while (1)
    {

        printf("Enter ID (or 0 to cancel deletion): ");
        scanf(" %[^\n]", id);

        if (strcmp(id, "0") == 0)
        {
            printf("Deletion Cancelled. Returning to Main Menu.\n");
            return; // if cancel return to main page
        }

        found = -1;
        for (int i = 0; i < *count; i++)
        {
            if (strcmp(services[i].serviceID, id) == 0)
            {
                found = i;
                break;
            }
        }
        if (found == -1)
        {
            printf("Service ID not found.\n");
            continue; // if not found then ask again
        }

        // show target record
        printf("\nService found:\n");
        printf("ID: %s | Name: %s | Details: %s | Date: %s\n",
               services[found].serviceID,
               services[found].customerName,
               services[found].serviceDetails,
               services[found].serviceDate);

        // ask for confirmation
        printf("\nAre you sure you want to delete this record? (y/n): ");
        scanf(" %c", &confirm);

        if (confirm[0] == 'y' || confirm[0] == 'Y')
        {
            for (int i = found; i < *count; i++)
            {
                services[i] = services[i + 1];
            }

            (*count)--;
            SaveData(services, *count);
            printf("Service deleted successfully!.\n");
            return;
        }
        else
        {
            printf("Deletion Cancelled.\n");
        }
    }
}

// update service
void UpdateService(Service services[], int count)
{
    char id[10];
    printf("Enter Service ID to update: ");
    scanf(" %s", id);

    int found = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcasecmp(services[i].serviceID, id) == 0)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("No service found with ID %s\n", id);
        return;
    }

    // Show current record
    printf("\nService Found:\n");
    printf("ID: %s\nCustomer: %s\nDetails: %s\nDate: %s\n",
           services[found].serviceID,
           services[found].customerName,
           services[found].serviceDetails,
           services[found].serviceDate);

    int choice;
    int changed = 0; // track updates

    do
    {
        printf("\nWhat would you like to update?\n");
        printf("1. Customer Name\n");
        printf("2. Service Details (will also update Date)\n");
        printf("3. Service Date only\n");
        printf("0. Finish updating\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice)
        {
        case 1:
            printf("Enter new Customer Name: ");
            scanf(" %[^\n]s", services[found].customerName);
            changed = 1;
            break;
        case 2:
            printf("Enter new Service Details: ");
            fgets(services[found].serviceDetails, sizeof(services[found].serviceDetails), stdin);
            services[found].serviceDetails[strcspn(services[found].serviceDetails, "\n")] = '\0';
            ReplaceComma(services[found].serviceDetails);

            printf("Enter updated Service Date (YYYY-MM-DD): ");
            scanf(" %s", services[found].serviceDate);
            changed = 1;
            break;
        case 3:
            printf("Enter new Service Date (YYYY-MM-DD): ");
            scanf(" %s", services[found].serviceDate);
            changed = 1;
            break;
        case 0:
            printf("Finished updating.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    // Ask for confirmation only if something changed
    if (changed)
    {
        char confirm;
        printf("\nAre you sure you want to save these changes? (y/n): ");
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y')
        {
            SaveData(services, count);
            printf("Service record updated successfully!\n");
        }
        else
        {
            printf("Changes were discarded.\n");
        }
    }
    else
    {
        printf("No changes were made.\n");
    }
}

// display all records cuz I'm paranoid
void DisplayAll(Service services[], int count)
{
    if (count == 0)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n===============================================================================\n");
    printf("                         CUSTOMER SERVICE RECORDS                       \n");
    printf("===============================================================================\n");
    printf("| %-8s | %-20s | %-25s | %-12s |\n",
           "ID", "Customer Name", "Service Details", "Date");
    printf("------------------------------------------------------------------------\n");

    for (int i = 1; i < count; i++)
    {
        // Make local copies for readable display
        char nameCopy[100], detailsCopy[200];
        strcpy(nameCopy, services[i].customerName);
        strcpy(detailsCopy, services[i].serviceDetails);
        RestoreComma(nameCopy);
        RestoreComma(detailsCopy);

        // Limit long text to prevent table overflow
        if (strlen(nameCopy) > 19)
        {
            nameCopy[17] = '.';
            nameCopy[18] = '.';
            nameCopy[19] = '\0';
        }
        if (strlen(detailsCopy) > 24)
        {
            detailsCopy[22] = '.';
            detailsCopy[23] = '.';
            detailsCopy[24] = '\0';
        }

        printf("| %-8s | %-20s | %-25s | %-12s |\n",
               services[i].serviceID,
               nameCopy,
               detailsCopy,
               services[i].serviceDate);
    }

    printf("================================================================================\n");
    printf("Total Records: %d\n\n", count);
}

// menu page
void Menu()
{

    printf("\n===== Customer Service Management =====\n");
    printf("1. Display All Services\n");
    printf("2. Add Service\n");
    printf("3. Search Service\n");
    printf("4. Delete Service\n");
    printf("5. Update Service\n");
    printf("9. Exit\n");
    printf("=======================================\n");
}
