#include "fichier.h"
#include "paramsinterro.h"
#include "declstar.h"
#include "instrplus.h"
#include "declbis.h"
#include "type.h"
#include "suite.h"

int Decl(struct element_token_valeur ** element_token){
    int valider = 1;
    // si on a pas de type, fonction, procédure, ident ou begin alors on return -1
    if ((*element_token)->tokenCodageId != 6 && (*element_token)->tokenCodageId != 13 && (*element_token)->tokenCodageId != 3 && (*element_token)->tokenCodageId != 53 && (*element_token)->tokenCodageId != 12){
        printf(GREEN"Erreur : il faut un type, une fonction, une procedure, un ident ou un begin \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;  
    }
    // DECL → procedure IDENT PARAMSINTERRO is DECLSTAR begin INSTRPLUS end IDENTINTERRO ;
    if ((*element_token)->tokenCodageId==3){
        (*element_token) = (*element_token)->next;
        if ((*element_token)->tokenCodageId!=53){
            printf(GREEN"Erreur : le nom de la procedure n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        valider = Paramsinterro(element_token);
        if (valider==-1){
            return -1;
        }
        if ((*element_token)->tokenCodageId!=4){
            printf(GREEN"Erreur : il faut le mot is \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        valider = Declstar(element_token);
        if (valider==-1){
            return -1;
        }
        // begin
        if ((*element_token)->tokenCodageId!=12){
            printf(GREEN"Erreur : il faut le mot begin \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        valider = Instrplus(element_token);
        if (valider==-1){
            return -1;
        }
       
        // end
        if ((*element_token)->tokenCodageId!=9){
            printf(GREEN"Erreur : il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // ident ou ;
        
        if ((*element_token)->tokenCodageId==53 ){
            (*element_token) = (*element_token)->next;
            if ((*element_token)->tokenCodageId!=5){
                printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;
            }
        }
        else if ((*element_token)->tokenCodageId==5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
       
        (*element_token) = (*element_token)->next;
    }
    // DECL -> function IDENT PARAMSINTERRO return TYPE is DECLSTAR begin INSTRPLUS end IDENTINTERRO ';'
    if ((*element_token)->tokenCodageId==13){
        (*element_token) = (*element_token)->next;
        // ident
        if ((*element_token)->tokenCodageId!=53){
            printf(GREEN"Erreur : le nom de la fonction n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
       
        valider = Paramsinterro(element_token);
        if (valider==-1){
            return -1;
        }
     
        if ((*element_token)->tokenCodageId!=14){
            printf(GREEN"Erreur : il faut le mot return \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        valider = Type(element_token);
        if (valider==-1){
            return -1;
        }

        if ((*element_token)->tokenCodageId!=4){
            printf(GREEN"Erreur : il faut le mot is \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        valider = Declstar(element_token);
        if (valider==-1){
            return -1;
        }

        // begin
        if ((*element_token)->tokenCodageId!=12){
            printf(GREEN"Erreur : il faut le mot begin \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        valider = Instrplus(element_token);
        if (valider==-1){
            return -1;
        }

        // end
        if ((*element_token)->tokenCodageId!=9){
            printf(GREEN"Erreur : il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // ident ou ;
        if ((*element_token)->tokenCodageId==53 ){
            (*element_token) = (*element_token)->next;

            if ((*element_token)->tokenCodageId!=5){
                printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;
            }
        }
        else if ((*element_token)->tokenCodageId==5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }

        (*element_token) = (*element_token)->next;

        return valider;
    }
    // DECL -> type IDENT DECLBIS
    if ((*element_token)->tokenCodageId==6){
        (*element_token) = (*element_token)->next;
        if ((*element_token)->tokenCodageId!=53){
            printf(GREEN"Erreur : le nom du type n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        valider = Declbis(element_token);
        if (valider==-1){
            return -1;
        }
    }
    // DECL -> IDENTPLUSVIRGULE : TYPE SUITE ;
    if ((*element_token)->tokenCodageId==53){
        (*element_token) = (*element_token)->next;
        // tant qu'on  , ou ident
        int a=0; // vaut 0 si on a un ident, 1 si on a un ,
        while((*element_token)->tokenCodageId==59 || (*element_token)->tokenCodageId==53){
            if ((*element_token)->tokenCodageId!=59&& a%2==0){
                a++;
                (*element_token) = (*element_token)->next;
            }
            else if ((*element_token)->tokenCodageId!=53 && a%2==1){
                a++;
                (*element_token) = (*element_token)->next;
            }
            else {
                printf(GREEN"Erreur : il faut un ident ou un , \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;
            }
        }
            
        if ((*element_token)->tokenCodageId!=10){
            printf(GREEN"Erreur : il faut le mot : \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;  
        }
        (*element_token) = (*element_token)->next;
        
        valider = Type(element_token);
        if (valider==-1){
            return -1;
        }
        valider = Suite(element_token);
        if (valider==-1){
            return -1;
        }
        if ((*element_token)->tokenCodageId!=5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;  
        }
        (*element_token) = (*element_token)->next;
    }

    return valider;
}