#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char serviceID[10];       
    char customerName[50];    
    char serviceDetails[100]; 
    char serviceDate[15];    
} Service;

void LoadData(Service services[],int *count);
void SaveData(Service services[],int count);
void SearchService(Service services[],int count);
void AddService(Service services[],int *count);
void DisplayAll(Service services[],int count);
void Menu(void);

int main(){
    Service services[MAX];
    int count = 0; 

    LoadData(services, &count);

    int choice;
    do{
        Menu();
        printf("Enter choice: ");
        if(scanf("%d",&choice)!= 1){
            printf("Invalid input. Exiting. \n");
            break;
        }

    switch(choice) {
        case 1: DisplayAll(services, count); break;
        case 2: AddService(services, &count); break; 
        case 3: SearchService(services, count); break;
        case 0: printf("Exiting program...\n"); break;
        default: printf("Choice invalid. Try again.\n");
                    }
    }while(choice != 0);

    return 0;


}


 
//load data from csv
void LoadData(Service services[],int *count){
    FILE *file = fopen("services.csv","r");
    if(file == NULL){
        printf("No existing file found.\n");
        return;
    }
    *count = 0;
    while(fscanf(file, "%9[^,],%49[^,],%99[^,],%14s\n",
                    services[*count].serviceID,
                    services[*count].customerName,
                    services[*count].serviceDetails,
                    services[*count].serviceDate) == 4){ //read only 4 fields
            (*count)++;                    
            if (*count >= MAX) break;
    }

    fclose(file);

}

//save data to csv
void SaveData(Service services[], int count){
    FILE *file = fopen("services.csv", "w"); 
    if (file == NULL){
        printf("Error: could not save file!\n");
        return;
    }

    for(int i=0; i < count;i++){
        fprintf(file,"%s,%s,%s,%s\n",
        services[i].serviceID,
        services[i].customerName,
        services[i].serviceDetails,
        services[i].serviceDate);
    }
    fclose(file);
    printf("Data Saved.\n");

}

//add new service
void AddService(Service services[],int *count){
    //check array bounds.
    if(*count >= MAX){
        printf("Cannot add more services (max %d reached).\n",MAX);
        return;
    }

    printf("Enter Service ID: ");
    scanf(" %9s", services[*count].serviceID);

    printf("Enter Name: \n");
    scanf(" %49[^\n]",services[*count].customerName);

    printf("Enter Service Detail: \n");
    scanf(" %99[^\n]",services[*count].serviceDetails);

    printf("Enter Service Date(YYYY-MM-DD): \n");
    scanf(" %14s",services[*count].serviceDate);

    (*count)++;
    SaveData(services,*count);
    printf("Service added and saved successfully!\n");
}

//search for services by ID or Name P.S. WHY DOESN'T THIS WORK AHHHH
void SearchService(Service services[], int count) {
    char input[100];
    printf("Enter Service ID or Customer Name to search: ");
    getchar();
    fgets(input, sizeof(input),stdin);

    input[strcspn(input, "\n")] = 0;

    int found = 0;
    for(int i = 0; i < count; i++) {
        if(strcmp(services[i].serviceID, input) == 0 || 
           strstr(services[i].customerName, input) != NULL) {
            printf("Service Found:\n");
            printf("ID: %s\nCustomer: %s\nDetails: %s\nDate: %s\n\n",
                   services[i].serviceID,
                   services[i].customerName,
                   services[i].serviceDetails,
                   services[i].serviceDate);
            found =1;    
        }
    }

    if(!found) {
        printf("No matching service found.\n");
    }
}

//display all records cuz I'm paranoid
void DisplayAll(Service services[],int count){
    if(count ==0){
        printf("No services to display,\n");
        return;
    }
    printf("\n---- All Services (%d) ----\n",count);
    for(int i=0; i< count;i++){
        printf("%d) ID: %s | Name: %s |Service Details: %s | Date of service: %s\n",
        i+1,
        services[i].serviceID,
        services[i].customerName,
        services[i].serviceDetails,
        services[i].serviceDate);
    }
    printf("------------------------\n");

}

//menu page
void Menu() {

    printf("\n===== Customer Service Management =====\n");
    printf("1. Display All Services\n");
    printf("2. Add Service\n");
    printf("3. Search Service\n");
    printf("4. Update Service\n");
    printf("5. Delete Service\n");
    printf("0. Exit\n");
    printf("=======================================\n");
}

