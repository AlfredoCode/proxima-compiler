#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void bufferHandler(char** buffer, int* index, char input){
    char* newBuffer = realloc(*buffer, sizeof(*buffer) * sizeof(char));
   
    if(!newBuffer){
        fprintf(stderr,"Malloc failure\n");
        exit(1);
    }
    *buffer = newBuffer;
    (*buffer)[*index] = input;
    (*index)++;
}


bool getToken(token_t *token){
    STATES state = BEGIN_S;
    int input;
    int index = 0;
    char *buffer = NULL;
    
    token->attribute = NULL;
    
    

    while(true){
        input = getchar();

        switch(state){
            case BEGIN_S:
                if(isalpha(input)){
                    state = ID_S;
                    bufferHandler(&buffer, &index, input);
                    continue; 
                }
                else if(input == '='){
                    bufferHandler(&buffer, &index, input);
                    token->type = ASSIG_T;
                    return true;
                }
                else if(isdigit(input)){
                    state = INT_S;
                    bufferHandler(&buffer, &index, input);
                    continue; 

                }
                return false;
            case ID_S:  // Trying to read IDENTIFIER
                if(isalpha(input) || isdigit(input) || input == '_'){ // TODO add numbers and other characters
                    bufferHandler(&buffer, &index, input);
                    continue; 
                }
                else{
                    buffer[index] = '\0';
                    token->attribute = buffer;
                    token->type = ID_T;
                    return true;
                }
            case INT_S:
                if(isdigit(input)){
                    bufferHandler(&buffer, &index, input);
                    continue;   
                }
                else if(input == '.'){
                    bufferHandler(&buffer, &index, input);
                    state = FLOAT_S;
                    continue;
                }
                else{
                    buffer[index] = '\0';
                    token->attribute = buffer;
                    token->type = INT_T;
                    return true; 
                }
            case FLOAT_S:
                if(isdigit(input)){
                    bufferHandler(&buffer, &index, input);
                    continue;   
                } 
                else{
                    buffer[index] = '\0';
                    token->attribute = buffer;
                    token->type = FLOAT_T;
                    return true; 
                }
        }
    }
}