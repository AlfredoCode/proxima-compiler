#include "lexer.h"


int checkToken(token_t **token);


int statList(); // Starts the parsing
int rightOperand();
int checkOperator(int type);
int checkIfFunctionCall();
int functionCallParams();
