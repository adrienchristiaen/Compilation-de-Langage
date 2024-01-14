#include "fichier.h"

int Operateurter(struct element_token_valeur ** element_token){
    int valider = 1;
    // OPERATEURTER -> else 
    if ((*element_token)->tokenCodageId == 27){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    return valider;
}