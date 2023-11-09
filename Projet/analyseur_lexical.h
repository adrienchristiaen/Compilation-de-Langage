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
