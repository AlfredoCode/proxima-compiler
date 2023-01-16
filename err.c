#include "err.h"
#include <stdio.h>
#include <stdlib.h>
void errMsg(err_e code, char *message){
    fprintf(stderr, "%s\n",message);
    exit(code);
}

void warningMsg(const char *message){
    fprintf(stderr, "### WARNING ### %s\n", message);
}