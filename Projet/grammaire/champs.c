#include "fichier.h"
#include "type.h"


int Champs(struct element_token_valeur ** element_token){
    int valider = 1;
    // CHAMPS -> IDENTPLUSVIRGULE ':' TYPE ';'
    int a=0; // a =1 si on a un ident et 0 si ,
    
    while ((*element_token)->tokenCodageId==53 || (*element_token)->tokenCodageId==5){
        if ((*element_token)->tokenCodageId==53 && a==0){
            a=1;
            (*element_token) = (*element_token)->next;
        }
        else if ((*element_token)->tokenCodageId==5 && a==1){
            a=0;
            (*element_token) = (*element_token)->next;
        }
        else{
            printf(GREEN"Erreur : il faut un ident ou une virgule \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
    }
    if (a==0){
        printf(GREEN"Erreur : il faut un ident  \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;
    }
    if ((*element_token)->tokenCodageId!=10){
        printf(GREEN"Erreur : il faut un ':' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;
    }
    (*element_token) = (*element_token)->next;
    valider = Type(element_token);
    if (valider == -1){
        return -1;
    }

    if ((*element_token)->tokenCodageId!=5){
        printf(GREEN"Erreur : il faut un ';' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        
        return -1;
    }
    (*element_token) = (*element_token)->next;
    return valider;
}