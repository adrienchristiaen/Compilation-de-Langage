#include "fichier.h"
#include "expr.h"
#include "instrbis.h"
#include "instrplus.h"
#include "boucle1.h"
#include "boucle2.h"

int Instr(struct element_token_valeur ** element_token){
    
    int valider =1;

    // si on a pas IDENT, begin, return, if, for, while, put alors on return -1
    if ((*element_token)->tokenCodageId != 53 && (*element_token)->tokenCodageId != 12 && (*element_token)->tokenCodageId != 14 && (*element_token)->tokenCodageId != 24 && (*element_token)->tokenCodageId != 28 && (*element_token)->tokenCodageId != 31 && (*element_token)->tokenCodageId != 52){
        printf(GREEN"Erreur : il faut un ident, un begin, un return, un if, un for ou un while \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
       
        return -1;  
    }
    // Instr -> begin INSTRPLUS end ;
    if ((*element_token)->tokenCodageId == 12){
        
        (*element_token) = (*element_token)->next;
        valider = Instrplus(element_token);
        if (valider==-1){
            return -1;
        }
        
        //end 
        if ((*element_token)->tokenCodageId != 9){
            printf(GREEN"Erreur : il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // ;
        if ((*element_token)->tokenCodageId != 5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        return 1;
    }
        
    // INSTR -> for IDENT in REVERSE? EXPR '..' EXPR
    if ((*element_token)->tokenCodageId == 28){
        (*element_token) = (*element_token)->next;
        if ((*element_token)->tokenCodageId != 53){
            printf(GREEN"Erreur : il faut un ident \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        if ((*element_token)->tokenCodageId != 15){
            printf(GREEN"Erreur : il faut le mot in \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // cas reverse
        if ((*element_token)->tokenCodageId == 29){
            (*element_token) = (*element_token)->next;
            // si on a pas un IDENT, (, character, ENTIER, CARACTERE, true, false, null, not, -
            if ((*element_token)->tokenCodageId != 53 && (*element_token)->tokenCodageId != 20 && (*element_token)->tokenCodageId != 47 && (*element_token)->tokenCodageId != 54 && (*element_token)->tokenCodageId != 56 && (*element_token)->tokenCodageId != 57 && (*element_token)->tokenCodageId != 61 && (*element_token)->tokenCodageId != 19 && (*element_token)->tokenCodageId != 22 && (*element_token)->tokenCodageId != 39){
                printf(GREEN"Erreur : il faut un ident, un (, un character, un entier, un caractere, un true, un false, un null, un not ou un - \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;
            }
            valider = Expr(element_token);
            if (valider==-1){
                return -1;
            }
            // ..
            if ((*element_token)->tokenCodageId != 46 && (*element_token)->next->tokenCodageId != 46){
                printf(GREEN"Erreur : il faut le mot . \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;
            }
            (*element_token) = (*element_token)->next->next;
            // si on a pas un IDENT, (, character, ENTIER, CARACTERE, true, false, null, not, -
            if ((*element_token)->tokenCodageId != 53 && (*element_token)->tokenCodageId != 20 && (*element_token)->tokenCodageId != 47 && (*element_token)->tokenCodageId != 54 && (*element_token)->tokenCodageId != 56 && (*element_token)->tokenCodageId != 57 && (*element_token)->tokenCodageId != 61 && (*element_token)->tokenCodageId != 19 && (*element_token)->tokenCodageId != 22 && (*element_token)->tokenCodageId != 39){
                printf(GREEN"Erreur : il faut un ident, un (, un character, un entier, un caractere, un true, un false, un null, un not ou un - \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;
            }
            valider = Expr(element_token);
            if (valider==-1){
                return -1;
            }
            return 1;
            
        }
    }
    // INSTR -> return EXPRINTERRO ';'
    if ((*element_token)->tokenCodageId == 14){
        (*element_token) = (*element_token)->next;

        
        // ;
        if ((*element_token)->tokenCodageId == 5){
            (*element_token) = (*element_token)->next;
        }
        else {
            valider= Expr(element_token);
            if (valider==-1){
                return -1;
            }

            // ;
            if ((*element_token)->tokenCodageId != 5){
                printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;
            }
            (*element_token) = (*element_token)->next;

        }
        return 1;
    }
    // INSTR -> while EXPR loop INSTRPLUS end loop ';'
    if ((*element_token)->tokenCodageId==31){
        (*element_token) = (*element_token)->next;
        // Appel de la fonction Expr
        valider = Expr(element_token);
        if (valider == -1){
            return -1;
        }
        // loop
        if ((*element_token)->tokenCodageId != 30){
            printf(GREEN"Erreur : il faut le mot loop \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // Appel de la fonction Instrplus
        valider = Instrplus(element_token);
        if (valider == -1){
            return -1;
        }
        // end
        if ((*element_token)->tokenCodageId != 9){
            printf(GREEN"Erreur : il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // loop
        if ((*element_token)->tokenCodageId != 30){
            printf(GREEN"Erreur : il faut le mot loop \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // ;
        if ((*element_token)->tokenCodageId != 5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
    }

    // INSTR -> IDENT INSTRBIS
     

    if ((*element_token)->tokenCodageId == 53){
        (*element_token) = (*element_token)->next;
        // Appel de la fonction Instrbis
        valider = Instrbis(element_token);
        if (valider == -1){
            return -1;
        }               

        return 1;
    }
    // EXPR -> if EXPR then INSTRPLUS BOUCLE1 BOUCLE2 end if ;
    if ((*element_token)->tokenCodageId == 24){
        (*element_token) = (*element_token)->next;
        
        // Appel de la fonction Expr
        valider = Expr(element_token);
        if (valider == -1){
            return -1;
        }
        // then

        if ((*element_token)->tokenCodageId != 25){
            printf(GREEN"Erreur : il faut le mot then \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }                                


       
        (*element_token) = (*element_token)->next;
        // Appel de la fonction Instrplus
        valider = Instrplus(element_token);
        if (valider == -1){
            return -1;
        }
        // on regarde si y'a un ( elsif ou un ( else
        if ((*element_token)->tokenCodageId==26){
            // on appelle la fonction Boucle1
            valider = Boucle1(element_token);
            if (valider == -1){
                return -1;
            }
            // on appelle la fonction Boucle2
            valider = Boucle2(element_token);
            if (valider == -1){
                return -1;
            }
        }
        else if ((*element_token)->tokenCodageId==27){

            // on appelle la fonction Boucle2
            valider = Boucle2(element_token);
            if (valider == -1){
                return -1;
            }
        }
        // end
        if ((*element_token)->tokenCodageId != 9){
            printf(GREEN"Erreur : il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // if
        if ((*element_token)->tokenCodageId != 24){
            printf(GREEN"Erreur : il faut le mot if \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
        // ;

        if ((*element_token)->tokenCodageId != 5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;
        }
        (*element_token) = (*element_token)->next;
                          return 1;
    }
    // INSTR -> put '(' ident ou char ou bool ou integer ')' ';'
    if ((* element_token)->tokenCodageId==52){
        (*element_token) = (*element_token)->next;
        if ((*element_token)->tokenCodageId != 20 ){
            printf(GREEN"Erreur : il faut un ( \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;  
        }
        (*element_token) = (*element_token)->next;

        if ((*element_token)->tokenCodageId!=53 && (*element_token)->tokenCodageId!=58 && (*element_token)->tokenCodageId!=57 && (*element_token)->tokenCodageId!=61 && (*element_token)->tokenCodageId!=54){
            printf(GREEN"Erreur : il faut un ident, un character, un true ou un false \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;  
        }

        if ((*element_token)->tokenCodageId==58){
            (*element_token) = (*element_token)->next;
            if ((*element_token)->tokenCodageId!=56){
                printf(GREEN"Erreur : il faut un char \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;  
            }
            (*element_token) = (*element_token)->next;
            if ((*element_token)->tokenCodageId!=58){
                printf(GREEN"Erreur : il faut un ' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
                return -1;  
            }
            (*element_token) = (*element_token)->next;
            }
        
        if ((*element_token)->tokenCodageId!=21){
            printf(GREEN"Erreur : il faut un ) \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;  
        }
        (*element_token) = (*element_token)->next;
        if ((*element_token)->tokenCodageId!=5){
            printf(GREEN"Erreur : il faut un ; \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
            return -1;  
        }
        (*element_token) = (*element_token)->next;
        return 1;
    }


   

    return valider;
}