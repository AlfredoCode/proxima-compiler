typedef enum{
    SUCCESS,
    LEX_ERR,
    SYNTAX,
    INTERNAL
}err_e;

void errMsg(err_e type, char *message);