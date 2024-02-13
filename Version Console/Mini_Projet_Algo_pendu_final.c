#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define BLUE    "\033[0;34m"
#define RESET   "\033[0m"

typedef struct Noeud {
    char lettre;
    struct Noeud * gauche;
    struct Noeud * droite;
} Noeud;

typedef Noeud * Arbre;

int lireMots(const char *nomFichier, char mots[100][50]) {
    int nbMots = 0;
    FILE *fichier = fopen("Mots.txt", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier, exit lireMots\n");
        return 0;
    }
    while (fscanf(fichier, "%s", mots[nbMots]) == 1) {
        nbMots++;
    }
    fclose(fichier);
    return nbMots;
}

void afficher(Arbre a)
{
if (a != NULL){
    printf("%c \n",a->lettre);
    afficher(a->gauche);
    afficher(a->droite);
   }
}

Arbre creerfeuille(char lettre) {
    Arbre p;
    p = (Arbre) malloc(sizeof(Noeud));
    p->lettre = lettre;
    p->gauche = NULL;
    p->droite = NULL;
    return p;
}

//fonctionnalite : ----

Arbre Ajoutermot(Arbre p,char mot[50],int i)
{
    Arbre k ;
    if (i > strlen(mot)){ return p; }
    if ( p == NULL ){
         p = creerfeuille(mot[i]);
         p = Ajoutermot(p,mot,i);
    }
    else{
            if ( mot[i] < p->lettre ){
                k = creerfeuille(mot[i]);
                k->droite = p;
                p = k;
                p->gauche = Ajoutermot(p->gauche,mot,i+1);
            }else{
                if ( p->lettre == mot[i] ){
                        p->gauche = Ajoutermot(p->gauche,mot,i+1);
                }else{
                        p->droite = Ajoutermot(p->droite,mot,i);
                    }
            }
    }
}

bool recherchemot(Arbre a, char mot[50]) {
    Arbre p = NULL;
    p = a;
    int i = 0;
    while(p != NULL && i <= strlen(mot)) {
        if( p->lettre == mot[i]) {
            if (mot[i] != '\0') {p = p->gauche;}
            i++;
        }else {
            p = p->droite ;
        }
        if (p == NULL) {
            return false;
        }
    }
    return true;
}

void supprimermot(Arbre* a, char mot[50], int i) {
    if ( *a != NULL) {
        if ((*a)->lettre == mot[i]) {
            supprimermot(&((*a)->gauche), mot, i + 1);
            if ( (*a)->gauche == NULL && (*a)->droite == NULL ) {
                free(*a);
                *a = NULL;
            }else if ( (*a)->droite != NULL && (*a)->gauche == NULL) {
                Arbre p = NULL;
                p = *a;
                *a = (*a)->droite;
                free(p);
            }
        }else{
            supprimermot(&((*a)->droite), mot, i);
        }
    }
}


Arbre creer_arbre(Arbre a, char mots[100][50], int nbMots) {
    for(int i=0;i<nbMots;i++)
        {
        a = Ajoutermot(a,mots[i],0);
        }
       return a;
}

