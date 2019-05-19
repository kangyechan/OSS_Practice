#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum {
    UNDEFINED = 0,
    OBJECT = 1,
    ARRAY = 2,
    STRING =3,
    PRIMITIVE = 4

}type_t;

typedef struct {
    type_t type;
    int start;
    int end;
    int size;
    char *string;
}tok_t;

#define TOKEN_COUNT 50

typedef struct _JSON{
    tok_t tokens[TOKEN_COUNT];
} JSON;

char* readfile(char* filename, int* filesize)
{
    FILE* fp = fopen(filename, "r");

    if (fp ==  NULL){
        printf("WRONG FILENAME\n");
        return NULL;
    }

    int size;
    char* buffer;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp); //current file position
    fseek(fp, 0, SEEK_SET);

    buffer = (char*)malloc(size+1);
    memset(buffer, 0, size+1);

    if(fread(buffer,1, size, fp)<1){
        *filesize = 0;
        free(buffer);
        fclose(fp);
        return NULL;
    }

    *filesize = size;

    fclose(fp);

    return buffer;

}

void json_parse(char *doc, int size, JSON *json, int *b_cnt)
{
    int cnt = 0;
    int pos = 0; //for checking position in doc.
    int e,s; //ending, starting position for each token
    int tokenIndex = 0; //index for token

    while(pos < size)
    {
        switch(doc[pos])
        {
            case '"':
            json->tokens[tokenIndex].type = STRING; // token.type is STRING
            s = pos+1;  // the word starts after "
            json->tokens[tokenIndex].start = s;  // token.start = s
             while(doc[pos+1]!= '"'){ // increase pos while it meets "
                pos++;
             }

             e = ++pos; // the word ends when doc[pos] meets ". (includes last ")
             json->tokens[tokenIndex].end = e; // token.end = e
            
             json->tokens[tokenIndex].size=1; //if : is coming right after "" {size = 1}
             if(doc[pos+1]!=':'){// else {size = 0}
                 json->tokens[tokenIndex].size = 0;
             }

            //put doc[s]~doc[e+1] in token.string
             json->tokens[tokenIndex].string = (char *)malloc(e-s +1);
             memset(json->tokens[tokenIndex].string, 0, e-s + 1);
             memcpy(json->tokens[tokenIndex].string, doc+s, e-s);

             pos++;
             tokenIndex++;

             break;
             
            
            default:
             pos++;
        }
    }
    
    *b_cnt = tokenIndex;    //update bigcnt
}

void freeJson(JSON *json, int bigcnt){
    for (int i = 0; i<bigcnt; i++){
        if (json->tokens[i].type == STRING)
            free(json->tokens[i].string);
    }
}
int main(int argc, char** argv)
{
    int filesize=0;
    char* doc = readfile(argv[1], &filesize);
    int bigcnt=0; //total count including objects in value.

    if(doc == NULL){
        printf("NULL");
        return -1;
    }

    JSON json = {0, };

    json_parse(doc, filesize, &json, &bigcnt);

    //printing
    for(int i = 0; i<bigcnt;i++){
        printf("[%d] %s (size = %d, %d~%d, %u) \n", i+1, json.tokens[i].string, json.tokens[i].size, json.tokens[i].start, json.tokens[i].end, json.tokens[i].type);
    }

    freeJson(&json, bigcnt);

    return 0;
}
