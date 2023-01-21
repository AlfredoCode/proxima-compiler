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
    ASSIG_T,        // :
    EOF_T,          // 5
    SEMICOL_T,
    L_PAR_T,
    R_PAR_T,
    L_BRAC_T,
    R_BRAC_T,       // 10
    ADD_T,
    ADD_ASSIGN_T,
    KW_T,           // KEYWORD
    LOWER_T,
    LOWER_EQ_T,     // 15
    GREATER_T,
    GREATER_EQ_T,
    EQUALS_T,
    SUB_T,
    SUB_ASSIGN_T,   // 20
    DIV_T,
    DIV_ASSIGN_T,
    MULTI_T,
    MULTI_ASSIGN_T,
    POW_T,          // 25

}token_type;

typedef enum{
    BEGIN_S,
    ID_S,
    INT_S,
    FLOAT_S,
    STRING_S,
    ASSIG_S,
    ADD_S,
    SUB_S,
    DIV_S,
    MULTI_S,
    LOWER_S,
    GREATER_S,
}STATES;

typedef struct token{
    char* attribute;    // FOR NAME OF IDs
    char* kw;           // NAME OF KEYWORD
    token_type type;    // TOKEN TYPE

}token_t;

bool getToken(token_t *token);


/**
 * @brief Reallocates the memory for the string buffer
 * 
 * @param buffer current string buffer
 * @param index Position of the character to be pushed in buffer
 * @param input Character to be pushed into buffer
 */
void bufferHandler(char** buffer, int* index, char input);
bool returnHandler(bool type, char** buffer);