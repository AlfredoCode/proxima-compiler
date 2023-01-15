#include <stdbool.h>
/**
 * @brief token_type is an enumeration of possible token types such as integer, float, identifier etc
 * 
 */
typedef enum{
    ID_T,
    INT_T,
    FLOAT_T,
    STRING_T,
    ASSIG_T,
}token_type;

typedef enum{
    BEGIN_S,
    ID_S,
    INT_S,
    FLOAT_S,
    STRING_S,
}STATES;

typedef struct token{
    char* attribute;    // FOR NAME OF IDs
    char* kw;   // NAME OF KEYWORD
    token_type type;    // TOKEN TYPE

}token_t;

bool getToken(token_t *token);
void bufferHandler(char** buffer, int* index, char input);