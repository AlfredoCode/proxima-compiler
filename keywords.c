#include <string.h>
#include "keywords.h"
/**
 * @brief 2D Array of strings representing keywords, NULL is for terminating the while loop, I do not want to use nested loops.
 * 
 */
const char *keywords[] = {  "if", "elsif", "else", 
                            "func", "loop", "until",
                            "concat", "ret", NULL
                            };

bool isKeyword(const char* input){
    int i = 0;
    while(keywords[i] != NULL){
        if(!strcmp(keywords[i], input)){
            return true;
        }
        i++;
    }
    return false;
}