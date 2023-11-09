#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>


// Les mots clés de notre langage
const char* keyword_token[] = {"if", "else", "elsif", "then", "end", "loop", "while", "for"} ;
// Les mots clés de notre langage qui doivent être gardés et on enlevera ceux qui ne sont pas dans cette liste, en regardardant lettre par lettre
const int keyword_token_keep[] = {1 , 1, 1, 1, 1, 1, 1, 1} ;
const int keyword_token_index[] = {1, 2, 3, 4, 5, 6, 7, 8} ;
// Les types de données de notre langage
const char* type_token[] = { "integer", "float", "string", "char", "boolean" } ;
const int type_token_keep[] = {1 , 1, 1, 1, 1} ;
const int type_token_index[] = {9, 10, 11, 12, 13} ;
// Les déclarations de notre langage
const char* declaration_token[] = { "declare", "function", "procedure", "is", "begin", "end", "return"} ;
const int declaration_token_keep[] = {1 , 1, 1, 1, 1, 1, 1} ;
const int declaration_token_index[] = {14, 15, 16, 17, 18, 19, 20} ;
// Les opérateurs de notre langage
const char* operator_token[] = { "+", "-", "*", "/", "mod", "and", "or", "not"} ;
const int operator_token_keep[] = {1 , 1, 1, 1, 1, 1, 1, 1} ;
const int operator_token_index[] = {21, 22, 23, 24, 25, 26, 27, 28} ;
// Les comparaisons de notre langage
const char* comparison_token[] = { "=", "/=", "<", "<=", ">", ">="} ;
const int comparison_token_keep[] = {1 , 1, 1, 1, 1, 1} ;
const int comparison_token_index[] = {29, 30, 31, 32, 33, 34} ;
// Les symboles de ponctuation de notre langage
const char* punctuation_token[] = { ";", ":", ",", "."} ;
const int punctuation_token_keep[] = {1 , 1, 1, 1} ;
const int punctuation_token_index[] = {35, 36, 37, 38} ;
// Les parenthèses et crochets de notre langage
const char* parenthesis_token[] = { "(", ")", "[", "]"} ;
const int parenthesis_token_keep[] = {1 , 1, 1, 1} ;
const int parenthesis_token_index[] = {39, 40, 41, 42} ;
// Les affectations et opérateurs de notre langage
const char* assignment_token[] = { ":=", "+=", "-=", "*=", "/="} ;
const int assignment_token_keep[] = {1 , 1, 1, 1, 1} ;
const int assignment_token_index[] = {43, 44, 45, 46, 47} ;
// Les valeurs littérales de notre langage
const char* literal_token[] = { "integer_literal", "float_literal", "string_literal", "char_literal", "boolean_literal"} ;
const int literal_token_keep[] = {1 , 1, 1, 1, 1} ;
const int literal_token_index[] = {48, 49, 50, 51, 52} ;


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