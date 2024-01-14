#include "fichier.h"
#include "exprsimple.h"
#include "exprrestant.h"

int Expr(struct element_token_valeur ** element_token){

    int valider =1;
    // si on a pas un IDENT, (, character, ENTIER, CARACTERE, true, false, null, not, -
    if ((*element_token)->tokenCodageId != 53 && (*element_token)->tokenCodageId != 20 && (*element_token)->tokenCodageId != 47 && (*element_token)->tokenCodageId != 54 && (*element_token)->tokenCodageId != 56 && (*element_token)->tokenCodageId != 57 && (*element_token)->tokenCodageId != 61 && (*element_token)->tokenCodageId != 19 && (*element_token)->tokenCodageId != 22 && (*element_token)->tokenCodageId != 39){
            printf(GREEN"Erreur : il faut un ident, un (, un character, un entier, un caractere, un true, un false, un null, un not ou un - \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
    }
    // EXPR -> EXPRSIMPLE EXPRRESTANT .
    // Appel de la fonction Exprsimple
    valider = Exprsimple(element_token);
    if (valider == -1){
        return -1;
    }

    // Appel de la fonction Exprrestant
    valider = Exprrestant(element_token);
    if (valider == -1){
        return -1;
    }
    return valider;
}