void afficherPendu(int nbErreur, int niveau) {
    if (niveau == 1) {
        switch (nbErreur) {
        case 0:
            printf("\n");
            printf("     |--|     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 1:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 2:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 3:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 4:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     -  |     \n");
            printf("    /   |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 5:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     -  |     \n");
            printf("    / \\ |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;
    }
    }else if(niveau == 2) {
        switch (nbErreur) {
        case 0:
            printf("\n");
            printf("     |--|     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 1:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 2:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /   |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;
         case 3:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

         case 4:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 5:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     -  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 6:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     -  |     \n");
            printf("    /   |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 7:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     -  |     \n");
            printf("    / \\ |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;
        }
    }else {
         switch (nbErreur) {
        case 0:
            printf("\n");
            printf("     |--|     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 1:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 2:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /   |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;
         case 3:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

         case 4:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("       |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 5:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     |  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;

        case 6:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     |  |     \n");
            printf("     -  |     \n");
            printf("        |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;
         case 7:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     |  |     \n");
            printf("     -  |     \n");
            printf("       |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;
         case 8:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     |  |     \n");
            printf("     -  |     \n");
            printf("    /   |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;
        case 9:
            printf("\n");
            printf("     |--|     \n");
            printf("     O  |     \n");
            printf("    /|\\ |     \n");
            printf("     -  |     \n");
            printf("    / \\ |     \n");
            printf("        |     \n");
            printf("     ------   \n");
            printf("\n");
            break;
        }


    }

}

//rechercher lettre dans le mot a deviner et remplacer dans la mot cachee
void recherchelettre(char lettre,char mot_a_deviner[50],char mot_cachee[50])
{
    for(int i=0;i<strlen(mot_a_deviner);i++){
        if (mot_a_deviner[i] == lettre){
                mot_cachee[i] = lettre;
        }
    }
}

bool verif(char ch [50],int niveau)
{
    if (niveau == 1){
            if ( strlen(ch) > 4 ) {
                    return false;
            }
            else{
                return true;
            }
    }else if (niveau == 2){
            if (strlen(ch) >= 4 && strlen(ch)<= 7){
                return true;
            }
            else
            {
             return false;
            }
        }else{
            if (strlen(ch) > 7){
                return true;
            }
            else
            {
                return false;
            }
        }
}


char * Selectionner_Mot(Arbre racine,int niv) {
    //parcoursPrefixeIteratif
    char ch[50] = "";
    char sh[50] = "";
    int i = 0; //variable pour parcourir l'arbre
    char mots[100][50] ;
    int j = 0; // le nombre de mots selectionnee selon niveau
    //Pile
    Arbre pile[100];
    int sommet = 0;
    int longueur_maximale;
    switch (niv) {
        case 1:
            longueur_maximale = 3;
            break;
        case 2:
            longueur_maximale = 7;
            break;
        case 3:
            longueur_maximale = INT_MAX;
            break;
        default:
            break;
    }
    pile[sommet] = racine;
    while ( sommet >= 0 ) {
        Noeud* noeudCourant = pile[sommet];
        sommet--;
        if ( noeudCourant == NULL ){
            strncpy(sh,ch,i);
            sh[i] = '\0';
            strcpy(ch,sh);
            i--;
        }else{
            if ( i == longueur_maximale ){
                 if (noeudCourant->lettre == '\0'){
                    if (verif(ch,niv)){

                        strcpy(mots[j],ch);
                        j++;
                    }
                    i--;
                 }
                 else
                     {
                         i--;
                    }
            }
            else{
            ch[i] = noeudCourant->lettre;
            i++;
            if (noeudCourant->lettre == '\0'){
                if (verif(ch,niv)){
                    strcpy(mots[j],ch);
                    j++;
                }
                if (noeudCourant->droite != NULL){
                    sommet++;
                    pile[sommet] = noeudCourant->droite;
                    i--;
                }else{
                    strncpy(sh,ch,i-1);
                    strcpy(ch,sh);
                    i = i-2;
                }
            }
            else{
                sommet++;
                pile[sommet] = noeudCourant->droite;
                if (noeudCourant->gauche != NULL) {
                    sommet++;
                    pile[sommet] = noeudCourant->gauche;
                }

            }
    }
    }

    }
    if (j == 0 ){
        printf("Desolee, il n existe pas du mot dans le niveau %d \n",niv);
        return "";
    }else{
        int indice = rand() % j;
        char mot[50]="";
        return strcpy(mot,mots[indice]);
    }
}

void verifier(int * v,int deb,int fin){

}

void commencer_Jeu_du_pendu(Arbre a,char mots[100][50],int nb)
{
    char * mot_a_deviner;
    int niveau;
    do
    {
        printf(BLUE "Choisir le niveau entre 1 et 3 " RESET "\n");
        scanf("%d",&niveau);
        if ( ! (niveau>=1 && niveau <=3) ){
             printf(RED"Choix invalide" RESET "\n");
        }
    } while (! (niveau>=1 && niveau <=3) );

    int nberreur_max;
    switch (niveau) {
        case 1:
            mot_a_deviner = Selectionner_Mot(a,1);
            nberreur_max = 6;
            break;
        case 2:
            mot_a_deviner = Selectionner_Mot(a,2);
            nberreur_max = 8;
            break;
        case 3:
            mot_a_deviner = Selectionner_Mot(a,3);
            nberreur_max = 10;
            break;
        default:
            break;
    }

    //afficher(a);
    if ( strcmp(mot_a_deviner,"") != 0){
        char mot_cachee[strlen(mot_a_deviner) + 1],mot_cachee2[strlen(mot_a_deviner) + 1];
        for (int i = 0; i < strlen(mot_a_deviner); i++) { mot_cachee[i] = '*';}
        mot_cachee[strlen(mot_a_deviner)] = '\0';
        strcpy(mot_cachee2,mot_cachee);
        int nbErreur = 0;
        char lettre;
        while (nbErreur < nberreur_max && strcmp(mot_cachee,mot_a_deviner)!=0 ) {
            do{
                printf(BLUE "Proposer une lettre " RESET "\n");
                scanf(" %c",&lettre);
            }while ( !(isalpha(lettre)!=0));
            recherchelettre(lettre,mot_a_deviner,mot_cachee);
            printf("----> %s \n",mot_cachee);
            if (strcmp(mot_cachee,mot_cachee2) == 0 ){nbErreur++;}
            strcpy(mot_cachee2,mot_cachee);

            if(nbErreur>0)
            {
                afficherPendu(nbErreur,niveau );
            }
        }
        if (nbErreur < nberreur_max && strcmp(mot_cachee,mot_a_deviner)==0 ){
            printf(GREEN "Vous avez gagne" RESET" \n");
        }
        else{
            printf(RED "Vous avez perdu, le mot a deviner est %s " RESET "\n",mot_a_deviner);
        }
    }
}

void afficherMenu(){
        printf("  ******** Menu **********\n");
        printf(BLUE"---------------------------\n"RESET);
        printf(BLUE"|"RESET"    1. Jouer             "BLUE"|"RESET"\n");
        printf(BLUE"|"RESET"    2. Ajouter mot       "BLUE"|"RESET"\n");
        printf(BLUE"|"RESET"    3. Supprimer mot     "BLUE"|"RESET"\n");
        printf(BLUE"|"RESET"    4. Rechercher mot    "BLUE"|"RESET"\n");
        printf(BLUE"|"RESET"    5. Quitter           "BLUE"|"RESET"\n");
        printf(BLUE"---------------------------\n"RESET);

}


int main() {
    printf("Bienvenue dans le jeu du Pendu!\n\n");
    char mots[100][50];
    int nb = lireMots("Mots.txt", mots);
    Arbre a = NULL;
    a = creer_arbre(a,mots,nb);
    int choix;
    char choixMenu;
    char ch[50];
	do{
        afficherMenu();
        do
        {
            printf("Votre choix: ");
            scanf("%d", &choix);
            if ( ! (choix>=1 && choix<=5) ){
                 printf(RED"Choix invalide" RESET "\n");
                 afficherMenu();
            }
        } while (! (choix>=1 && choix <=5) );


   switch (choix)
    {
        case 1:
            commencer_Jeu_du_pendu(a, mots, nb);
            break;

        case 2:
            printf(BLUE "Donner le mot a ajouter" RESET" \n");
            scanf("%s", ch);
            a = Ajoutermot(a, ch, 0);
            break;

        case 3:
            printf(BLUE"Donner le mot a supprimer " RESET"\n");
            scanf("%s", ch);
            if (recherchemot(a,ch)){
                supprimermot(&a, ch, 0);
            } else {
                printf(RED"Le mot n'existe pas dans le dictionnaire" RESET" \n");
            }
            break;
        case 4:
            printf(BLUE"Donner le mot a rechercher" RESET" \n");
            scanf("%s", ch);
            if (recherchemot(a,ch)) {
                printf(GREEN "Le mot existe dans le dictionnaire" RESET" \n");
            } else {
                printf(RED "Le mot n'existe pas dans le dictionnaire" RESET" \n ");
            }
            break;

        case 5:
            exit(1);
            break;
        default:
            printf(RED"Choix invalide" RESET"\n");
    }
        printf("Voulez-vous continuer a jouer? (O: Oui, N: Non) ");
        scanf(" %c",&choixMenu);
	}
	while(toupper(choixMenu)=='O');
    return 0;
}



