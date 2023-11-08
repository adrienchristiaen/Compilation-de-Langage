#include "header.h"


struct element_token_valeur {
    //type des tokens
    char * token;
    //valeur des tokens 
    char * valeur;
    struct element_token_valeur * next;
};
// séprarer
struct linked_list_token {
    struct element_token_valeur * head;
};

