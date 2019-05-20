#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TOKEN_COUNT 50

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
             while(doc[pos+1]!= '"'){ // increase pos until it meets "
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

             
             case '[':
             
             json->tokens[tokenIndex].type = ARRAY; // token.type is STRING
             int arraytokenIndex = tokenIndex;//save tokenIndex for array we found             
             s = pos;  // the token starts at '['
             json->tokens[arraytokenIndex].start = s;  // token.start = s
             int size =0;
             while(doc[pos]!= ']'){ // increase pos until it meets "
                pos++;

                if(doc[pos]=='"'){
                    tokenIndex++; //increase tokenIndex for element found insdie array
                    size++; //increase size for each element found. This is array size.
                    json->tokens[tokenIndex].type = STRING; // token.type is STRING
                    s = pos+1;  // the word starts after "
                    json->tokens[tokenIndex].start = s;  // token.start = s
                    while(doc[pos+1]!= '"'){ // increase pos until it meets "
                        pos++;
                    }

                    e = ++pos; // the word ends when doc[pos] meets ". (includes last ")
                    json->tokens[tokenIndex].end = e; // token.end = e
                    
                    json->tokens[tokenIndex].size=0; //0 because it is a value

                    //put doc[s]~doc[e+1] in token.string
                    json->tokens[tokenIndex].string = (char *)malloc(e-s +1);
                    memset(json->tokens[tokenIndex].string, 0, e-s + 1);
                    memcpy(json->tokens[tokenIndex].string, doc+s, e-s);
                    //  printf("[array element] %s (size = %d, %d~%d, %u) \n", json->tokens[tokenIndex].string, json->tokens[tokenIndex].size, json->tokens[tokenIndex].start, json->tokens[tokenIndex].end, json->tokens[tokenIndex].type);
                    pos++;
                }


             }//array ended 
                tokenIndex++; //increase tokenIndex because we have found all elements in array. Prepare for next token.
                json->tokens[arraytokenIndex].end = pos;
                json->tokens[arraytokenIndex].size = size;
                //put doc[s]~doc[e+1] in token.string for the array
                json->tokens[arraytokenIndex].string = (char *)malloc(pos-json->tokens[arraytokenIndex].start + 1);
                memset(json->tokens[arraytokenIndex].string, 0, pos-json->tokens[arraytokenIndex].start + 1);
                memcpy(json->tokens[arraytokenIndex].string, doc+json->tokens[arraytokenIndex].start, pos-json->tokens[arraytokenIndex].start+1);
                break;
            case '-': case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 't': case 'f': case 'n':
                json->tokens[tokenIndex].type = PRIMITIVE;
                s = pos;
                json->tokens[tokenIndex].start = s;
                while(doc[pos+1] != ',') { // ','만날때까지
                    if(doc[pos+1] == '}') { // 만약 ','를 만나지 않았는데 '}'를 만난다면 마지막이 개행문자 제거를 위해 pos--
                        pos--; 
                        break;
                    } else pos++;
                }
                e = ++pos; // the word ends when doc[pos] meets ',' or NULL
                json->tokens[tokenIndex].end = e;
                json->tokens[tokenIndex].size = 0;
                json->tokens[tokenIndex].string = (char *)malloc(e-s+1);
                memset(json->tokens[tokenIndex].string, 0, e-s+1);
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
