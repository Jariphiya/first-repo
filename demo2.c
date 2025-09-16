#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX_SERVICES 100

//structure
typedef struct {
    char serviceID[10];       
    char customerName[50];    
    char serviceDetails[100]; 
    char serviceDate[15];    
} Service;

Service services[MAX_SERVICES];
int count = 0; 

int main(){
    const char  *filename = "services.csv";

    int choice;
 

    
    Menu();
    printf("Enter choice: ");
    scanf("%d",&choice);
    getchar(); //clear buffer



}

void SavetoCSV(Service services[], int count, const char *filename){
    FILE *fp = fopen(filename, "w"); //open file to write
    if (!fp){
        printf("Error: could not save file!\n");
        return;
    }

    for(int i=0; i < count;i++){
        fprintf(fp,"%s,%s,%s,%s\n",
        services[i].serviceID,
        services[i].customerName,
        services[i].serviceDetails,
        services[i].serviceDate);
    }
    fclose(fp);
    printf("Data Saved to %s \n",filename);

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
    printf("Enter choice: ");
}

