#include "json.h"

void printCompanies(Company *companies, int count) {
    char *sizeToStr;
    printf("\n*********************** Companies *************************\n");
    for (int i = 0; i < count; i++) {
        if (companies[i].size == 1)
            sizeToStr = "Large";
        else if (companies[i].size == 2)
            sizeToStr = "Medium";
        else if (companies[i].size == 3)
            sizeToStr = "Small";
        else if (companies[i].size == 4)
            sizeToStr = "Startup";

        printf("\r\n[%d] %s \r\n", i + 1, companies[i].name);
        printf("Size : %s \r\n", sizeToStr);
        printf("Recruiting # : %d \r\n", companies[i].recruitNum);
        printf("Coding Test : %s \r\n", companies[i].coding);
        printf("Salary : %d \r\n", companies[i].salary);
        printf("Location is : %s \r\n", companies[i].location);
        printf("Available Positions : \r\n");

        for(int j = 0; j < companies[i].positionCount; j++){
            printf(" %d. %s \r\n", j+1, companies[i].positions[j]);
        }
    }
    printf("**********************************************************\n");
}



void searchByName(Company *companies, int count){
    char name[20];
    char *sizeToStr;
    
    printf("Enter a company name: ");
    scanf("%s", name);
    // printf("%d",(int)strlen(name));

    printf("line2 test");

    printf("Results:");

    for (int i = 0; i < count; i++) {
        // printf("%s",companies[i].name);

        if(!(strcmp(name, companies[i].name))){
            if (companies[i].size == 1){
                sizeToStr = "Large";
            }
            else if (companies[i].size == 2){
                sizeToStr = "Medium";
            }
            else if (companies[i].size == 3){
                sizeToStr = "Small";
            }
            else{
                sizeToStr = "Startup";
            }

            printf("\r\n[%d] %s \r\n", i + 1, companies[i].name);
            printf("Recruiting # : %d \r\n", companies[i].recruitNum);
            printf("Coding Test : %s \r\n", companies[i].coding);
            printf("Salary : %d \r\n", companies[i].salary);
            printf("Available Positions : \r\n");
            for(int j=0; j<companies[i].positionCount; j++){
                printf(" %d. %s \r\n", j+1,companies[i].positions[j]);
            }
        }
    }
}

void searchBySize(Company *companies, int count){
    char size[10];
    char *sizeToStr;
    int selectedComapny;

    printf("Enter size of company: ");
    scanf("%s", size);

    printf("%d",(int)strlen(size));

    printf("Results:");

    for (int i = 0; i < count; i++) {
    // printf("%s",companies[i].name);

            //convert size number to string equivalent
            if (companies[i].size == 1){
                sizeToStr = "Large";
            }
            else if (companies[i].size == 2){
                sizeToStr = "Medium";
            }
            else if (companies[i].size == 3){
                sizeToStr = "Small";
            }
            else{
                sizeToStr = "Startup";
            }
        if(!strcmp(sizeToStr,size)){ //if user input and company size are equal
            printf("\r\n[%d] %s \r\n", i + 1, companies[i].name);
            printf("Size : %s \r\n", sizeToStr);

        }
    }

        
    printf("Enter number of company for more information: ");
    scanf("%d", &selectedComapny);
    printf("\r\n%s \r\n", companies[selectedComapny-1].name);
    printf("\r\nRecruiting # : %d \r\n", companies[selectedComapny-1].recruitNum);
    printf("Coding Test : %s \r\n", companies[selectedComapny-1].coding);
    printf("Salary : %d \r\n", companies[selectedComapny-1].salary);
    printf("Available Positions : \r\n");
    for(int j=0; j<companies[selectedComapny-1].positionCount; j++){
        printf(" %d. %s \r\n", j+1,companies[selectedComapny-1].positions[j]);
    }
}

void searchBySalary(Company *companies, int count){
    int minSalary;
    char *sizeToStr;
    int selectedComapny;
    
    printf("Enter desired minimum salary : ");
    scanf("%d", &minSalary);

    // printf("%d",(int)strlen(size));

    printf("Results:");

    for (int i = 0; i < count; i++) {
    // printf("%s",companies[i].name);
        if(companies[i].salary>minSalary){ //if user input and company size are equal

            printf("\r\n[%d] %s \r\n", i + 1, companies[i].name);
            printf("Salary : %d \r\n", companies[i].salary);
        }
    }

        
    printf("Enter number of company for more information: ");
    scanf("%d", &selectedComapny);
    //convert size number to string equivalent
    if (companies[selectedComapny-1].size == 1){
        sizeToStr = "Large";
    } else if (companies[selectedComapny-1].size == 2){
        sizeToStr = "Medium";
    } else if (companies[selectedComapny-1].size == 3){
        sizeToStr = "Small";
    } else{
        sizeToStr = "Startup";
    }
    printf("Size : %s \r\n", sizeToStr);
    printf("\r\n%s \r\n", companies[selectedComapny-1].name);
    printf("\r\nRecruiting # : %d \r\n", companies[selectedComapny-1].recruitNum);
    printf("Coding Test : %s \r\n", companies[selectedComapny-1].coding);
    printf("Salary : %d \r\n", companies[selectedComapny-1].salary);
    printf("Available Positions : \r\n");
    for(int j=0; j<companies[selectedComapny-1].positionCount; j++){
        printf(" %d. %s \r\n", j+1,companies[selectedComapny-1].positions[j]);
    }
}
