#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

typedef enum{FALSE, TRUE} boolean;
// Les mots clés de notre langage
const char* keyword_token [] = {"if", "else", "for", "while", "int", "float", "string"};
// Les symboles de notre langage
const char symbole_token[] = {'*', '/', '+', '-', '=', '>', '<', '(', ')', '{', '}', ';', ','};
// nom des tokens
typedef enum{ 
    //keyword token
    IF_TOKEN, ELSE_TOKEN, FOR_TOKEN, WHILE_TOKEN, INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN,
    // symbole token
PLUS_TOKEN, MINUS_TOKEN, DIV_TOKEN, STAR_TOKEN, COMMA_TOKEN, SEMICOLON_TOKEN, OPEN_BRACE_TOKEN, CLOSE_BRACE_TOKEN, 
OPEN_PARENS_TOKEN, CLOSE_PARENS_TOKEN, ASSIGNMENT_TOKEN, GT_TOKEN, LT_TOKEN, OP_EQ_TOKEN, OP_GE_TOKEN, OP_LE_TOKEN,
//other token
ID_TOKEN, INT_VAL_TOKEN, FLOAT_VAL_TOKEN, STRING_VAL_TOKEN, EOF_TOKEN, ERROR_TOKEN

} token_type;
