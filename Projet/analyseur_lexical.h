#include "header.h"
// creation de la variable qui va contenir le caractere actuel en ascii
int caractereActuel = 0;
// endroit du carectere sur le mot qu'on lit
int position_caractere = 0;
// variable qui contiendra le nombre de ligne
int line = 1;
// variaable qui contiendra le numéro du caractère dans la ligne
int column = 1;

struct element_token_valeur {
    int tokenCodageId;
    // la valeur est nul si c'est pas un string ou un entier ou une variable
    char * valeur;
    int line;
    int column;
    struct element_token_valeur * next;
};

struct linked_list_token_valeur {
    struct element_token_valeur * head;
};

int codage_token(ada_token_type tokenName);

//Fonction qui supprime les commentaires du fichier source en Ada 

void supprimer_commentaires(FILE* fichier_entree, FILE* fichier_sortie); 

//Fonction qui prends un mot et le compare avec les mots d'une liste et renvoie l'index du token correspondant

int comparer_mot(const char* mot, const char** liste_mots, const int* liste_indices, int taille_liste); 

//Creer la fonction tokeniser 

void tokeniser(FILE* fichier, struct linked_list_token_valeur * list_token);

//Creer la fonction afficher liste des tokens ligne par ligne 

void afficher_liste_tokens(struct linked_list_token_valeur * list_token);
