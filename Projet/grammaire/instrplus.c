#include "fichier.h"
#include "instr.h"

int Instrplus(struct element_token_valeur * element_token){
    
    int valider=1;
    // si on a pas 	IDENT, begin, return, if, for, while alors on return -1
    if (element_token->tokenCodageId != 53 && element_token->tokenCodageId != 12 && element_token->tokenCodageId != 14 && element_token->tokenCodageId != 24 && element_token->tokenCodageId != 28 && element_token->tokenCodageId != 31){
        printf(GREEN"Erreur : il faut un ident, un begin, un return, un if, un for ou un while \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;  
    }
    // INSTRPLUS -> INSTR INSTRPLUS .
    // Appel de la fonction Instr
    valider = Instr(element_token);
    if (valider == -1){
        return -1;
    }
    return valider;
}