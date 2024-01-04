#include "fichier.h"
#include "parampluspointvirgule.h"

int Paramsinterro(struct element_token_valeur * element_token){
    int valider =1;
    // si ce n'est pas un return ou ( alors on return -1
    if (element_token->tokenCodageId != 14 && element_token->tokenCodageId != 20){
        printf(GREEN"Erreur : il faut un return ou un ( \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;  
    }
    // si c'est un return alors Paramsinterro -> epsilon
    else if (element_token->tokenCodageId == 14){
        return valider;
    }
    else if (element_token->tokenCodageId==20){
        element_token = element_token->next;
        // changer l'adresse de element_token
        if (element_token->tokenCodageId != 53){
            printf(GREEN"Erreur : il faut un ident \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        else {
        valider = Parampluspointvirgule(element_token);
        }
    }
    return valider;
}