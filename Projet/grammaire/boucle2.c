#include "fichier.h"
#include "instrplus.h"

int Boucle2 ( struct element_token_valeur * element_token) {
    int valider ;
    // BOUCLE2 -> ( else INSTRPLUS  )
    if (element_token->tokenCodageId != 20){
        printf(GREEN"Erreur : il faut un '(' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }
    if (element_token->tokenCodageId != 27){
        printf(GREEN"Erreur : il faut un 'else' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }

    element_token = element_token->next;
    // INSTRPLUS
    element_token = element_token->next;
    valider = Instrplus(element_token);
    if (valider == -1){
        return -1;
    }
    
    // )
    if (element_token->tokenCodageId != 21){
        printf(GREEN"Erreur : il faut un ')' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }
    return valider;
}