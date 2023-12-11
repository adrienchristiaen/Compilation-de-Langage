#include "fichier.h"
#include "../analyseur_lexical.h"
int Fichier(int token[], int ligne[],int colonne[]){
    // taille du tableau
    int taille = 0;
    while (ligne[taille] != 0) {
        taille++;
    }

    int valider=1;
   if (token[0]!=1){
    printf(GREEN"Erreur : le fichier Ada ne commence pas par un with\n Ligne : %d\n Colonne : %d\n"RESET,ligne[0],colonne[0]);
    return -1;
   }
   if (token[1]!=60){
    printf(GREEN"Erreur : le nom du fichier n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,ligne[1],colonne[1]);
    return -1;
   }
   if(token[2]!=5){
    printf(BLUE"Erreur : ça ne contient pas de ';' \n Ligne : %d\n Colonne : %d\n"RESET,ligne[2],colonne[2]);
    return -1;
   }
    if(token[3]!=2){
     printf(GREEN"Erreur : Il faut le mot use \n Ligne : %d\n Colonne : %d\n"RESET,ligne[3],colonne[3]);
     return -1;
   }
    if(token[4]!=60){
     printf(GREEN"Erreur : le nom du fichier n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,ligne[4],colonne[4]);
     return -1;
   }
   if(token[5]!=5){
     printf(BLUE"Erreur :ça ne contient pas de ';' \n Ligne : %d\n Colonne : %d\n"RESET,ligne[5],colonne[5]);
     return -1;
   }
   if(token[6]!=3){
     printf(GREEN"Erreur : Il faut le mot procedure \n Ligne : %d\n Colonne : %d\n"RESET,ligne[6],colonne[6]);
     return -1;
   }
    if(token[7]!=53){
     printf(RED"Erreur : le nom de la procedure n'est pas le bon \n Ligne : %d\n Colonne : %d\n"RESET,ligne[7],colonne[7]);
     return -1;
     }
    if(token[8]!=4){
        printf(GREEN"Erreur : Il faut le mot is \n Ligne : %d\n Colonne : %d\n"RESET,ligne[8],colonne[8]);
        return -1;
    }

   
   
   return valider;
}
