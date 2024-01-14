#include "fichier.h"
#include "champs.h"
#include "champsplus.h"

int Champsplus(struct element_token_valeur ** element_token){
    int valider = 1;
    // CHAMPSPLUS -> CHAMPS CHAMPSPLUS2
    if ((*element_token)->tokenCodageId==53){
        valider = Champs(element_token);
        if (valider==-1){
            return -1;
        }
        valider = Champsplus(element_token);
        if (valider==-1){
            return -1;
        }
        
       
    }
    return valider;
}