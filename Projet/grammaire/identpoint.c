#include "fichier.h"

int Identpoint(struct element_token_valeur * element_token){
    int valider=1;
    if (element_token->tokenCodageId==46){
        element_token = element_token->next;
        if (element_token->tokenCodageId != 53){
            printf(GREEN"Erreur : il faut un ident \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        return Identpoint(element_token);
        
    }
    return valider;
}