#include "fichier.h"
#include "operateurbis.h"

int Operateur(struct element_token_valeur ** element_token){
    int valider=1;
    // OPERATEUR -> '=' 
    if ((*element_token)->tokenCodageId==32){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '/='
    else if ((*element_token)->tokenCodageId==33){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '<'
    else if ((*element_token)->tokenCodageId==34){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '<='
    else if ((*element_token)->tokenCodageId==35){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '>'
    else if ((*element_token)->tokenCodageId==36){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '>='
    else if ((*element_token)->tokenCodageId==37){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '+'
    else if ((*element_token)->tokenCodageId==38){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '-'
    else if ((*element_token)->tokenCodageId==39){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '*'
    else if ((*element_token)->tokenCodageId==40){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> '/'
    else if ((*element_token)->tokenCodageId==41){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> 'rem'
    else if ((*element_token)->tokenCodageId==42){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // OPERATEUR -> and OPERATEURBIS
    else if ((*element_token)->tokenCodageId==43){
        (*element_token) = (*element_token)->next;
        valider = Operateurbis(element_token);
        if (valider == -1){
            return -1;
        }
        return valider;
    }
    return valider;
}