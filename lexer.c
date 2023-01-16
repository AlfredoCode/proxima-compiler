#include "lexer.h"
#include "keywords.h"

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
    
    bool separator = false; // Can be useful for managing great numbers such as 42_000_000

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
                else if(isspace(input) || input == '\n' ){
                    continue;
                }
                else if(input == ':'){
                    state = ASSIG_S;
                    continue;
                }
                else if(isdigit(input)){
                    state = INT_S;
                    bufferHandler(&buffer, &index, input);
                    continue; 
                }
                else if(input == ';'){
                    token->type = SEMICOL_T;    // ;
                    return true;
                }
                else if(input == EOF){
                    token->type = EOF_T;    // End Of File
                    return true;
                }
                else if(input == '+'){
                    state = ADD_S;
                    continue;
                }
                else if(input == '-'){
                    state = SUB_S;
                    continue;
                }
                else if(input == '*'){
                    state = MULTI_S;
                    continue;
                }
                else if(input == '/'){
                    state = DIV_S;
                    continue;
                }
                else if(input == '('){
                    token->type = L_PAR_T;  // '('
                    return true;
                }
                else if(input == ')'){
                    token->type = R_PAR_T;  // ')'
                    return true;
                }
                else if(input == '<'){
                    state = LOWER_S;
                    continue;
                }
                else if(input == '>'){
                    state = GREATER_S;
                    continue;
                }
                return false;
        
            case ID_S:  // Trying to read IDENTIFIER
                if(isalpha(input) || isdigit(input) || input == '_'){ // TODO add numbers and other characters
                    bufferHandler(&buffer, &index, input);
                    continue; 
                }
                else{
                    ungetc(input, stdin);
                    buffer[index] = '\0';
                    if(isKeyword(buffer)){
                        token->type = KW_T;
                        token->kw = buffer;
                        return true;
                    }
                    token->attribute = buffer;
                    token->type = ID_T;     // Identifier
                    return true;
                }
            
            case INT_S:
                if(isdigit(input) || input == '_'){
                    if(isdigit(input)){
                        separator = false;
                        bufferHandler(&buffer, &index, input);
                        continue;
                    }
                    separator = true;
                    continue;   
                }
                else if(input == '.'){
                    bufferHandler(&buffer, &index, input);
                    state = FLOAT_S;
                    continue;
                }
                else{
                    if(separator){
                        return false;   // We do not want something like 42000_
                    }
                    ungetc(input, stdin);
                    buffer[index] = '\0';
                    token->attribute = buffer;
                    token->type = INT_T;    // Integer number
                    return true; 
                }
            
            case FLOAT_S:
                if(isdigit(input)){
                    bufferHandler(&buffer, &index, input);
                    continue;   
                } 
                else{
                    ungetc(input, stdin);
                    buffer[index] = '\0';
                    token->attribute = buffer;
                    token->type = FLOAT_T;  // Float number
                    return true; 
                }
            case ASSIG_S:
                if(input == ':'){
                    token->type = EQUALS_T; // ::
                }
                else{
                    token->type = ASSIG_T;  // :
                    ungetc(input, stdin);
                }
                return true;
            case ADD_S:
                if(input == ':'){
                    token->type = ADD_ASSIGN_T; // +:
                }
                else{
                    ungetc(input, stdin);
                    token->type = ADD_T;    // '+'
                }
                return true;
            case SUB_S:
                if(input == ':'){
                    token->type = SUB_ASSIGN_T; // "-:"
                }
                else{
                    ungetc(input, stdin);
                    token->type = SUB_T;    // '-'
                }
                return true;
            case MULTI_S:
                if(input == ':'){
                    token->type = MULTI_ASSIGN_T; // "*:"
                }
                else if(input ==  '*'){
                    token->type = POW_T;    // "**"
                }
                else{
                    ungetc(input, stdin);
                    token->type = MULTI_T;  // '*'
                }
                return true;
            case DIV_S:
                if(input == ':'){
                    token->type = DIV_ASSIGN_T; // "/:"
                }
                else{
                    ungetc(input, stdin);
                    token->type = DIV_T; // '/'
                }
                return true;
            case LOWER_S:
                if(input == ':'){
                    token->type = LOWER_EQ_T;   // <:
                }
                else{
                    ungetc(input, stdin);
                    token->type = LOWER_T;  // <
                }
                return true;
            
            default: return false;
        }
    }
}