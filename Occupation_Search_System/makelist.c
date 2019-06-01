#include "json.h"

void makeCompanyTokens(JSON *json, Company *companies, int bigcnt, int *companyCount){
    bool companyInfoStart = false;
    *companyCount = 0;
    for(int i = 0; i < bigcnt; i++){
        if(!strcmp(json->tokens[i].string, "company information")){
            //when token String equals company info we start saving the information
            companyInfoStart = true;
        }
        //read and save the info
        if(companyInfoStart){
            if(!strcmp(json->tokens[i].string, "name")){
                
                strcpy(companies[*companyCount].name,json->tokens[i+1].string);

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
                strcpy(companies[*companyCount].coding , json->tokens[i+1].string);

            }else if(!strcmp(json->tokens[i].string, "location")){
                strcpy(companies[*companyCount].location , json->tokens[i+1].string);

            }else if(!strcmp(json->tokens[i].string, "recruiting")){
                companies[*companyCount].recruitNum = atoi(json->tokens[i+1].string);

            }else if(!strcmp(json->tokens[i].string, "city")){
                strcpy(companies[*companyCount].city , json->tokens[i+1].string);

            }else if(!strcmp(json->tokens[i].string, "positions")){
                int positionCount = json->tokens[i+1].size;
                companies[*companyCount].positionCount = positionCount;

                for(int j=0; j<positionCount; j++){
                    strcpy(companies[*companyCount].positions[j], json->tokens[i+2+j].string);

                }
                *companyCount+=1;//positions is the last info of a company that appears
                //so after reading this we increment the value
            }
        }
    }
}

void makeGraduateSchoolToken(JSON *json, School *schools, int bigcnt, int *schoolCount){
    bool schoolInfoStart = false;
        *schoolCount = 0;
        for(int i = 0; i < bigcnt; i++){
            if(!strcmp(json->tokens[i].string, "graduate school")){
                //when token String equals company info we start saving the information
                schoolInfoStart = true;
            }
            //read and save the info
            if(schoolInfoStart){
                if(!strcmp(json->tokens[i].string, "name")){
                    schools[*schoolCount].name = json->tokens[i+1].string;

                }else if(!strcmp(json->tokens[i].string, "location")){
                    strcpy(schools[*schoolCount].location , json->tokens[i+1].string);

                }else if(!strcmp(json->tokens[i].string, "type")){
                    int typeCount = json->tokens[i+1].size;
                    schools[*schoolCount].typeCount = typeCount;

                    for(int j = 0; j<typeCount; j++){
                        strcpy(schools[*schoolCount].type[j], json->tokens[i+2+j].string);

                    }
                    *schoolCount+=1;//positions is the last info of a company that appears
                    //so after reading this we increment the value
                }
            }
        }
    }