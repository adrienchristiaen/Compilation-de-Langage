#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

extern const char* keyword_token[];
extern const int keyword_token_keep[];
extern const int keyword_token_index[];
extern const char* type_token[];
extern const int type_token_keep[];
extern const int type_token_index[];
extern const char* declaration_token[];
extern const int declaration_token_keep[];
extern const int declaration_token_index[];
extern const char* operator_token[];
extern const int operator_token_keep[];
extern const int operator_token_index[];
extern const char* comparison_token[];
extern const int comparison_token_keep[];
extern const int comparison_token_index[];
extern const char* punctuation_token[];
extern const int punctuation_token_keep[];
extern const int punctuation_token_index[];
extern const char* parenthesis_token[];
extern const int parenthesis_token_keep[];
extern const int parenthesis_token_index[];
extern const char* assignment_token[];
extern const int assignment_token_keep[];
extern const int assignment_token_index[];
extern const char* literal_token[];
extern const int literal_token_keep[];
extern const int literal_token_index[];




typedef enum {
    // Structure de contrôle
    IF_TOKEN, ELSE_TOKEN, ELSIF_TOKEN, THEN_TOKEN, END_TOKEN_1, LOOP_TOKEN, WHILE_TOKEN, FOR_TOKEN, 
    // Types de données
    INTEGER_TOKEN, FLOAT_TOKEN, STRING_TOKEN, CHAR_TOKEN, BOOLEAN_TOKEN, 
    // Déclarations
    DECLARE_TOKEN, FUNCTION_TOKEN, PROCEDURE_TOKEN, IS_TOKEN, BEGIN_TOKEN, END_TOKEN_2, RETURN_TOKEN, 
    // Opérateurs
    PLUS_TOKEN, MINUS_TOKEN, MULTIPLY_TOKEN, DIVIDE_TOKEN, MOD_TOKEN, AND_TOKEN, OR_TOKEN, NOT_TOKEN, 
    // Comparaisons
    EQUAL_TOKEN, NOT_EQUAL_TOKEN, LESS_THAN_TOKEN, LESS_EQUAL_TOKEN, GREATER_THAN_TOKEN, GREATER_EQUAL_TOKEN, 
    // Symboles de ponctuation
    SEMICOLON_TOKEN, COLON_TOKEN, COMMA_TOKEN, DOT_TOKEN, 
    // Parenthèses et crochets
    LEFT_PAREN_TOKEN, RIGHT_PAREN_TOKEN, LEFT_BRACKET_TOKEN, RIGHT_BRACKET_TOKEN, 
    // Affectation et opérateurs
    ASSIGNMENT_TOKEN, ADD_ASSIGNMENT_TOKEN, SUBTRACT_ASSIGNMENT_TOKEN, 
    MULTIPLY_ASSIGNMENT_TOKEN, DIVIDE_ASSIGNMENT_TOKEN, 
    // Identificateurs
    IDENTIFIER_TOKEN,
    // Valeurs littérales
    INTEGER_LITERAL_TOKEN, FLOAT_LITERAL_TOKEN, STRING_LITERAL_TOKEN, CHAR_LITERAL_TOKEN, BOOLEAN_LITERAL_TOKEN, 
    // Fin de fichier
    EOF_TOKEN, 
    // Erreur
    ERROR_TOKEN
} ada_token_type;

#endif // HEADER_H