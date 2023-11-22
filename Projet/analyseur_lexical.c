#include "analyseur_lexical.h"

// creation de la variable qui va contenir le caractere actuel en ascii
int caractereActuel=0;
// endroit du carectere sur le mot qu'on lit
int position_caractere=0;
// variable qui contiendra le nombre de ligne
int line=1;
// variaable qui contiendra le numéro du caractère dans la ligne
int column=1;
// si on est dans un string, on met cette variable à 1
int stringValeur = 0; 
// si on a un identifiant, on met cette variable à 1
int identifiantValeur = 0;


// Les mots clés de notre langage concernant le fichier
const char* file_token[] = {"with", "use", "procedure", "is", ";", "put"};
const int file_token_keep[] = {1, 1, 1, 1, 1, 1};
const int file_token_index[] = {1, 2, 3, 4, 5, 54};

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

// Les types de notre langage
const char* type_token[] = {"character", "string", "boolean", "integer", "float", "access"};
const int type_token_keep[] = {1, 1, 1, 1, 1, 1}; 
const int type_token_index[] = {47, 48, 49, 50, 51, 52};

// Identificateur nom de variable, de fonction, de procédure etc..
const char* identifier_token[] = { "identifier"} ;
const int identifier_token_keep[] = {1} ;
const int identifier_token_index[] = {53} ;

// Les valeurs littérales de notre langage
const char* literal_token[] = { "integer_literal", "float_literal", "string_literal", "char_literal", "boolean_literal"} ;
const int literal_token_keep[] = {1 , 1, 1, 1, 1} ;
const int literal_token_index[] = {55, 56, 57, 58, 59} ;

void supprimer_commentaires(FILE* fichier_entree, FILE* fichier_sortie) {
    int caractereActuel;
    int caracterePrecedent = EOF; // (End Of File)
    bool dans_commentaire = false; //drapeau pour savoir si on est dans un commentaire ou pas 

    while ((caractereActuel = fgetc(fichier_entree)) != EOF) {
        if (!dans_commentaire && caractereActuel == '-' && caracterePrecedent == '-') {
            dans_commentaire = true;
        } else if (dans_commentaire && caractereActuel == '\n') {
            dans_commentaire = false;
        } else if (!dans_commentaire && caracterePrecedent == '-' && caractereActuel != '-') {
            fputc(caracterePrecedent, fichier_sortie);
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
int estUnFloat(char*mot) {
    int longueur = strlen(mot);
    int i;
    int pointCount = 0;

    for (i = 0; i < longueur; i++) {
        if (isdigit(mot[i]) == 0) {
            if (mot[i] == '.' && pointCount == 0) {
                pointCount = 1;
            } else {
                return -1;
            }
        }
    }
    return pointCount == 1 ? 1 : -1;
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

void afficher_liste_tokens(struct linked_list_token_valeur *list_token) {
    struct element_token_valeur *current = list_token->head;

    while (current != NULL) {
        if (current->tokenCodageId == 0) {
            break; // Fin de la liste
        }

        if (current->valeur[0] == NULL) {
            printf("(%d)\n", current->tokenCodageId);
        } else {
            for (int i = 0; i < MAX_LENGTH; i++) {
                if (current->valeur[i] == NULL) {
                    break;
                }
                printf("(%d,%s) ", current->tokenCodageId, current->valeur[i]);
            }
            printf("\n");
        }

        // Passez au prochain élément
        current = current->next;
    }
}


// Fonction index_token_word
int index_token_word(const char* mot) {
    int index = comparer_mot(mot, file_token, file_token_index, 6);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, declaration_token, declaration_token_index, 9);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, mode_token, mode_token_index, 2);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, expression_token, expression_token_index, 7);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, instruction_token, instruction_token_index, 8);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, operator_token, operator_token_index, 15);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, type_token, type_token_index, 6);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, identifier_token, identifier_token_index, 1);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, literal_token, literal_token_index, 5);
    if (index != -1) {
        return index;
    }
    return 53; // identifier_token
}




