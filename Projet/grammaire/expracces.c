#include "fichier.h"
#include "identpoint.h"
#include "exprplusvirgule.h"


int Expracces(struct element_token_valeur * element_token){
    int valider =1;
    // EXPRACCES -> '(' EXPRPLUSVIRGULE ')' 
    if (element_token->tokenCodageId == 20){
    element_token = element_token->next;
    // Appel de la fonction Exprplusvirgule
    valider = Exprplusvirgule(element_token);
    if (valider == -1){
        return -1;
    }
    // )
    if (element_token->tokenCodageId != 21){
        printf(GREEN"Erreur : il faut un ')' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;
    }}
    //EXPRACCES -> . IDENT IDENTPOINT 
    if (element_token->tokenCodageId == 46){
        element_token = element_token->next;
        // IDENT
        if (element_token->tokenCodageId != 53){
            printf(GREEN"Erreur : il faut un ident \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        // Appel de la fonction Identpoint
        valider = Identpoint(element_token);
        if (valider == -1){
            return -1;
        }
    }
    return valider;
}