#include "fichier.h"
#include "declstar.h"
#include "instrplus.h"
int Fichier(struct linked_list_token_valeur * list_token, struct Node * root){

  root->children = (struct Node**)malloc(16 * sizeof(struct Node*));
   
  int valider = 1; // vaut 1 si le fichier Ada est valide et -1 sinon
  struct element_token_valeur * element_token = malloc(sizeof(struct element_token_valeur));

  // With
  element_token = list_token->head;
  if (element_token->tokenCodageId!=1){
    printf(GREEN"Erreur : le fichier Ada ne commence pas par un with\n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
   root->children[0] = createNode("with", root);

  // Nom du fichier
  element_token = element_token->next;
  if (element_token->tokenCodageId!=60){
    printf(GREEN"Erreur : le nom du fichier n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
   root->children[1] = createNode(element_token->valeur[0], root);

  // ;
  element_token = element_token->next;
  if(element_token->tokenCodageId!=5){
    printf(BLUE"Erreur : ça ne contient pas de ';' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root->children[2] = createNode(";", root);

  // Use
  element_token = element_token->next;
  if(element_token->tokenCodageId!=2){
    printf(GREEN"Erreur : Il faut le mot use \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root ->children[3] = createNode("use", root);

  // Nom du fichier
  element_token = element_token->next;
  if(element_token->tokenCodageId!=60){
    printf(GREEN"Erreur : le nom du fichier n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root->children[4] = createNode(element_token->valeur[0], root);


  // ;
  element_token = element_token->next;
  if(element_token->tokenCodageId!=5){
    printf(BLUE"Erreur :ça ne contient pas de ';' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root->children[5] = createNode(";", root);

  // Procedure
  element_token = element_token->next;
  if(element_token->tokenCodageId!=3){
    printf(GREEN"Erreur : Il faut le mot procedure \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root->children[6] = createNode("procedure", root);

  // Nom de la procedure
  element_token = element_token->next;
  if(element_token->tokenCodageId!=53){
    printf(RED"Erreur : le nom de la procedure n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root->children[7] = createNode(element_token->valeur[0], root);

  // Is
  element_token = element_token->next;
  if(element_token->tokenCodageId!=4){
    printf(GREEN"Erreur : Il faut le mot is \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root->children[8] = createNode("is", root);
  
  // On appelle la fonction Declstar
  element_token = element_token->next;
  root->children[9] = createNode("DECLSTAR", root);
  valider = Declstar(&element_token, root->children[9]);
  if (valider==-1){
    return -1;
  }
  // begin
  
  if (element_token->tokenCodageId !=12){
    printf(GREEN"Erreur : Il faut le mot begin \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root->children[10] = createNode("begin", root);
  (element_token) = (element_token)->next;

  root->children[11] = createNode("INSTRPLUS", root);
  
  // On appelle la fonction Instrplus
  valider = Instrplus(&element_token, root->children[11]);
  if (valider==-1){
    return -1;
  }

  // end
  if (element_token->tokenCodageId !=9){
    printf(GREEN"Erreur : Il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  root->children[12] = createNode("end", root);

  element_token = element_token->next;

    // identinterro
  if (element_token->tokenCodageId == 53){
    root->children[13] = createNode(element_token->valeur[0], root);
    element_token = element_token->next;

    if (element_token->tokenCodageId != 5){
      printf(BLUE"Erreur : Il faut le mot ; \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
      return -1;
    }

    root->children[14] = createNode(";", root);
    root->children[15] = createNode("EOF", root);
    root->numChildren = 16;
  }
  else if(element_token->tokenCodageId == 5){
    root->children[13] = createNode(";", root);
    root->children[14] = createNode("EOF", root);
  }
  else if (element_token->tokenCodageId !=5){
    printf(BLUE"Erreur : Il faut le mot ; \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  element_token = element_token->next;

  // fin du fichier
  if (element_token->tokenCodageId !=0){
    printf(GREEN"Erreur : Le fichier doit se terminer\n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }
  // Si on arrive ici, le fichier est valide
  printf(BLUE"Le fichier est valide !!!!!\n"RESET);
  return valider;
}