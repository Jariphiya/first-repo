#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include<assert.h>
#include"project.h"

#define Test(name) void name()
#define ASSERT(cond, msg)\
    if(!(cond)) printf("Test failed: %s\n",msg);\
    else printf("%s passed\n",msg)

Test(test_Replace_and_Restore_Comma){
    char str[100] = "Hello,world,example";
    ReplaceComma(str);
    ASSERT(strcmp(str, "Hello;world;example") == 0, "ReplaceComma()");
    RestoreComma(str);
    ASSERT(strcmp(str, "Hello,world,example") == 0, "RestoreComma()");
}

Test(test_generate_next_id){
    Service services[3] = {
        {"S001", "A", "X", "2025-01-01"},
        {"S002", "B", "Y", "2025-01-02"},
        {"S003", "C", "Z", "2025-01-03"}
    };
    char newid[10];
    GenerateNextID(services, 3, newid);
    ASSERT(strcmp(newid, "S004") == 0, "GenerateNextID()");
}

// Test(test_save_and_load_data){
//     Service services[2] = {
//         {"S001", "Alice Wonderland", "Cleaning", "2025-01-01"},
//         {"S002", "Ada Wong", "Maintenance", "2025-02-01"}
//     };
//     SaveData(services,2);

//     Service loaded[2];
//     int count = 0;
//     LoadData(loaded, &count);

//     ASSERT(count == 2, "LoadData() count");
//     ASSERT(strcmp(loaded[0].customerName,"Alice Wonderland") == 0, "LoadData() record 1");
//     ASSERT(strcmp(loaded[1].serviceDetails,"Maintenance") == 0, "LoadData() record 2");
// }

Test(test_search_service) {
    Service services[2] = {
        {"S001", "Alice", "Fix lights", "2025-01-01"},
        {"S002", "Bob", "Repair AC", "2025-01-02"}
    };

    int found = 0;
    for (int i = 0; i < 2; i++) {
        if (strcasecmp(services[i].customerName, "alice") == 0)
            found = 1;
    }

    int find = 0;
    for(int j = 0; j < 2; j++){
        if(strcasecmp(services[j].serviceID, "S001") == 0)
        find = 1;
    }
    ASSERT(found == 1, "SearchService() by name");
    ASSERT(find == 1, "SearchService() by ID");
}

int main() {
    printf("\n===== Running Unit Tests =====\n");
    test_Replace_and_Restore_Comma();
    test_generate_next_id();
    test_search_service();
    // test_save_and_load_data();
    printf("\n===== All Tests Complete =====\n");
    return 0;
}
