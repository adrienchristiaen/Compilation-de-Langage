#include "fichier.h"
#include "declstar.h"
#include "instrplus.h"
int Fichier(struct linked_list_token_valeur * list_token){
  int valider = 1; // vaut 1 si le fichier Ada est valide et -1 sinon
  struct element_token_valeur * element_token = malloc(sizeof(struct element_token_valeur));

  // With
  element_token = list_token->head;
  if (element_token->tokenCodageId!=1){
    printf(GREEN"Erreur : le fichier Ada ne commence pas par un with\n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // Nom du fichier
  element_token = element_token->next;
  if (element_token->tokenCodageId!=60){
    printf(GREEN"Erreur : le nom du fichier n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // ;
  element_token = element_token->next;
  if(element_token->tokenCodageId!=5){
    printf(BLUE"Erreur : ça ne contient pas de ';' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // Use
  element_token = element_token->next;
  if(element_token->tokenCodageId!=2){
    printf(GREEN"Erreur : Il faut le mot use \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // Nom du fichier
  element_token = element_token->next;
  if(element_token->tokenCodageId!=60){
    printf(GREEN"Erreur : le nom du fichier n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // ;
  element_token = element_token->next;
  if(element_token->tokenCodageId!=5){
    printf(BLUE"Erreur :ça ne contient pas de ';' \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // Procedure
  element_token = element_token->next;
  if(element_token->tokenCodageId!=3){
    printf(GREEN"Erreur : Il faut le mot procedure \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // Nom de la procedure
  element_token = element_token->next;
  if(element_token->tokenCodageId!=53){
    printf(RED"Erreur : le nom de la procedure n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // Is
  element_token = element_token->next;
  if(element_token->tokenCodageId!=4){
    printf(GREEN"Erreur : Il faut le mot is \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // On appelle la fonction Declstar
  element_token = element_token->next;
  valider = Declstar(element_token);
  if (valider==-1){
    return -1;
  }

  // begin
  if (element_token->tokenCodageId !=12){
    printf(GREEN"Erreur : Il faut le mot begin \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // On appelle la fonction Instrplus
  valider = Instrplus(element_token);
  if (valider==-1){
    return -1;
  }

  // end
  if (element_token->tokenCodageId !=13){
    printf(GREEN"Erreur : Il faut le mot end \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  // ; 
  element_token = element_token->next;
  if (element_token->tokenCodageId !=5){
    printf(BLUE"Erreur : Il faut le mot ; \n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  element_token = element_token->next;
  // fin du fichier
  if (element_token->tokenCodageId !=0){
    printf(GREEN"Erreur : Le fichier doit se terminer\n Ligne : %d\n Colonne : %d\n"RESET,element_token->line,element_token->column);
    return -1;
  }

  return valider;
}