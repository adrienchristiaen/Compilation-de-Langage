#include "fichier.h"
#include "expracces.h"
#include "expr.h"


int Exprsimple(struct element_token_valeur * element_token){
    int valider =1;
    // si on a pas un IDENT, (, character, ENTIER, CARACTERE, true, false, null, not, -
    if (element_token->tokenCodageId != 53 && element_token->tokenCodageId != 20 && element_token->tokenCodageId != 47 && element_token->tokenCodageId != 54 && element_token->tokenCodageId != 56 && element_token->tokenCodageId != 57 && element_token->tokenCodageId != 61 && element_token->tokenCodageId != 19 && element_token->tokenCodageId != 22 && element_token->tokenCodageId != 39){
            printf(GREEN"Erreur : il faut un ident, un (, un character, un entier, un caractere, un true, un false, un null, un not ou un - \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
    }
    //EXPRSIMPLE -> ENTIER .
    if (element_token->tokenCodageId == 54){
        return 1;
    }
    //EXPRSIMPLE -> CARACTERE .
    if (element_token->tokenCodageId == 56){
        return 1;
    }
    //EXPRSIMPLE -> true .
    if (element_token->tokenCodageId == 57){
        return 1;
    }
    //EXPRSIMPLE -> false .
    if (element_token->tokenCodageId == 61){
        return 1;
    }
    //EXPRSIMPLE -> null .
    if (element_token->tokenCodageId == 19){
        return 1;
    }
    // EXPRSIMPLE -> ( EXPR ) 
    if (element_token->tokenCodageId == 20){
        element_token = element_token->next;
        // Appel de la fonction Expr
        valider = Expr(element_token);
        if (valider == -1){
            return -1;
        }
        // )
        if (element_token->tokenCodageId != 21){
            printf(GREEN"Erreur : il faut un ) \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        return 1;
    }
    // EXPRSIMPLE -> not EXPRSIMPLE
    if (element_token->tokenCodageId == 22){
        element_token = element_token->next;
        // Appel de la fonction Exprsimple
        int valider = Exprsimple(element_token);
        if (valider == -1){
            return -1;
        }
        return 1;
    }
    // EXPRSIMPLE -> - EXPRSIMPLE
    if (element_token->tokenCodageId == 39){
        element_token = element_token->next;
        // Appel de la fonction Exprsimple
        int valider = Exprsimple(element_token);
        if (valider == -1){
            return -1;
        }
        return 1;
    }
    // EXPRSIMPLE -> IDENT EXPRACCES
    if (element_token->tokenCodageId == 53){
        element_token = element_token->next;
        // Appel de la fonction Expracces
        int valider = Expracces(element_token);
        if (valider == -1){
            return -1;
        }
        return 1;
    }
    // EXPRSIMPLE -> character ‘ val ( EXPR )
    if (element_token->tokenCodageId == 47){
        element_token = element_token->next;
        // '
        if (element_token->tokenCodageId != 58){
            printf(GREEN"Erreur : il faut un ' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        // val
        if (element_token->tokenCodageId != 62){
            printf(GREEN"Erreur : il faut un entier \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        // (
        if (element_token->tokenCodageId != 20){
            printf(GREEN"Erreur : il faut un ( \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        // Appel de la fonction Expr
        valider = Expr(element_token);
        // )
        if (element_token->tokenCodageId != 21){
            printf(GREEN"Erreur : il faut un ) \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        return 1;
    }
    return valider;
}