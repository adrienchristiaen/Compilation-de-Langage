#include "fichier.h"

int Type(struct element_token_valeur * element_token){
    int valider=1;

    if (element_token->tokenCodageId != 53 && element_token->tokenCodageId != 47 && 
    element_token->tokenCodageId != 48 && 
    element_token->tokenCodageId != 49 && 
    element_token->tokenCodageId != 50){
        printf(GREEN"Erreur : il faut un type \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;  
    }
    element_token = element_token->next;
    return valider;
}