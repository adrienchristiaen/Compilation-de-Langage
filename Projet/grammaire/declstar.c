#include "fichier.h"
#include "decl.h"
int Declstar(struct element_token_valeur * element_token){
    int valider =1;

    // si on a pas de type, fonction, procédure, ident ou begin alors on return -1
    if (element_token->tokenCodageId != 6 && element_token->tokenCodageId != 13 && element_token->tokenCodageId != 3 && element_token->tokenCodageId != 53 && element_token->tokenCodageId != 12){
        printf(GREEN"Erreur : il faut un type, une fonction, une procedure, un ident ou un begin \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;  
    }
    // Declstar -> epsilon si on a un begin
    else if (element_token->tokenCodageId == 12){
        return valider;
    } 
    // Declstar -> DECL Declstar
    else {
        valider = Decl(element_token);
    }
 
    return valider;

}