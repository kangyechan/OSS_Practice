#include "json.h"

int main(int argc, char **argv) {
    int filesize = 0;
    char *fileName;
    char *doc;
    int bigcnt = 0; //total count including objects in value.
    int selectMenu;

    JSON json = {0};

    while(selectMenu != 4) {
        printf("\nHello!! Welcome to the world of smart refrigerators.\n");
        printf("Select one of the menus below :)\n");
        printf("************* Smart Refrigerator Application *************\n");
        printf("*                                                        *\n");
        printf("*    1.        Current Refrigerator Status.              *\n");
        printf("*    2.                Add new food.                     *\n");
        printf("*    3.       Check recipes and ingredients.             *\n");
        printf("*    4.        Close the refrigerator door.              *\n");
        printf("*                                                        *\n");
        printf("**********************************************************\n");
        printf("your select : ");
        scanf("%d", &selectMenu);

        switch (selectMenu) {
        case 1:
            fileName = "fridge.json";
            doc = readfile(fileName, &filesize); // 파일 읽음
            fileCheck(fileName, doc); // 파일 내용 없으면 에러
            json_parse(doc, filesize, &json, &bigcnt); // 파서 시작
            printResult(&json, bigcnt); // 파서 출력
            makeFoodToken();            // 파서결과를 Food Array에 저장
            freeJson(&json, bigcnt); // 토큰 free
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            printf("OK. Bye! :)\n");
            break;
        default:
            break;
        }
    }

    return 0;
}
