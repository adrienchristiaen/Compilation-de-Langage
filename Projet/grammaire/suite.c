#include "fichier.h"
#include "expr.h"

int Suite(struct element_token_valeur ** element_token){
    int valider =1;

    
    //SUITE ->  .

    // SUITE -> ':=' EXPR  ';' .  
    // :=
    if ((*element_token)->tokenCodageId == 11){(*element_token) = (*element_token)->next;
    // EXPR
    valider = Expr(element_token);
    if (valider == -1){
        return -1;
    }
    (*element_token) = (*element_token)->next;
    
    }
    return valider;
}
