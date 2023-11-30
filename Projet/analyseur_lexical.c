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
const int file_token_index[] = {1, 2, 3, 4, 5, 52};

// Les déclarations de notre langage
const char* declaration_token[] = {"type", "access", "record", "end", ":", ":=", "begin", "function", "return"};
const int declaration_token_keep[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
const int declaration_token_index[] = {6, 7, 8, 9, 10, 11, 12, 13, 14};

// Les modes de notre langage
const char* mode_token[] = {"in", "out"};
const int mode_token_keep[] = {1, 1};
const int mode_token_index[] = {15, 16};

// Les expressions de notre langage
const char* expression_token[] = { "true", "false", "null", "(", ")", "not", "new","\'"};
const int expression_token_keep[] = {1, 1, 1, 1, 1, 1, 1,1}; 
const int expression_token_index[] = {17, 18, 19, 20, 21, 22, 23,58};

// Les instructions de notre langage
const char* instruction_token[] = { "if", "then", "elsif", "else", "for", "reverse", "loop", "while"};
const int instruction_token_keep[] = {1, 1, 1, 1, 1, 1, 1, 1};
const int instruction_token_index[] = {24, 25, 26, 27, 28, 29, 30, 31};

// Les opérateurs de notre langage
const char* operator_token[] = {"=", "/=", "<", "<=", ">", ">=", "+", "-", "*", "/", "rem", "and", "then", "or", "."};
const int operator_token_keep[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
const int operator_token_index[] = {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42 , 43, 44, 45, 46};

// Les types de notre langage
const char* type_token[] = {"character", "boolean", "integer", "float", "access"};
const int type_token_keep[] = {1, 1, 1, 1, 1}; 
const int type_token_index[] = {47, 48, 49, 50, 51};

// Identificateur nom de variable, de fonction, de procédure etc..
const char* identifier_token[] = { "identifier"} ;
const int identifier_token_keep[] = {1} ;
const int identifier_token_index[] = {53} ;

// Les valeurs littérales de notre langage
const char* literal_token[] = { "integer_literal", "float_literal", "char_literal", "boolean_literal"} ;
const int literal_token_keep[] = {1 , 1, 1, 1, 1} ;
const int literal_token_index[] = {54, 55, 56, 57} ;



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
    // si la fin est un point, on renvoie -1
    if (mot[longueur - 1] == '.') {
        return -1;
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



// la longueur du char est de 1
int estUnChar(char * mot){
    // si mot = a ou b ou ... A ou B ou etc.. ou . ou 0 
    if (strlen(mot) == 1){
        return 1;
    }
    return -1;

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
            printf("line : %d\n", current->line);
            printf("column : %d\n", current->column);
        } else {
            for (int i = 0; i < MAX_LENGTH; i++) {
                if (current->valeur[i] == NULL) {
                    break;
                }
                printf("(%d,%s) ", current->tokenCodageId, current->valeur[i]);
                printf("line : %d\n", current->line);
                printf("column : %d\n", current->column);
            }
            printf("\n");
        }

        // Passez au prochain élément
        current = current->next;
    }
}


int index_token_word( char* mot){
    // si c'ets un boolean, on renvoie 57
    if (estUnBoolean(mot) == 1) {
        return 57;
    }
    // si c'est un float, on renvoie 49
    if (estUnFloat(mot) == 1) {
        return 55;
    }
    // si c'est un entier, on renvoie 48
    else if (estUnEntier(mot) == 1) {
        return 54;
    }
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
    index = comparer_mot(mot, expression_token, expression_token_index, 8);
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
    index = comparer_mot(mot, type_token, type_token_index, 5);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, identifier_token, identifier_token_index, 1);
    if (index != -1) {
        return index;
    }
    index = comparer_mot(mot, literal_token, literal_token_index, 4);
    if (index != -1) {
        return index;
    }
    return 53; // identifier_token

}


