#include "analyseur_lexical.h"

//Fonction qui supprime les commentaires du fichier source en Ada 

void supprimer_commentaires(FILE* fichier); 

//Fonction qui prends un mot et le compare avec les mots d'une liste et renvoie l'index du token correspondant

int comparer_mot(char *mot); 

//Creer la fonction tokeniser 

void tokeniser(FILE* fichier, struct linked_list_token_valeur * list_token);

//Creer la fonction afficher liste des tokens ligne par ligne 

void afficher_liste_tokens(struct linked_list_token_valeur * list_token);