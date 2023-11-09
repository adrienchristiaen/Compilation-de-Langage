#include "analyseur_lexical.h"

// ouvrir le fichier ada_test.txt
FILE* fichier = NULL;




int main(){
    fichier = fopen("ada_test.txt", "r+");
  
    // supprimer les commentaires 
    // void supprimer_commentaires(fichier); enlever le commentaire quand on aura créer la fonction 

    // creer la liste vide element_token_valeur
    struct linked_list_token_valeur * list_token = malloc(sizeof(struct linked_list_token_valeur));
    struct element_token_valeur * element_token = malloc(sizeof(struct element_token_valeur));

    // initialiser la liste vide
    element_token->tokenCodageId = 0;
    element_token->valeur = NULL;
    element_token->line = 0;
    element_token->column = 0;
    element_token->next = NULL;
    list_token->head = element_token;

    // utiliser la fonction tokeniser
  

    // printf le resultat 
    fclose(fichier);
    return 0;
}