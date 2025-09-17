#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 100 //max service
#define LINE_LEN 256 //max line in csv

typedef struct {
    char serviceID[10];       
    char customerName[50];    
    char serviceDetails[100]; 
    char serviceDate[15];    
} Service;

/* prototypes for helper functions */
void trim_newline(char *s);
void trim_whitespace(char *s);
void LoadData(Service services[],int *count);
void SaveData(Service services[],int count);
void SearchService(Service services[],int count);
void AddService(Service services[],int *count);
void DisplayAll(Service services[],int count);
void Menu(void);

void trim_newline(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[--len] = '\0';
    }
}

void trim_whitespace(char *s) {
    if (!s) return;
    // left trim
    char *p = s;
    while (*p && isspace((unsigned char)*p)) p++;
    if (p != s) memmove(s, p, strlen(p) + 1);
    // right trim
    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len-1])) s[--len] = '\0';
}


int main(){
    Service services[MAX];
    int count = 0; 

    LoadData(services, &count);

    int choice;
    do{
        Menu();
        printf("Enter choice: ");
        scanf("%d",&choice);
            getchar();
        

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


 
void LoadData(Service services[], int *count) {
    FILE *f = fopen("services.csv", "r");
    if (!f) {
        printf("[Info] No existing CSV found, starting fresh.\n");
        *count = 0;
        return;
    }
    printf("[Debug] Opened services.csv successfully.\n");

    char line[LINE_LEN];
    *count = 0;
    while (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        if (strlen(line) == 0) continue;

        printf("[Debug] Read line: %s\n", line);

        char *t = strtok(line, ",");
        if (!t) continue;
        strncpy(services[*count].serviceID, t, sizeof(services[*count].serviceID)-1);

        t = strtok(NULL, ",");
        if (t) strncpy(services[*count].customerName, t, sizeof(services[*count].customerName)-1);

        t = strtok(NULL, ",");
        if (t) strncpy(services[*count].serviceDetails, t, sizeof(services[*count].serviceDetails)-1);

        t = strtok(NULL, ",");
        if (t) strncpy(services[*count].serviceDate, t, sizeof(services[*count].serviceDate)-1);

        (*count)++;
        if (*count >= MAX) break;
    }
    fclose(f);
    printf("[Info] Loaded %d service(s)\n", *count);
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
void DisplayAll(Service services[], int count) {
    if (count == 0) {
        printf("No services found.\n");
        return;
    }
    printf("\n=== All Services ===\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %s | Name: %s | Details: %s | Date: %s\n",
               services[i].serviceID,
               services[i].customerName,
               services[i].serviceDetails,
               services[i].serviceDate);
    }
    printf("====================\n");
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

