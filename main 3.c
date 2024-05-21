#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVRES 100
#define MAX_TITRE_LEN 100
#define MAX_AUTEUR_LEN 50
#define MAX_ISBN_LEN 13
#define MAX_CATEGORIE_LEN 50

// D�finition de la structure Livre
typedef struct {
    char titre[MAX_TITRE_LEN];
    char auteur[MAX_AUTEUR_LEN];
    char ISBN[MAX_ISBN_LEN];
    char categorie[MAX_CATEGORIE_LEN];
} Livre;

// Fonction pour ajouter un livre � la biblioth�que
void ajouterLivre(Livre *bibliotheque, int *nbLivres) {
    if (*nbLivres >= MAX_LIVRES) {
        printf("La biblioth�que est pleine.\n");
        return;
    }

    // Demander les informations sur le livre � l'utilisateur
    printf("Entrez le titre du livre : ");
    scanf("%s", bibliotheque[*nbLivres].titre);

    printf("Entrez l'auteur du livre : ");
    scanf("%s", bibliotheque[*nbLivres].auteur);

    printf("Entrez l'ISBN du livre : ");
    scanf("%s", bibliotheque[*nbLivres].ISBN);

    printf("Entrez la cat�gorie du livre : ");
    scanf("%s", bibliotheque[*nbLivres].categorie);

    (*nbLivres)++;
}

// Fonction pour afficher tous les livres dans la biblioth�que
void afficherLivres(Livre *bibliotheque, int nbLivres) {
    if (nbLivres == 0) {
        printf("La biblioth�que est vide.\n");
        return;
    }

    printf("Liste des livres :\n");
    for (int i = 0; i < nbLivres; i++) {
        printf("Titre : %s, Auteur : %s, ISBN : %s, Cat�gorie : %s\n",
               bibliotheque[i].titre, bibliotheque[i].auteur, bibliotheque[i].ISBN, bibliotheque[i].categorie);
    }
}

// Fonction pour supprimer un livre de la biblioth�que en utilisant son ISBN
void supprimerLivre(Livre *bibliotheque, int *nbLivres, char *ISBN) {
    int index = -1;
    for (int i = 0; i < *nbLivres; i++) {
        if (strcmp(bibliotheque[i].ISBN, ISBN) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // D�placer les livres d'une position vers la gauche pour remplir l'emplacement supprim�
        for (int i = index; i < *nbLivres - 1; i++) {
            bibliotheque[i] = bibliotheque[i + 1];
        }
        (*nbLivres)--;
        printf("Le livre avec l'ISBN %s a �t� supprim�.\n", ISBN);
    } else {
        printf("Aucun livre trouv� avec l'ISBN %s.\n", ISBN);
    }
}

// Fonction pour compter le nombre de livres dans la biblioth�que
int compterLivres(Livre *bibliotheque, int nbLivres) {
    return nbLivres;
}

// Fonction pour �crire les livres dans un fichier
void ecrireLivresDansFichier(Livre *bibliotheque, int nbLivres, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < nbLivres; i++) {
        fprintf(fichier, "Titre : %s, Auteur : %s, ISBN : %s, Cat�gorie : %s\n",
                bibliotheque[i].titre, bibliotheque[i].auteur, bibliotheque[i].ISBN, bibliotheque[i].categorie);
    }

    fclose(fichier);
}

// Fonction principale
int main() {
    Livre bibliotheque[MAX_LIVRES];
    int nbLivres = 0;
    int choix;

    do {
        // Affichage du menu
        printf("\nMenu :\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher tous les livres\n");
        printf("3. Supprimer un livre\n");
        printf("4. Compter les livres\n");
        printf("5. Ecrire les livres dans un fichier\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        // Traitement en fonction du choix de l'utilisateur
        switch (choix) {
            case 1:
                ajouterLivre(bibliotheque, &nbLivres);
                break;
            case 2:
                afficherLivres(bibliotheque, nbLivres);
                break;
            case 3:
                if (nbLivres == 0) {
                    printf("La biblioth�que est vide. Impossible de supprimer un livre.\n");
                } else {
                    char ISBN[MAX_ISBN_LEN];
                    printf("Entrez l'ISBN du livre � supprimer : ");
                    scanf("%s", ISBN);
                    supprimerLivre(bibliotheque, &nbLivres, ISBN);
                }
                break;
            case 4:
                printf("Nombre total de livres dans la biblioth�que : %d\n", compterLivres(bibliotheque, nbLivres));
                break;
            case 5:
                if (nbLivres == 0) {
                    printf("La biblioth�que est vide. Impossible d'�crire dans le fichier.\n");
                } else {
                    char nomFichier[100];
                    printf("Entrez le nom du fichier dans lequel vous voulez �crire : ");
                    scanf("%s", nomFichier);
                    ecrireLivresDansFichier(bibliotheque, nbLivres, nomFichier);
                    printf("Les livres ont �t� �crits dans le fichier avec succ�s.\n");
                }
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choix != 0);

    return 0;
}



