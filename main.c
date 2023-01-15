#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]){
    token_t *tok = malloc(sizeof(token_t));
    while(1){
        if(getToken(tok)){
            printf("Token type: %d, token attribute: %s\n", tok->type, tok->attribute);
        }   
    }
    
    return 0;
}
