#include "fichier.h"
#include "champsplus.h"

int Declter(struct element_token_valeur * element_token){
    int valider = 1;
    // DECLTER -> record CHAMPSPLUS end record ';'
    if (element_token->tokenCodageId!= 8){
        printf(GREEN"Erreur : il faut un 'record' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }
    element_token = element_token->next;
    valider = Champsplus(element_token);
    if (valider == -1){
        return -1;
    }
    if (element_token->tokenCodageId != 9){
        printf(GREEN"Erreur : il faut un 'end' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    } 
    element_token = element_token->next;
    if (element_token->tokenCodageId != 8){
        printf(GREEN"Erreur : il faut un 'record' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }
    if (element_token->tokenCodageId != 5){
        printf(GREEN"Erreur : il faut un ';' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }

    return valider;
}