void litMotFichier(FILE* fichier, struct linked_list_token_valeur *list_token) {
    int m=0;
    int premierMot = 0; // 0 si c'est le premier mot, 1 sinon
    int line = 0;
    int column = 1;
    struct element_token_valeur *current = list_token->head;
    printf("Liste des tokens :\n");

    if (fichier == NULL) {
        fprintf(stderr, "Invalid file pointer\n");
        exit(EXIT_FAILURE);
    }
    column = 1;
    int caractereActuel;
    char caractere;
    char mot[MAX_LENGTH];
    int i = 0;  // Index du caractère dans le mot

    // Tant qu'on n'est pas à la fin du fichier
    while ((caractereActuel = fgetc(fichier)) != EOF) {
        caractere = (char)caractereActuel;
       
        if (caractere == '\n') {
            line++;
            column = 1;
        } 
        // Si c'est un espace, cela signifie la fin d'un mot
        if (caractere == ' ' || caractere == '\t' || caractere == '\n') {
            // Vérifier le type du mot et ajouter à la liste des tokens
            mot[i] = '\0';  // Ajouter le caractère de fin de chaîne
            i = 0;

            if (estUnFloat(mot) == 1) {
                current->tokenCodageId = 55;
                current->valeur[0] = strdup(mot);
            }
            else if (estUnEntier(mot) == 1) {
                current->tokenCodageId = 54;
                current->valeur[0] = strdup(mot);
            } 
         
            // si il y a un " au début du mot et à la fin du mot et pas au milieu
            else if (estUnChar(mot) == 1) {
                current->tokenCodageId = 56;
                current->valeur[0] = strdup(mot);
            }
            else if (estUnBoolean(mot) == 1) {
                current->tokenCodageId = 57;
                current->valeur[0] = strdup(mot);
            }
           
            
            else {
                current->tokenCodageId = index_token_word(mot);
                if (current->tokenCodageId == 53) {
                    m=0;
                    int longueur = strlen(mot);
                     for (int j=0; j<=longueur-1; j++){
                        if(j>=m){
                        for (int k = j+1;k<=longueur;k++){
                            char* mot_courant = malloc(sizeof(char) * (k - j + 1));
                            strncpy(mot_courant, mot + j, k - j); 
                            mot_courant[k - j] = '\0'; // Null-terminate the string
                            
                            int index = index_token_word(mot_courant);
                              // si c'est : , on regarde le caractère suivant pour voir si on a pas := 
                                if (index == 10 && mot[k] == '='){
                                   continue;
                                }
                        
                            // on fait la même chose avec /=    
                                if (index == 41 && mot[k] == '='){
                                   continue;
                                }
                            // on fait la même chose avec <=
                                if (index == 34 && mot[k] == '='){
                                   continue;
                                }   
                            // on fait la même chose avec >=    
                                if (index == 36 && mot[k] == '='){
                                   continue;
                                }
                            // on fait la même chose pour in et integer donc on regarde si la prohcaine lettre est un t
                                if (index == 15 && mot[k] == 't'){
                                   continue;
                                }
                            char *lettre = malloc(sizeof(char) );
                            lettre[0] = mot[k];
                            // si c'est un entier, on regarde les prochains caractères pour voir si c'est un float 
                            if(index == 54){
                                 printf("mot courant : %s\n", mot_courant);
                                if(lettre[0] == '.'){
                                    int n = k;
                                 while (isdigit(mot[n]) != 0){
                                n++;
                                // on récupère le mot courant 2 et on regarde si c'est un float 
                                char * mot_courant_2 = malloc(sizeof(char) * (n - j + 1));
                                strncpy(mot_courant_2, mot + j, n - j);
                                mot_courant_2[n - j] = '\0'; // Null-terminate the string
                                free(mot_courant_2);
                                
                                }
                                 m=n-1;  }
                                 else if (isdigit(mot[k])==0){
                                        if (m<j){
                                            continue;
                                        }
                                        else {
                                   
                                        // ajoute dans la liste et on passe m à k+1
                                        current->tokenCodageId = index;
                                        current->valeur[0] = strdup(mot_courant);
                                        current->line = line;

                                        current->column = column;
                                        column = column+1;
                                        current->next = malloc(sizeof(struct element_token_valeur));
                                        current = current->next;
                                        current->tokenCodageId = 0;
                                        for (int j = 0; j < 1000; j++) {
                                                current->valeur[j] = NULL;
                                            }

                                            current->line = line;
                                            current->column = column;
                                            column = column+1;
                                            current->next = NULL;
                                            m=k;



                                        }
                                    }
                                   
                            // si c'est un entier
                           }
                                
                            else if (index != 53 && j ==0 && k != longueur){
                              
                                
                                current->tokenCodageId = index;
                                // si ça correspond au token "\'", on met stringValeur à 1
                                if(index == 58 && stringValeur == 0){
                                    stringValeur = 1;
                                }
                                else if (index == 58 && stringValeur == 1){
                                    stringValeur = 0;
                                }
                                
                                

                                
                                current->valeur[0] = strdup(mot_courant);
                                current->line = line;
                                
                                current->column = column;
                                column = column+1;
                                current->next = malloc(sizeof(struct element_token_valeur));
                                current = current->next;
                                current->tokenCodageId = 0;
                                for (int j = 0; j < 1000; j++) {
                                        current->valeur[j] = NULL;
                                    }

                                    current->line = line;
                                column = column+1;
                                current->column = column;
                                    current->next = NULL;
                                    m=k;
                            premierMot = 1;
                            }
                            else if (index !=53 && j!=0 && k == longueur){
                               if (premierMot == 0){
                                // on créer motPremier ajoute mot[0:j-1] dans la liste 
                                char * motPremier = malloc(sizeof(char) * (j + 1));
                                strncpy(motPremier, mot, j);
                                motPremier[j] = '\0'; // Null-terminate the string
                                int indexPremier = index_token_word(motPremier);
                                current->tokenCodageId = indexPremier;
                                current->valeur[0] = strdup(motPremier);
                                current->line = line;

                                current->column = column;
                                column = column+1;
                                current->next = malloc(sizeof(struct element_token_valeur));
                                current = current->next;
                                current->tokenCodageId = 0;
                                for (int j = 0; j < 1000; j++) {
                                        current->valeur[j] = NULL;
                                    }

                                    current->line = line;
                                    column = column+1;
                                    current->column = column;
                                    current->next = NULL;
                                    premierMot = 1;
                                
                               }

                                if(index == 58 && stringValeur == 0){
                                    stringValeur = 1;
                                }
                                else if (index == 58 && stringValeur == 1){
                                    stringValeur = 0;
                                }
                               
                                current->tokenCodageId = index;
                                current->valeur[0] = strdup(mot_courant);
                                m=k;
                                
                            }
                                else if (index !=53 && j!=0 && k != longueur  ){
                                   
                                if (premierMot == 0){
                                // on créer motPremier ajoute mot[0:j-1] dans la liste
                                char * motPremier = malloc(sizeof(char) * (j + 1));
                                strncpy(motPremier, mot, j);
                                motPremier[j] = '\0'; // Null-terminate the string
                                int indexPremier = index_token_word(motPremier);
                                current->tokenCodageId = indexPremier;
                                current->valeur[0] = strdup(motPremier);
                                current->line = line;

                                current->column = column;
                                column = column+1;
                                current->next = malloc(sizeof(struct element_token_valeur));
                                current = current->next;
                                current->tokenCodageId = 0;
                                for (int j = 0; j < 1000; j++) {
                                        current->valeur[j] = NULL;
                                    }

                                    current->line = line;
                                    column = column+1;
                                    current->column = column;
                                    current->next = NULL;
                                    premierMot = 1;
                                }
                               
                               if (index == 55 && isdigit(mot[k])!=0){
                                   
                                   continue;}
                                if(index == 58 && stringValeur == 0){
                                    stringValeur = 1;
                                }
                                else if (index == 58 && stringValeur == 1){
                                    stringValeur = 0;
                                }
                                current->tokenCodageId = index;
                                current->valeur[0] = strdup(mot_courant);
                                current->line = line;
                                
                                current->column = column;
                                column = column+1;
                                current->next = malloc(sizeof(struct element_token_valeur));
                                current = current->next;
                                current->tokenCodageId = 0;
                                for (int j = 0; j < 1000; j++) {
                                        current->valeur[j] = NULL;
                                    }

                                    current->line = line;
                                    current->column = column;
                                    column = column+1;
                                    current->next = NULL;
                                    m=k;
                            }
                            // si c'est un char
                            else if (index==53 && estUnChar(mot_courant)==1 && stringValeur==1 && j==0 && k==longueur){
                                current->tokenCodageId = 51;
                                current->valeur[0] = strdup(mot_courant);
                                premierMot = 1;
                              
                            }
                            else if (index==53 && estUnChar(mot_courant)==1 && stringValeur==1 && j!=0 && k==longueur){
                                if (premierMot == 0){
                                // on créer motPremier ajoute mot[0:j-1] dans la liste
                                char * motPremier = malloc(sizeof(char) * (j + 1));
                                strncpy(motPremier, mot, j);
                                motPremier[j] = '\0'; // Null-terminate the string
                                int indexPremier = index_token_word(motPremier);
                                current->tokenCodageId = indexPremier;
                                current->valeur[0] = strdup(motPremier);
                                current->line = line;

                                current->column = column;
                                column = column+1;
                                current->next = malloc(sizeof(struct element_token_valeur));
                                current = current->next;
                                current->tokenCodageId = 0;
                                for (int j = 0; j < 1000; j++) {
                                        current->valeur[j] = NULL;
                                    }

                                    current->line = line;
                                    column = column+1;
                                    current->column = column;
                                    current->next = NULL;
                                    premierMot = 1;
                                }

                                current->tokenCodageId = 51;
                                current->valeur[0] = strdup(mot_courant);
                                
                            }
                            else if (index==53 && estUnChar(mot_courant)==1 && stringValeur==1 && j!=0 && k!=longueur){
                                if (premierMot == 0){
                                // on créer motPremier ajoute mot[0:j-1] dans la liste
                                char * motPremier = malloc(sizeof(char) * (j + 1));
                                strncpy(motPremier, mot, j);
                                motPremier[j] = '\0'; // Null-terminate the string
                                int indexPremier = index_token_word(motPremier);
                                current->tokenCodageId = indexPremier;
                                current->valeur[0] = strdup(motPremier);
                                current->line = line;

                                current->column = column;
                                column = column+1;
                                current->next = malloc(sizeof(struct element_token_valeur));
                                current = current->next;
                                current->tokenCodageId = 0;
                                for (int j = 0; j < 1000; j++) {
                                        current->valeur[j] = NULL;
                                    }

                                    current->line = line;
                                    column = column+1;
                                    current->column = column;
                                    current->next = NULL;
                                    premierMot = 1;
                                }

                                current->tokenCodageId = 56;
                                current->valeur[0] = strdup(mot_courant);
                                current->line = line;
                                
                                current->column = column;
                                column = column+1;
                                current->next = malloc(sizeof(struct element_token_valeur));
                                current = current->next;
                                current->tokenCodageId = 0;
                                for (int j = 0; j < 1000; j++) {
                                        current->valeur[j] = NULL;
                                    }

                                    current->line = line;
                                   
                                    current->column = column;
                                    column = column+1;
                                    current->next = NULL;
                                    m=k;
                            }
                           
                           
                            
                           
                           
                           
                            

                        

                   }}}
                // on regarde si m<longueur(mot)alors on ajoute mot[m:longueur(mot)] dans la liste
                int longueur_mot = strlen(mot);
                if(m<longueur_mot-1){
                    char * mot_dernier = malloc(sizeof(char) * (longueur_mot - m + 1));
                    strncpy(mot_dernier, mot + m, longueur_mot - m);
                    mot_dernier[longueur_mot - m] = '\0'; // Null-terminate the string
                    int index_dernier = index_token_word(mot_dernier);
                    current->tokenCodageId = index_dernier;
                    current->valeur[0] = strdup(mot_dernier);
                    
                }
                
                
               
                if (premierMot==0){
                    // on najoute le mot avec l'ID 53
                    current->tokenCodageId = 53;
                    current->valeur[0] = strdup(mot);
                }
                premierMot=0;
                }
                
                else {
                    current->valeur[0] = strdup(mot);
                }
        
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

            current->line = line;
           
            current->column = column;
        
            current->next = NULL;
          
            printf("line : %d\n", line);
        } else {
            // Ajouter le caractère au mot
            mot[i++] = caractere;
        }
    }

}
