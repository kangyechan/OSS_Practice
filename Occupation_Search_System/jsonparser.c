#include "json.h"

int fileCheck(char *fileName, char *doc) {
    if (doc == NULL) {
        printf("%s is NULL", fileName);
        return -1;
    }
}

char *readfile(char *filename, int *filesize) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("WRONG FILENAME\n");
        return NULL;
    }

    int size;
    char *buffer;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp); //current file position
    fseek(fp, 0, SEEK_SET);

    buffer = (char *)malloc(size + 1);
    memset(buffer, 0, size + 1);

    if (fread(buffer, 1, size, fp) < 1) {
        *filesize = 0;
        free(buffer);
        fclose(fp);
        return NULL;
    }

    *filesize = size;
    fclose(fp);
    return buffer;
}

void array_parse(char *doc, JSON *json, int *oriPos, int *oriTokenIndex) {
    int pos = *oriPos;
    int tokenIndex = *oriTokenIndex;
    int s, e;
    int arraytokenIndex = tokenIndex;        //save tokenIndex for array we found
    json->tokens[tokenIndex].type = ARRAY;   // token.type is STRING
    tokenIndex++;                            //increase tokenIndex for element found insdie array
    s = pos;                                 // the token starts at '['
    json->tokens[arraytokenIndex].start = s; // token.start = s
    int arrSize = 0;
    while (doc[pos] != ']') { // increase pos until it meets ]
        pos++;
        switch (doc[pos]) {
        case '"':
            arrSize++;                              //increase size for each element found. This is array size.
            json->tokens[tokenIndex].type = STRING; // token.type is STRING
            s = pos + 1;                            // the word starts after "
            json->tokens[tokenIndex].start = s;     // token.start = s
            while (doc[pos + 1] != '"') {        // increase pos until it meets "
                pos++;
            }
            e = ++pos;                         // the word ends when doc[pos] meets ". (includes last ")
            json->tokens[tokenIndex].end = e;  // token.end = e
            json->tokens[tokenIndex].size = 0; //0 because it is a value
            json->tokens[tokenIndex].string = (char *)malloc(e - s + 1);
            memset(json->tokens[tokenIndex].string, 0, e - s + 1);
            memcpy(json->tokens[tokenIndex].string, doc + s, e - s);
            tokenIndex++; //increase tokenIndex for element found insdie array
            break;

        case '[':
            arrSize++;  
            array_parse(doc, json, &pos, &tokenIndex);
            break;

        case '{':
            arrSize++;  
            object_parse(doc, json, &pos, &tokenIndex);
            break;

        case '-': case '0': case '1': case '2':
        case '3': case '4': case '5': case '6':
        case '7': case '8': case '9': case 't':
        case 'f': case 'n':
            arrSize++;
            json->tokens[tokenIndex].type = PRIMITIVE;
            s = pos;
            json->tokens[tokenIndex].start = s;
            while (doc[pos + 1] != ',') { // ','만날때까지
                if (doc[pos + 1] == '\n' || doc[pos+1] == ']') break;
                else pos++;
            }
            e = ++pos; // the word ends when doc[pos] meets ',' or NULL
            json->tokens[tokenIndex].end = e;
            json->tokens[tokenIndex].size = 0;
            json->tokens[tokenIndex].string = (char *)malloc(e - s + 1);
            memset(json->tokens[tokenIndex].string, 0, e - s + 1);
            memcpy(json->tokens[tokenIndex].string, doc + s, e - s);
            if(doc[pos] != ']') pos++;
            tokenIndex++;
            break;

        default:
            break;
        }
    }
    e = ++pos;
    json->tokens[arraytokenIndex].end = e;
    json->tokens[arraytokenIndex].size = arrSize;
    //put doc[s]~doc[e+1] in token.string for the array
    json->tokens[arraytokenIndex].string = (char *)malloc(e - json->tokens[arraytokenIndex].start + 1);
    memset(json->tokens[arraytokenIndex].string, 0, e - json->tokens[arraytokenIndex].start + 1);
    memcpy(json->tokens[arraytokenIndex].string, doc + json->tokens[arraytokenIndex].start, e - json->tokens[arraytokenIndex].start);

    *oriTokenIndex = tokenIndex;
    *oriPos = pos;
}

