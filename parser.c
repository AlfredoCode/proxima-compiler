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

int checkOperator(int type){
    token_t *tok;
    checkToken(&tok);
    
    switch(tok->type){
        case ASSIG_T:
            if(type == ID_T){
                return SUCCESS;
            }
            errMsg(SYNTAX, "Forbidden assignment\n");
        case SEMICOL_T:
            return SUCCESS;
        case ADD_ASSIGN_T:
            return rightOperand();
        case ADD_T: case SUB_T: case MULTI_T: case DIV_T:
            return rightOperand();
        case R_PAR_T:   // TODO Remove L_PAR from global stack, if stack is empty, then syntax error
            return checkOperator(tok->type);
    }
}

int functionCallParams(){
    return SYNTAX;  // TODO
}


int checkIfFunctionCall(){
    token_t *tok;
    
    checkToken(&tok);   
    switch(tok->type){
        case SEMICOL_T: case L_PAR_T: case R_PAR_T: 
            if(tok->type == L_PAR_T){
                functionCallParams();
            }
            else if(tok->type == R_PAR_T){
                return checkOperator(tok->type);
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
            return checkOperator(tok->type);
        case L_PAR_T:
            return rightOperand();
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
        case FLOAT_T:
        case INT_T:
        case STRING_T:
        case ID_T:
            if(checkOperator(tok->type) == SUCCESS){
                
               return statList(); 
                
            }
            errMsg(SYNTAX, "Wrong statement assignment\n");
        case L_PAR_T: // TODO PUSH L_PAR to global stack of L_PARs and remove each one when ')' occurs, if stack is not empty after parsing, then syntax error
            return statList();
        

        case EOF_T:
            return SUCCESS;
        default: return SYNTAX;
            

    }
}

