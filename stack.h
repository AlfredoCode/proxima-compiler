#include "lexer.h"

typedef struct stackItem{
    struct stackItem *next;
    struct stackItem *prev;
    token_type tokenType;
}stack_item;

typedef struct stack{
    stack_item *top;
    stack_item *bottom;
}stack_T;


stack_T* stackInit();
void stackPush(stack_T *stack, token_type tok);
void stackPop(stack_T *stack);