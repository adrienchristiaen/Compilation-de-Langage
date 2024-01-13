#include "fichier.h"
#include "instr.h"

int Instrplus(struct element_token_valeur ** element_token){

    int valider=1;
    // si on a pas 	IDENT, begin, return, if, for, while, put alors on return -1
    if ((*element_token)->tokenCodageId != 53 && (*element_token)->tokenCodageId != 12 && (*element_token)->tokenCodageId != 14 && (*element_token)->tokenCodageId != 24 && (*element_token)->tokenCodageId != 28 && (*element_token)->tokenCodageId != 31 && (*element_token)->tokenCodageId != 52){
        printf(GREEN"Erreur : il faut un ident, un begin, un return, un if, un for ou un while \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
         printf("token : %d\n", (*element_token)->tokenCodageId);
        return -1;  
    }
    // INSTRPLUS -> INSTR INSTRPLUS .
    // Appel de la fonction Instr
    valider = Instr(element_token);
    if (valider == -1){
        return -1;
    }


    // si on a IDENT ou begin ou  return ou if ou for ou while  on appelle Instrplus
    if ((*element_token)->tokenCodageId == 53 || (*element_token)->tokenCodageId == 12 || (*element_token)->tokenCodageId == 14 || (*element_token)->tokenCodageId == 24 || (*element_token)->tokenCodageId == 28 || (*element_token)->tokenCodageId == 31 || (*element_token)->tokenCodageId == 52){
        return Instrplus(element_token);
        
    }
    

    

    return valider;
}