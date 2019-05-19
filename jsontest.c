#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
    const int maxBufLen = 255;
    char buffer[maxBufLen];
    const int maxDataLen = 512;
    char data[maxDataLen];
    FILE *fp;

    //implement: ./a.out ./example.json 
    fp = fopen("argv[1]", "r");    

    int length = 0;
    while (fscanf(fp, "%s", buffer) > 0)
    {
        if ((length + strlen(buffer) + 1)>= maxDataLen) break;
        strncpy(&data[length], buffer, strlen(buffer));
        length += strlen(buffer) + 1;
        data[length-1] = ' ';
    }    
    printf("%s", data);

    fclose(fp);


}