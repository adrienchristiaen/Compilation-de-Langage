#include "fichier.h"
#include "expr.h"
#include "instrplus.h"

int Boucle1(struct element_token_valeur ** element_token){
    int valider =1 ;
    // BOUCLE1 ->  elsif EXPR then INSTRPLUS  BOUCLE1
    
    if ((*element_token)->tokenCodageId == 26){
        (*element_token) = (*element_token)->next;
    // elsif
    if ((*element_token)->tokenCodageId != 26){
        printf(GREEN"Erreur : il faut un 'elsif' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;
    }
    // EXPR
    (*element_token) = (*element_token)->next;
    valider = Expr(element_token);
    if (valider == -1){
        return -1;
    }
    // then
    if ((*element_token)->tokenCodageId != 27){
        printf(GREEN"Erreur : il faut un 'then' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;
    }
    // INSTRPLUS
    (*element_token) = (*element_token)->next;
    valider = Instrplus(element_token);
    if (valider == -1){
        return -1;
    }
    
    if ((*element_token)->tokenCodageId == 26){
        valider = Boucle1(element_token);
        if (valider == -1){
            return -1;
        }
    }
    
    }
    
return valider;
}