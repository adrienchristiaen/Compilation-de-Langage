#include "fichier.h"
#include "expr.h"

int Suite(struct element_token_valeur * element_token){
    int valider =1;

    
    //SUITE ->  .

    if (element_token->tokenCodageId!=20){
        return valider;
    }
    // SUITE -> '(' ':=' EXPR ')' ';' .  

    element_token = element_token->next;
    // :=
    if (element_token->tokenCodageId != 11){
        printf(GREEN"Erreur : il faut un ':=' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }
    element_token = element_token->next;
    // EXPR
    valider = Expr(element_token);
    if (valider == -1){
        return -1;
    }
    // )
    if (element_token->tokenCodageId != 21){
        printf(GREEN"Erreur : il faut un ')' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }
    element_token = element_token->next;
    // ;
    if (element_token->tokenCodageId != 5){
        printf(GREEN"Erreur : il faut un ';' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }
    
    return valider;
}