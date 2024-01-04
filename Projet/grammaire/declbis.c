#include "fichier.h"
#include "declter.h"

int Declbis(struct element_token_valeur * element_token){
    int valider = 1;
    // DECLBIS ->  ;
    if (element_token->tokenCodageId == 5){
        element_token = element_token->next;
        return valider;
    }
    // DECLBIS -> is DECLTER
    if (element_token->tokenCodageId == 28){
        element_token = element_token->next;
        valider = Declter(element_token);
        if (valider == -1){
            return -1;
        }
    }
    return valider;
}