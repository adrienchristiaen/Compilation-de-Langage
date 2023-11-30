#include "analyseur_lexical.h"




// ouvrir le fichier ada_test.txt
FILE* fichier = NULL;
// creer le fichier vide ada_sans_commentaires.txt
FILE* fichier_sortie = NULL;
// creer le fichier vide ada_sans_commentaires.txt pour lire
FILE* fichier_sortie_lecture = NULL;



int main(){
     char * mot = "333.33";
    int a;

    a=estUnFloat(mot);
    printf("%d\n", a);
    fichier = fopen("ada_test.txt", "r+");
    // ouvrir le fichier ada_sans_commentaires.txt
    fichier_sortie = fopen("ada_sans_commentaires.txt", "w+");

    supprimer_commentaires(fichier, fichier_sortie);
    // fermer le fichier ada_test.txt
    fclose(fichier);
    // fermer le fichier ada_sans_commentaires.txt
    fclose(fichier_sortie);
    fichier_sortie_lecture = fopen("ada_sans_commentaires.txt", "r+");


    struct linked_list_token_valeur * list_token = malloc(sizeof(struct linked_list_token_valeur));
    struct element_token_valeur * element_token = malloc(sizeof(struct element_token_valeur));

   

    // initialiser la liste vide
    element_token->tokenCodageId = 0;
    for (int i = 0; i < 1000; i++){
        element_token->valeur[i] = NULL;
    }
    element_token->line = 0;
    element_token->column = 0;
    element_token->next = NULL;
    list_token->head = element_token;

     struct linked_list_token_valeur * list_token_recopie = malloc(sizeof(struct linked_list_token_valeur));
    struct element_token_valeur * element_token_recopie = malloc(sizeof(struct element_token_valeur));
    // initialisaer la liset vide 
    element_token_recopie->tokenCodageId = 0;
    for (int i = 0; i < 1000; i++){
        element_token_recopie->valeur[i] = NULL;
    }
    element_token_recopie->line = 0;
    element_token_recopie->column = 0;
    element_token_recopie->next = NULL;
    list_token_recopie->head = element_token_recopie;
    // test la fonction litMotFichier
    litMotFichier(fichier_sortie_lecture, list_token);
    afficher_liste_tokens(list_token);
   
    

    // fermer le fichier ada_sans_commentaires.txt
    fclose(fichier_sortie_lecture);
    return 0;
}

