#include "err.h"
#include <stdio.h>
#include <stdlib.h>
void errMsg(err_e code, char *message){
    fprintf(stderr, "%s",message);
    exit(code);
}