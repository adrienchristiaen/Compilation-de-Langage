#include "fichier.h"
#include "type.h"

int Parampluspointvirgule(struct element_token_valeur ** element_token){
    int valider =1;
    if ((*element_token) -> tokenCodageId != 53 ){
        printf(GREEN"Erreur : il faut un ident \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;
    }
    int a = 0; //  a pair alors on a un ident, a impair alors on a un ,
    while ((*element_token) -> tokenCodageId == 53 || (*element_token)->tokenCodageId == 59){
        if ((*element_token)->tokenCodageId == 59 && a%2 == 1){
            a++;
      
            (*element_token) = (*element_token)->next;
            
            }
        else if ((*element_token)->tokenCodageId == 53 && a%2 == 0){
            a++;

            (*element_token) = (*element_token)->next;}
        else {

            printf(GREEN"Erreur : il faut un ident ou un , \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
    }


    // : 
    if ((*element_token)->tokenCodageId != 10){
        printf(GREEN"Erreur : il faut un : \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;
    }
    (*element_token) = (*element_token)->next;
    // mode (in ou in out)  ou type (identifiant, entier float, bool, char)
 
    if ((*element_token)->tokenCodageId != 15  && (*element_token)->tokenCodageId != 53 && (*element_token)->tokenCodageId != 47 && (*element_token)->tokenCodageId != 48 && (*element_token)->tokenCodageId != 49 && (*element_token)->tokenCodageId != 50){
        printf(GREEN"Erreur : il faut un mode ou un type \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;
    }
    (*element_token) = (*element_token)->next;
    // mode  -> in | in out 
    if ((*element_token)->tokenCodageId == 15 ){
        (*element_token) = (*element_token)->next;
        if ((*element_token)->tokenCodageId == 16){
            (*element_token) = (*element_token)->next;
        }
        else if ((*element_token)->tokenCodageId != 53 && (*element_token)->tokenCodageId != 47 && (*element_token)->tokenCodageId != 48 && (*element_token)->tokenCodageId != 49 && (*element_token)->tokenCodageId != 50){
            printf(GREEN"Erreur : il faut un type \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
    }
    else if ((*element_token)->tokenCodageId == 53 || (*element_token)->tokenCodageId == 47 || (*element_token)->tokenCodageId == 48 || (*element_token)->tokenCodageId == 49 || (*element_token)->tokenCodageId == 50){

        int valider = Type(element_token);
        if (valider == -1){
            return -1;
        }
    }
    
    (*element_token) = (*element_token)->next;
    if ((*element_token)->tokenCodageId == 53){
        valider = Parampluspointvirgule(element_token);
        if (valider == -1){
            return -1;
        }
    }
    
  
    return valider;
}