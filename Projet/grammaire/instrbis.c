#include "fichier.h"
#include "expr.h"
#include "identpoint.h"
#include "exprplusvirgule.h"

int Instrbis(struct element_token_valeur ** element_token){
    
    int valider = 1;
    // INSTRBIS -> ;
    if ((*element_token)->tokenCodageId == 5){
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // INSTRBIS -> ( EXPRPLUSVIRGULE ) ;
    else if ((*element_token)->tokenCodageId == 20){
        (*element_token) = (*element_token)->next;
        valider = Exprplusvirgule(element_token);
        if (valider == -1){
            return -1;
        }
        // )
        if ((*element_token)->tokenCodageId != 21){
            printf(GREEN"Erreur : il faut un ')' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // ;
        if ((*element_token)->tokenCodageId != 5){
            printf(GREEN"Erreur : il faut un ';' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        return valider;
    }
    // INSTRBIS -> IDENTPOINT ':=' EXPR ';' 
    else if ((*element_token)->tokenCodageId == 11){
        

        (*element_token) = (*element_token)->next;

        valider = Expr(element_token);
        if (valider == -1){
            return -1;
        }

        // ;
        if ((*element_token)->tokenCodageId != 5){
            printf(GREEN"Erreur : il faut un ';' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }

        (*element_token) = (*element_token)->next;

        return valider;
    }
    else if ((*element_token)->tokenCodageId == 53){

        // appelle de la fonction Identpoint
        valider = Identpoint(element_token);
        // :=
        if ((*element_token)->tokenCodageId != 11){
            printf(GREEN"Erreur : il faut un ':=' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // EXPR
        valider = Expr(element_token);
        if (valider == -1){
            return -1;
        }
        // ;
        if ((*element_token)->tokenCodageId != 5){
            printf(GREEN"Erreur : il faut un ';' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
            
            (*element_token) = (*element_token)->next;  
        
    }
    return valider;
}