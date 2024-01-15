#include "fichier.h"
#include "instrplus.h"

int Boucle2 ( struct element_token_valeur ** element_token, struct Node * root) {
    root->children = (struct Node**)malloc(2 * sizeof(struct Node*));
    int valider ;
    // BOUCLE2 ->  else INSTRPLUS  
    if ((*element_token)->tokenCodageId != 27){

        printf(GREEN"Erreur : il faut un 'else' \n Ligne : %d\n Colonne : %d\n"RESET,(*element_token)->line,(*element_token)->column);
        return -1;
    }
    root->children[0] = createNode("else", root);


    (*element_token) = (*element_token)->next;
    // INSTRPLUS
      root->children[1] = createNode("INSTRPLUS", root);
    valider = Instrplus(element_token, root->children[1]);
    if (valider == -1){
        return -1;
    }
    root->numChildren = 2;
    
    return valider;
}