#include "analyseur_lexical.h"



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

