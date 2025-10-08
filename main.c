#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"project.h"

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