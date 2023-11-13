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


// Les mots clés de notre langage
const char* keyword_token[] = {"if", "else", "elsif", "then", "end", "loop", "while", "for"} ;
// Les mots clés de notre langage qui doivent être gardés et on enlevera ceux qui ne sont pas dans cette liste, en regardardant lettre par lettre
const int keyword_token_keep[] = {1 , 1, 1, 1, 1, 1, 1, 1} ;
const int keyword_token_index[] = {1, 2, 3, 4, 5, 6, 7, 8} ;
// Les types de données de notre langage
const char* type_token[] = { "integer", "float", "string", "char", "boolean" } ;
const int type_token_keep[] = {1 , 1, 1, 1, 1} ;
const int type_token_index[] = {9, 10, 11, 12, 13} ;
// Les déclarations de notre langage
const char* declaration_token[] = { "declare", "function", "procedure", "is", "begin", "end", "return"} ;
const int declaration_token_keep[] = {1 , 1, 1, 1, 1, 1, 1} ;
const int declaration_token_index[] = {14, 15, 16, 17, 18, 19, 20} ;
// Les opérateurs de notre langage
const char* operator_token[] = { "+", "-", "*", "/", "mod", "and", "or", "not"} ;
const int operator_token_keep[] = {1 , 1, 1, 1, 1, 1, 1, 1} ;
const int operator_token_index[] = {21, 22, 23, 24, 25, 26, 27, 28} ;
// Les comparaisons de notre langage
const char* comparison_token[] = { "=", "/=", "<", "<=", ">", ">="} ;
const int comparison_token_keep[] = {1 , 1, 1, 1, 1, 1} ;
const int comparison_token_index[] = {29, 30, 31, 32, 33, 34} ;
// Les symboles de ponctuation de notre langage
const char* punctuation_token[] = { ";", ":", ",", "."} ;
const int punctuation_token_keep[] = {1 , 1, 1, 1} ;
const int punctuation_token_index[] = {35, 36, 37, 38} ;
// Les parenthèses et crochets de notre langage
const char* parenthesis_token[] = { "(", ")", "[", "]"} ;
const int parenthesis_token_keep[] = {1 , 1, 1, 1} ;
const int parenthesis_token_index[] = {39, 40, 41, 42} ;
// Les affectations et opérateurs de notre langage
const char* assignment_token[] = { ":=", "+=", "-=", "*=", "/="} ;
const int assignment_token_keep[] = {1 , 1, 1, 1, 1} ;
const int assignment_token_index[] = {43, 44, 45, 46, 47} ;
// Les valeurs littérales de notre langage
const char* literal_token[] = { "integer_literal", "float_literal", "string_literal", "char_literal", "boolean_literal"} ;
const int literal_token_keep[] = {1 , 1, 1, 1, 1} ;
const int literal_token_index[] = {48, 49, 50, 51, 52} ;

// Identificateur nom de variable, de fonction, de procédure etc..
const char* identifier_token[] = { "identifier"} ;
const int identifier_token_keep[] = {1} ;
const int identifier_token_index[] = {53} ;

// autre mot clé 
const char* other_keyword_token[] = {"with", "use", "package", "body", "private", "limited", "null"};
const int other_keyword_token_keep[] = {1, 1, 1, 1, 1, 1, 1};
const int other_keyword_token_index[] = {54, 55, 56, 57, 58, 59, 60};



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

void afficher_liste_tokens(struct linked_list_token_valeur *list_token) {
    struct element_token_valeur *current = list_token->head;

    while (current != NULL) {
        if (current->tokenCodageId == 0) {
            break; // Fin de la liste
        }

        if (current->valeur[0] == NULL) {
            printf("%d", current->tokenCodageId);
        } else {
            for(int i=0 ; i<MAX_LENGTH ; i++){
                if(current->valeur[i] == NULL){
                    break;
                }
                printf("(%d,%s)", current->tokenCodageId,current->valeur[i]);
            }
            
        }

        // Passez au prochain élément
        current = current->next;
    }
}


int index_token_word(const char* mot){
    int index = comparer_mot(mot, keyword_token, keyword_token_index, 8);
    if (index != -1){
        return index;
    }
    index = comparer_mot(mot, type_token, type_token_index, 5);
    if (index != -1){
        return index;
    }
    index = comparer_mot(mot, declaration_token, declaration_token_index, 7);
    if (index != -1){
        return index;
    }
    index = comparer_mot(mot, operator_token, operator_token_index, 8);
    if (index != -1){
        return index;
    }
    index = comparer_mot(mot, comparison_token, comparison_token_index, 6);
    if (index != -1){
        return index;
    }
    index = comparer_mot(mot, punctuation_token, punctuation_token_index, 4);
    if (index != -1){
        return index;
    }
    index = comparer_mot(mot, parenthesis_token, parenthesis_token_index, 4);
    if (index != -1){
        return index;
    }
    index = comparer_mot(mot, assignment_token, assignment_token_index, 5);
    if (index != -1){
        return index;
    }
 
    index = comparer_mot(mot, other_keyword_token, other_keyword_token_index, 7);
    if (index != -1){
        return index;
    }
    return -1;

}
