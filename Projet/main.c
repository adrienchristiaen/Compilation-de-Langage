#include "analyseur_lexical.h"




// ouvrir le fichier ada_test.txt
FILE* fichier = NULL;




int main(){

    fichier = fopen("ada_test.txt", "r+");
  
    // supprimer les commentaires 
    // void supprimer_commentaires(fichier); enlever le commentaire quand on aura créer la fonction 
    // FILE *fichier_entree = fopen("ada_test.txt", "r");
    //if (fichier_entree == NULL) {
        //perror("Erreur lors de l'ouverture du fichier d'entrée");
        //return 1;
    //}

    // Créer un nouveau fichier de sortie en mode écriture
   // FILE *fichier_sortie = fopen("ada_sans_commentaires.txt", "w");
   // if (fichier_sortie == NULL) {
        //perror("Erreur lors de la création du fichier de sortie");
        //fclose(fichier_entree);
        //return 1;
    //}

    // Appeler la fonction pour supprimer les commentaires
    //supprimer_commentaires(fichier_entree, fichier_sortie);

    // Fermer les fichiers
    //fclose(fichier_entree);
   // fclose(fichier_sortie);

    // Afficher un message de réussite
    //printf("Les commentaires ont été supprimés avec succès. Le résultat est dans le fichier 'ada_sans_commentaires.txt'\n");

    //return 0;
    //Lana : j'ai mis en commentaires ce que je voulais utiliser pour tester la fonction met pb de "double déclarations" sur header.h quand je compile/execute que je n'arrive pas à résoudre

    // creer la liste vide element_token_valeur
    struct linked_list_token_valeur * list_token = malloc(sizeof(struct linked_list_token_valeur));
    struct element_token_valeur * element_token = malloc(sizeof(struct element_token_valeur));

    // initialiser la liste vide
    element_token->tokenCodageId = 0;
    element_token->valeur = NULL;
    element_token->line = 0;
    element_token->column = 0;
    element_token->next = NULL;
    list_token->head = element_token;
    //test estUnEntier
    char * mot = "123";
    int test = estUnEntier(mot);
    printf("%d", test);
    // utiliser la fonction tokeniser
  

    // printf le resultat 
    fclose(fichier);
    return 0;
}

