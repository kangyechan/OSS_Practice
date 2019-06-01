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
        printf("Location : %s \r\n", companies[i].location);
        printf("City : %s \r\n", companies[i].city);
        printf("Available Positions : \r\n");

        for(int j = 0; j < companies[i].positionCount; j++){
            printf(" %d. %s \r\n", j + 1, companies[i].positions[j]);
        }
    }
    printf("**********************************************************\n");
}

void printschools(School *schools, int count) {
    char *sizeToStr;
    printf("\n*********************** Graduate Schools List *************************\n");
    for (int i = 0; i < count; i++) {
        printf("\r\n[%d] %s \r\n", i + 1, schools[i].name);
       // printf("Recruiting # : %d \r\n", companies[i].recruitNum);
     //   printf("Coding Test : %s \r\n", companies[i].coding);
      //  printf("Salary : %d \r\n", companies[i].salary);
        printf("Location : %s \r\n", schools[i].location);
      //  printf("City : %s \r\n", companies[i].city);
        printf("Type : \r\n");

        for(int j = 0; j < schools[i].typeCount; j++){
            printf(" %d. %s \r\n", j + 1, schools[i].type[j]);
        }
    }
    printf("************************************************************************\n");
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

void searchByJob(Company *companies, int companyCount, char jobs[][40], int jobCount){
    int jobSelection;
    char *sizeToStr;
    int selectedComapny;
    char jobToSearch[40];
    for (int c = 0; c < jobCount; c++) {
            printf("[%d] %s \r\n", c + 1, jobs[c]);
    }

    printf("Enter your choice from position list : ");
    scanf("%d", &jobSelection);

    strcpy(jobToSearch,jobs[jobSelection-1]);
    printf("Selected job is : %s \r\n", jobToSearch);

    for (int i = 0; i < companyCount; i++) {
    // printf("%s",companies[i].name);
        for(int j =0; j < companies[i].positionCount; j++){
            if(!strcmp(companies[i].positions[j], jobToSearch)){ //if job is found
                    //print company info
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
                    printf("Position: \r\n");
                    printf(" %s \r\n", companies[i].positions[j]);
                    
            }
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
    printf("\r\n%s \r\n", companies[selectedComapny-1].name);
    printf("Size : %s \r\n", sizeToStr);
    printf("Recruiting # : %d \r\n", companies[selectedComapny-1].recruitNum);
    printf("Coding Test : %s \r\n", companies[selectedComapny-1].coding);
    printf("Salary : %d \r\n", companies[selectedComapny-1].salary);
    printf("Available Positions : \r\n");
    for(int j=0; j<companies[selectedComapny-1].positionCount; j++){
        printf(" %d. %s \r\n", j+1,companies[selectedComapny-1].positions[j]);
    }
}




void enterInfo(User* ourUser){
    char answer[5];
    char salary[10];
    printf("What is your name? : ");
    scanf("%s", ourUser[0].name);
    printf("Hi %s, Welcome!", ourUser[0].name);
  
    printf("\r\nWhere do you live or want to work? : ");
    scanf("%s", ourUser[0].city);
    printf("So you want to work at %s\r\n", ourUser[0].city);


    printf("How about working abroad? y/n: \r\n");
    scanf("%s", answer);
    if(!strcmp(answer, "y")){
        ourUser[0].workAbroad=1;
    }else{
        ourUser[0].workAbroad=0;
    }
    if(ourUser[0].workAbroad){
        printf("So you don't mind working overseas!\r\n");
    }else{
        printf("Okay we understand. You like staying closer to home.\r\n");
    }
    

    printf("How much salary would be okay for you? : ");
    scanf("%s", salary);
    ourUser[0].salary = atoi(salary);
    if( ourUser[0].salary>=7000){
        printf("%d is quite a bit of money!\r\n", ourUser[0].salary);
    }else{
        printf("%d sounds like a good amount.\r\n", ourUser[0].salary);
    }

    printf("Now we will run our algorithm....\r\n");
    Sleep(1800);
    printf("Making calculations...\r\n");
    Sleep(1800);
    printf("Making a cup of coffee...\r\n");
    Sleep(1800);
    printf("Finalyzing..");
    for (int g = 0; g < 6; g++)
    {
        Sleep(600);

        printf("...");
    }
    printf("\r\nHere are the results!\r\n");
    Sleep(1500);
    printf("NONE\r\n");




}