void object_parse(char *doc, JSON *json, int *oriPos, int *oriTokenIndex) {
    int pos = *oriPos;
    int tokenIndex = *oriTokenIndex;
    int s, e;
    int objtokenIndex = tokenIndex;
    json->tokens[tokenIndex].type = OBJECT; // token.type is STRING
    tokenIndex++;                           //increase tokenIndex for element found insdie array
    s = pos;                                // the token starts at '['
    json->tokens[objtokenIndex].start = s;  // token.start = s
    int objSize = 0;

    while (doc[pos] != '}') { // increase pos until it meets }
        pos++;
        switch (doc[pos]) {
        case '"':
            json->tokens[tokenIndex].type = STRING; // token.type is STRING
            s = pos + 1;                          // the word starts after "
            pos++;
            json->tokens[tokenIndex].start = s;     // token.start = s
            while (doc[pos] != '"') { // increase pos until it meets "
                pos++;
            }
            e = pos;                         // the word ends when doc[pos] meets ". (includes last ")
            json->tokens[tokenIndex].end = e;  // token.end = e
            json->tokens[tokenIndex].size = 0; //if : is coming right after "" {size = 1}
            while (doc[pos] != ':' && doc[pos] != '\n' && doc[pos] != ',' && doc[pos] != '}') {
                pos++;
            }
            if (doc[pos] == ':') {
                json->tokens[tokenIndex].size = 1;
            }
            else {
                objSize++;
            }
            json->tokens[tokenIndex].string = (char *)malloc(e - s + 1);
            memset(json->tokens[tokenIndex].string, 0, e - s + 1);
            memcpy(json->tokens[tokenIndex].string, doc + s, e - s);
            tokenIndex++; //increase tokenIndex for element found insdie array
            break;

        case '[':
            objSize++;
            array_parse(doc, json, &pos, &tokenIndex);
            break;

        case '{':
            objSize++;
            object_parse(doc, json, &pos, &tokenIndex);
            break;

        case '-': case '0': case '1': case '2':
        case '3': case '4': case '5': case '6':
        case '7': case '8': case '9': case 't':
        case 'f': case 'n':
            json->tokens[tokenIndex].type = PRIMITIVE;
            s = pos;
            json->tokens[tokenIndex].start = s;
            while (doc[pos + 1] != ',') { // ','만날때까지
                if (doc[pos + 1] == '\n' || doc[pos+1] == '}') { // 만약 ','를 만나지 않았는데 '\n'를 만난다면 끝남
                    break;
                }
                else pos++;
            }
            objSize++;
            e = ++pos; // the word ends when doc[pos] meets ',' or NULL
            json->tokens[tokenIndex].end = e;
            json->tokens[tokenIndex].size = 0;
            json->tokens[tokenIndex].string = (char *)malloc(e - s + 1);
            memset(json->tokens[tokenIndex].string, 0, e - s + 1);
            memcpy(json->tokens[tokenIndex].string, doc + s, e - s);
            if(doc[pos] != '}') pos++;
            tokenIndex++;
            break;
        default:
            break;

        }
    }
    e = ++pos;
    json->tokens[objtokenIndex].end = e;
    json->tokens[objtokenIndex].size = objSize;
    //put doc[s]~doc[e+1] in token.string for the array
    json->tokens[objtokenIndex].string = (char *)malloc(e - json->tokens[objtokenIndex].start + 1);
    memset(json->tokens[objtokenIndex].string, 0, e - json->tokens[objtokenIndex].start + 1);
    memcpy(json->tokens[objtokenIndex].string, doc + json->tokens[objtokenIndex].start, e - json->tokens[objtokenIndex].start);
    
    *oriTokenIndex = tokenIndex;
    *oriPos = pos;
}

void json_parse(char *doc, int size, JSON *json, int *b_cnt) {
    int cnt = 0;
    int pos = 0;        //for checking position in doc.
    int e, s;           //ending, starting position for each token
    int tokenIndex = 0; //index for token

    while (pos < size) {
        switch (doc[pos]) {
        case '{':
            object_parse(doc, json, &pos, &tokenIndex);
            break;
        default :
            pos++;
        }
    }

    *b_cnt = tokenIndex; //update bigcnt
}

