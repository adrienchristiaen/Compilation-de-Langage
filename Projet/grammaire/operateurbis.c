#include "fichier.h"
#include "operateurter.h"

int Operateurbis(struct element_token_valeur *element_token){
    int valider = 1;
    // OPERATEURBIS -> then
    if (element_token->tokenCodageId == 44){
        element_token = element_token->next;
        return valider;
    }
    // OPERATEURBIS -> or OPERATEURTER 
    else if (element_token->tokenCodageId == 45){
        element_token = element_token->next;
        valider = Operateurter(element_token);
        if (valider == -1){
            return -1;
        }
       
    }
    return valider;
}