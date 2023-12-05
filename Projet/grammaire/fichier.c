#include "../analyseur_lexical.h"

void ficher(element_token_valeur * liste_token){
    if (liste_token.tokenCodageId != 1){
        printf("Erreur de syntaxe ligne %d colonne %d\n", liste_token.line, liste_token.column);
        return -1;
    }
    liste_token = liste_token.next;
    if (liste_token.tokenCodageId != 52){
        printf("Erreur de syntaxe ligne %d colonne %d\n", liste_token.line, liste_token.column);
        return -1;
    }
    liste_token = liste_token.next;
    if (liste_token.tokenCodageId != 5){
        printf("Erreur de syntaxe ligne %d colonne %d\n", liste_token.line, liste_token.column);
        return -1;
    }
    liste_token = liste_token.next;
    if (liste_token.tokenCodageId != 2){
        printf("Erreur de syntaxe ligne %d colonne %d\n", liste_token.line, liste_token.column);
        return -1;
    }
    liste_token = liste_token.next;
    if (liste_token.tokenCodageId != 52){
        printf("Erreur de syntaxe ligne %d colonne %d\n", liste_token.line, liste_token.column);
        return -1;
    }
    liste_token = liste_token.next;
    if (liste_token.tokenCodageId != 5){
        printf("Erreur de syntaxe ligne %d colonne %d\n", liste_token.line, liste_token.column);
        return -1;
    }
    return 1;


}