void freeJson(JSON *json, int bigcnt) {
    for (int i = 0; i < bigcnt; i++) {
        if (json->tokens[i].type == STRING)
            free(json->tokens[i].string);
    }
}

void printResult(JSON *json, int bigcnt) {
    char *typeToStr;
    printf("\n*********************** All Tokens *************************\n");
    for (int i = 0; i < bigcnt; i++) {
        if (json->tokens[i].type == 0)
            typeToStr = "JSMN_UNDEFINED";
        else if (json->tokens[i].type == 1)
            typeToStr = "JSMN_OBJECT";
        else if (json->tokens[i].type == 2)
            typeToStr = "JSMN_ARRAY";
        else if (json->tokens[i].type == 3)
            typeToStr = "JSMN_STRING";
        else
            typeToStr = "JSMN_PRIMITIVE";
        printf("[%d] %s (size = %d, %d~%d, %s) \n", i + 1, json->tokens[i].string, json->tokens[i].size, json->tokens[i].start, json->tokens[i].end, typeToStr);
    }
    printf("**********************************************************\n");
}


void makeCompanyTokens(JSON *json, Company *companies, int bigcnt, int *companyCount){
    bool companyInfoStart = false;
    *companyCount=0;
    for(int i = 0; i<bigcnt; i++){
        // printf("%s, %d \r\n", json->tokens[i].string, json->tokens[i].size);
        // printf("%d of %d \r\n", i, bigcnt);

        if(!strcmp(json->tokens[i].string, "company information")){
            //when token String equals company info we start saving the information
            companyInfoStart = true;
        }
        //read and save the info
        if(companyInfoStart){
            if(!strcmp(json->tokens[i].string, "name")){
                companies[*companyCount].name = json->tokens[i+1].string;
                // printf("\r\n\r\ncmpCnt %d\r\n", *companyCount);

                // printf("Name: %s \r\n", companies[*companyCount].name);
                
            }else if(!strcmp(json->tokens[i].string, "size")){
                if(!strcmp(json->tokens[i+1].string, "Large")){
                    companies[*companyCount].size = LARGE;
                }else if(!strcmp(json->tokens[i+1].string, "Medium")){
                    companies[*companyCount].size = MEDIUM;
                }else if(!strcmp(json->tokens[i+1].string, "Small")){
                    companies[*companyCount].size = SMALL;
                }else if(!strcmp(json->tokens[i+1].string, "Startup")){
                    companies[*companyCount].size = STARTUP;
                }

            }else if(!strcmp(json->tokens[i].string, "salary")){
                companies[*companyCount].salary = atoi(json->tokens[i+1].string);


            }else if(!strcmp(json->tokens[i].string, "coding Test")){
                companies[*companyCount].coding = json->tokens[i+1].string;

            }else if(!strcmp(json->tokens[i].string, "location")){
                companies[*companyCount].location = json->tokens[i+1].string;


            }else if(!strcmp(json->tokens[i].string, "recruiting")){
                companies[*companyCount].recruitNum = atoi(json->tokens[i+1].string);

            }else if(!strcmp(json->tokens[i].string, "positions")){
                int positionCount = json->tokens[i+1].size;
                companies[*companyCount].positionCount = positionCount;
                // printf("position count %d \r\n",companies[*companyCount].positionCount);
                
                for(int j=0; j<positionCount; j++){
                    strcpy(companies[*companyCount].positions[j],json->tokens[i+2+j].string);
                    // printf("%d, %s \r\n", j,companies[*companyCount].positions[j]);
                    // printf("%s \r\n", json->tokens[i+2+j].string);
                        // i++;

                }


                *companyCount+=1;//positions is the last info of a company that appears
                //so after reading this we increment the value
            }
                            // i++;

        }
    }

}

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

        for(int j=0; j<companies[i].positionCount; j++){
            printf(" %d. %s \r\n", j+1,companies[i].positions[j]);
        }
    }
    printf("**********************************************************\n");
}


void searchByName(Company *companies, int count){
    char name[100];
    char *sizeToStr;

    printf("Enter a company name: ");
    scanf("%s", name);

    printf("%d",(int)strlen(name));

    printf("Results:");

    for (int i = 0; i < count; i++) {
    printf("%s",companies[i].name);

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