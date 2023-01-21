#include <stdlib.h>
#include "stack.h"
#include "err.h"

stack_T* stackInit(){
    stack_T *stack = malloc(sizeof(stack_T));
    if(!stack){
        errMsg(INTERNAL, "Stack initialization failure");
    }    
    stack->bottom = NULL;
    stack->top = NULL;
    return stack;
}

void stackPush(stack_T *stack, token_type tok){
    stack_item *item = malloc(sizeof(stack_item));
    item->tokenType = tok;

    if(stack->top == NULL && stack->bottom == NULL){
        item->next = NULL;
        item->prev = NULL;
        stack->top = item;
        stack->bottom = item;
        
        
    }
    else{
        stack->top->prev = item;
        item->next = stack->top;
        stack->top = item;
    }

}

void stackPop(stack_T *stack){
    
    if(stack->top != NULL){
        stack_item *item = stack->top;
        stack->top = item->next;
        if(stack->top != NULL){
            stack->top->prev = NULL;
        }
        free(item);
    }

}