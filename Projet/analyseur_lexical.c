#include "analyseur_lexical.h"

// creation de la variable qui va contenir le caractere actuel en ascii
int caractereActuel=0;
// endroit du carectere sur le mot qu'on lit
int position_caractere=1;
// variable qui contiendra le nombre de ligne
int line=1;
// variaable qui contiendra le numéro du caractère dans la ligne
int column=1;
// si on est dans un string, on met cette variable à 1
int stringValeur = 0; 


// Les mots clés de notre langage concernant le fichier
const char* file_token[] = {"with", "use", "procedure", "is", ";"};
const int file_token_keep[] = {1, 1, 1, 1, 1};
const int file_token_index[] = {1, 2, 3, 4, 5};

// Les déclarations de notre langage
const char* declaration_token[] = {"type", "access", "record", "end", ":", ":=", "begin", "function", "return"};
const int declaration_token_keep[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
const int declaration_token_index[] = {6, 7, 8, 9, 10, 11, 12, 13, 14};

// Les modes de notre langage
const char* mode_token[] = {"in", "out"};
const int mode_token_keep[] = {1, 1};
const int mode_token_index[] = {15, 16};

// Les expressions de notre langage
const char* expression_token[] = { "true", "false", "null", "(", ")", "not", "new"};
const int expression_token_keep[] = {1, 1, 1, 1, 1, 1, 1}; 
const int expression_token_index[] = {17, 18, 19, 20, 21, 22, 23};

// Les instructions de notre langage
const char* instruction_token[] = { "if", "then", "elsif", "else", "for", "reverse", "loop", "while"};
const int instruction_token_keep[] = {1, 1, 1, 1, 1, 1, 1, 1};
const int instruction_token_index[] = {24, 25, 26, 27, 28, 29, 30, 31};

// Les opérateurs de notre langage
const char* operator_token[] = {"=", "/=", "<", "<=", ">", ">=", "+", "-", "*", "/", "rem", "and", "then", "or", "."};
const int operator_token_keep[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
const int operator_token_index[] = {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42 , 43, 44, 45, 46};


void supprimer_commentaires(FILE* fichier_entree, FILE* fichier_sortie) {
    int caractereActuel;
    int caracterePrecedent = EOF; // (End Of File)
    bool dans_commentaire = false; //drapeau pour savoir si on est dans un commentaire ou pas 

    while ((caractereActuel = fgetc(fichier_entree)) != EOF) {
        if (!dans_commentaire && caractereActuel == '-' && caracterePrecedent == '-') {
            dans_commentaire = true;
        } else if (dans_commentaire && caractereActuel == '\n') {
            dans_commentaire = false;
        }


        if (!dans_commentaire) {
            fputc(caractereActuel, fichier_sortie);
        }
        caracterePrecedent = caractereActuel;
    }
}

//fgetc lit le fichier caractère par caractère 
//fputc écrit dans le fichier caractère par caractère
//En Ada un commentaire commence par -- et se termine par un retour à la ligne

int comparer_mot(const char* mot, const char** liste_mots, const int* liste_indices, int taille_liste) {
    for (int i = 0; i < taille_liste; ++i) {
        if (strcmp(mot, liste_mots[i]) == 0) {
            return liste_indices[i];
        }
    }
    // Retourne -1 si le mot n'est pas trouvé dans la liste
    return -1;
}

// il faut parcourir le mot lettre par lettre et regarder si c'est un entier ou pas et si il y a un . 
int estUnFloat(char*mot){
    int longueur = strlen(mot);
    int i ;
    // passe à 1 si on a trouvé un point
    int point = 0;
    for (i=0; i<longueur; i++){
        if(point==0){
            if (isdigit(mot[i]) == 0){
                return -1;
            }
        }
        else{
            if (isdigit(mot[i]) == 0 && mot[i] != '.'){
                return -1;
            }
            if (mot[i] == '.'){
                point = 1;
            }
        }
    }
    return 1;
}

int estUnEntier(char*mot){
    int longueur = strlen(mot);
    int i ;
    for (i=0; i<longueur; i++){
        if (isdigit(mot[i]) == 0){
            return -1;
        }
    }
    return 1;
}

int estUnString(char*mot){
    int longueur = strlen(mot);
    int i ;
    // on regarde si le premier caractère est un "
    if (mot[0] != '"'){
        return -1;
    }
    // on regarde si le dernier caractère est un "
    if (mot[longueur-1] != '"'){
        return -1;
    }
    // on regarde si il y a un " au milieu
    for (i=1; i<longueur-1; i++){
        if (mot[i] == '"'){
            return -1;
        }
    }
    return 1;
}

// la longueur du char est de 1
int estUnChar(char*mot){
       // on regarde si la longueur est de 3 caractères
    if (strlen(mot) != 3) {
        return -1;
    }
    
    // on regarde si le premier caractère est un '
    if (mot[0] != '\'') {
        return -1;
    }
    
    // on regarde si le dernier caractère est un '
    if (mot[2] != '\'') {
        return -1;
    }
    
    // Si toutes les conditions sont remplies, c'est un char valide
    return 1;

}

int estUnBoolean(char*mot){
    // on regarde si le mot est true ou false
    if (strcmp(mot, "true") == 0 || strcmp(mot, "false") == 0) {
        return 1;
    }
    return -1;
}