void litMotFichier(FILE* fichier, struct linked_list_token_valeur *list_token) {
    struct element_token_valeur *current = list_token->head;
    printf("Liste des tokens :\n");

    if (fichier == NULL) {
        fprintf(stderr, "Invalid file pointer\n");
        exit(EXIT_FAILURE);
    }

    int caractereActuel;
    char caractere;
    char mot[MAX_LENGTH];
    int i = 0;  // Index du caractère dans le mot

    // Tant qu'on n'est pas à la fin du fichier
    while ((caractereActuel = fgetc(fichier)) != EOF) {
        caractere = (char)caractereActuel;
        printf("caractere : %c\n", caractere);

        // Si c'est un espace, cela signifie la fin d'un mot
        if (caractere == ' ' || caractere == '\t' || caractere == '\n') {
            // Vérifier le type du mot et ajouter à la liste des tokens
            mot[i] = '\0';  // Ajouter le caractère de fin de chaîne
            i = 0;

            if (estUnFloat(mot) == 1) {
                current->tokenCodageId = 56;
                current->valeur[0] = strdup(mot);
            }
            else if (estUnEntier(mot) == 1) {
                current->tokenCodageId = 55;
                current->valeur[0] = strdup(mot);
            } 
            else if (estUnString(mot) == 1) {
                current->tokenCodageId = 57;
                current->valeur[0] = strdup(mot);
            }
            // si il y a un " au début du mot et à la fin du mot et pas au milieu
            else if (estUnChar(mot) == 1) {
                current->tokenCodageId = 58;
                current->valeur[0] = strdup(mot);
            }
            else if (estUnBoolean(mot) == 1) {
                current->tokenCodageId = 59;
                current->valeur[0] = strdup(mot);
            }
           
            
            else {
                current->tokenCodageId = index_token_word(mot);
                current->valeur[0] = strdup(mot);
            }
            
           
            
            // print le token id
            printf("token id : %d\n", current->tokenCodageId);
            // Mettre à jour les autres informations (ligne, colonne, etc.)
            current->line = line;
            current->column = column;
            current->next = malloc(sizeof(struct element_token_valeur));
            current = current->next;
            current->tokenCodageId = 0;
        
            for (int j = 0; j < 1000; j++) {
                current->valeur[j] = NULL;
            }

            current->line = 0;
            current->column = 0;
            current->next = NULL;
            // si on est dans un \n on met à jour la ligne et la colonne
            if (caractere == '\n') {
                line++;
                column = 1;
            }
            printf("line : %d\n", line);
        } else {
            // Ajouter le caractère au mot
            mot[i++] = caractere;
        }
    }
}

void recopie_liste_token(struct linked_list_token_valeur * list_token, struct linked_list_token_valeur * list_token_recopie){
    struct element_token_valeur *current = list_token->head;
    struct element_token_valeur *current_recopie = list_token_recopie->head;

    while (current->tokenCodageId !=0){
        // si l'id du token est différent de 53, on le recopie dans la liste recopie
        if(current->tokenCodageId!=53){
            current_recopie->tokenCodageId = current->tokenCodageId;
            current_recopie->valeur[0] = strdup(current->valeur[0]);
            current_recopie->line = current->line;
            current_recopie->column = current->column;
            current_recopie->next = malloc(sizeof(struct element_token_valeur));
            current_recopie = current_recopie->next;
            current_recopie->tokenCodageId = 0;
            for (int j = 0; j < 1000; j++) {
                current_recopie->valeur[j] = NULL;
            }
            current_recopie->line = 0;
            current_recopie->column = 0;
            current_recopie->next = NULL;
        }
        // si c'est l'id 53,n on regarde si on a eu raison de dire que c'était un identifiant, donc on lit lettre par lettre le mot de current->valeur et on regarde si oui ou non c'est un token déjà existant et on l'ajoute dans la liste recopie, on regarde tout le mot entier car il peut se finir par ; ou ) ou ")  etc..
     
       
        current = current->next;
    }
}