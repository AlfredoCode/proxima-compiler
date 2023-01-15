#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include "err.h"

int checkToken(token_t** token){
    *token = malloc(sizeof(token_t));
    if(!token){
        errMsg(INTERNAL, "Memory allocation failure\n"); 
    }
    if(!getToken(*token)){
        errMsg(LEX_ERR, "Unexpected Input!\n");
    }
    // printf("Token type: %d, token attribute: %s\n", token->type, token->attribute);
    return 0;
}

int checkOperator(){
    token_t *tok;
    checkToken(&tok);
    
    switch(tok->type){
        case ASSIG_T:
            return SUCCESS;
    }
}

int functionCallParams(){
    return SYNTAX;  // TODO
}

int checkIfFunctionCall(){
    token_t *tok;
    
    checkToken(&tok);   
    switch(tok->type){
        case SEMICOL_T: case L_PAR_T:
            if(tok->type == L_PAR_T){
                functionCallParams();
            }
            return SUCCESS;
        default: 
            errMsg(SYNTAX, "Missing semicol after statement\n");
        
    }
    errMsg(INTERNAL, "Congratulations, you found bug and broke the compiler\n");
}

int rightOperand(){
    token_t *tok;
    checkToken(&tok);  
    
    switch(tok->type){
        case ID_T:
            return checkIfFunctionCall();
            
            
            
        case FLOAT_T:
        case INT_T:
        case STRING_T: 
            return SUCCESS;
    }
}

/**
 * @brief Entry point for parsing
 * 
 * @return SUCCESS if parsing was successful otherwise error
 */
int statList(){
    token_t *tok;
    checkToken(&tok);

    switch(tok->type){
        case ID_T:
            if(checkOperator() == SUCCESS && rightOperand() == SUCCESS){
                
               return statList(); 
                
            }
            errMsg(SYNTAX, "Wrong statement assignment\n");
            
        case FLOAT_T:
        case INT_T:
        case STRING_T:
            return statList(); 
        case EOF_T:
            return SUCCESS;
            

    }
}

