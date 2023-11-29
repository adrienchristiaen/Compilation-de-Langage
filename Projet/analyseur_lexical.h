#include "header.h"
#define MAX_LENGTH 1000
struct element_token_valeur {
    int tokenCodageId;
    // la valeur est nul si c'est pas un entier ou une variable (ou un string mais pas de string)
    char * valeur[MAX_LENGTH];
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

// Fonction qui utilise la fonction comparer_mot pour comparer un mot avec les différents types de tokens et renvoie l'index du token correspondant sinon -1
int index_token_word(const char* mot);
//Fonction qui renvoie 1 si c’est un float et -1 sinon
int estUnFloat(char*mot);

//Fonction qui renvoie 1 si c’est un entier et -1 sinon
int estUnEntier(char*mot);

//Fonction qui renvoie 1 si c'est un char et -1 sinon
int estUnChar(char*mot);

//Fonction qui renvoie 1 si c'est un boolean et -1 sinon
int estUnBoolean(char*mot);

//fonction qui lit les mots du fichier 
void litMotFichier(FILE* fichier, struct linked_list_token_valeur * list_token);

//fonction qui recopie la liste des token et qui verifie lorsque le token est 53, et ajoute les token qui compose ce mot dans une nouvelle liste
void recopie_liste_token(struct linked_list_token_valeur * list_token, struct linked_list_token_valeur * list_token_recopie);

//Creer la fonction afficher liste des tokens ligne par ligne 
void afficher_liste_tokens(struct linked_list_token_valeur * list_token);