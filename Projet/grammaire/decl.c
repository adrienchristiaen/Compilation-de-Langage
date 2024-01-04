#include "fichier.h"
#include "paramsinterro.h"
#include "declstar.h"
#include "instrplus.h"
#include "declbis.h"
#include "type.h"

int Decl(struct element_token_valeur * element_token){
    int valider = 1;
    // si on a pas de type, fonction, procédure, ident ou begin alors on return -1
    if (element_token->tokenCodageId != 6 && element_token->tokenCodageId != 13 && element_token->tokenCodageId != 3 && element_token->tokenCodageId != 53 && element_token->tokenCodageId != 12){
        printf(GREEN"Erreur : il faut un type, une fonction, une procedure, un ident ou un begin \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
        return -1;  
    }
    // DECL → procedure IDENT PARAMSINTERRO is DECLSTAR begin INSTRPLUS end IDENTINTERRO ;
    if (element_token->tokenCodageId==3){
        element_token = element_token->next;
        if (element_token->tokenCodageId!=53){
            printf(GREEN"Erreur : le nom de la procedure n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        valider = Paramsinterro(element_token);
        if (valider==-1){
            return -1;
        }
        if (element_token->tokenCodageId!=4){
            printf(GREEN"Erreur : il faut le mot is \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        valider = Declstar(element_token);
        if (valider==-1){
            return -1;
        }
        // begin
        if (element_token->tokenCodageId!=12){
            printf(GREEN"Erreur : il faut le mot begin \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        valider = Instrplus(element_token);
        if (valider==-1){
            return -1;
        }
        // end
        if (element_token->tokenCodageId!=13){
            printf(GREEN"Erreur : il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        // ident ou ;
        if (element_token->tokenCodageId==53 ){
            if (element_token->tokenCodageId!=5){
                printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
                return -1;
            }
        }
        else if (element_token->tokenCodageId==5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
    }
    // DECL -> function IDENT PARAMSINTERRO return TYPE is DECLSTAR begin INSTRPLUS end IDENTINTERRO ';'
    if (element_token->tokenCodageId==13){
        element_token = element_token->next;
        // ident
        if (element_token->tokenCodageId!=53){
            printf(GREEN"Erreur : le nom de la fonction n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        printf("element_token->tokenCodageId : %d\n",element_token->tokenCodageId);
        valider = Paramsinterro(element_token);
        if (valider==-1){
            return -1;
        }
        printf("element_token->tokenCodageId : %d\n",element_token->tokenCodageId);
        if (element_token->tokenCodageId!=14){
            printf(GREEN"Erreur : il faut le mot return \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        valider = Type(element_token);
        if (valider==-1){
            return -1;
        }
        if (element_token->tokenCodageId!=4){
            printf(GREEN"Erreur : il faut le mot is \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        valider = Declstar(element_token);
        if (valider==-1){
            return -1;
        }
        // begin
        if (element_token->tokenCodageId!=12){
            printf(GREEN"Erreur : il faut le mot begin \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        valider = Instrplus(element_token);
        if (valider==-1){
            return -1;
        }
        // end
        if (element_token->tokenCodageId!=9){
            printf(GREEN"Erreur : il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        // ident ou ;
        if (element_token->tokenCodageId==53 ){
            if (element_token->tokenCodageId!=5){
                printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
                return -1;
            }
        }
        else if (element_token->tokenCodageId==5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
    }
    // DECL -> type IDENT DECLBIS
    if (element_token->tokenCodageId==6){
        element_token = element_token->next;
        if (element_token->tokenCodageId!=53){
            printf(GREEN"Erreur : le nom du type n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
            return -1;
        }
        element_token = element_token->next;
        valider = Declbis(element_token);
        if (valider==-1){
            return -1;
        }
    }

    return valider;
}