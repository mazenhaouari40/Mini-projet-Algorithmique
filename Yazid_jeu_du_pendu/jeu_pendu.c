#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <emscripten.h>

typedef struct Noeud {
    char lettre;
    struct Noeud * gauche;
    struct Noeud * droite;
} Noeud;

typedef Noeud * Arbre;
//const char *nomFichier
//EMSCRIPTEN_KEEPALIVE
int lireMots(char mots[100][50]) {
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
//EMSCRIPTEN_KEEPALIVE
/*void afficher(Arbre a)
{
if (a != NULL){
    printf("%c \n",a->lettre);
    afficher(a->gauche);
    afficher(a->droite);
   }
}*/
//EMSCRIPTEN_KEEPALIVE
Arbre creerfeuille(char lettre) {
    Arbre p;
    p = (Arbre) malloc(sizeof(Noeud));
    p->lettre = lettre;
    p->gauche = NULL;
    p->droite = NULL;
    return p;
}

//fonctionnalite : ----
//EMSCRIPTEN_KEEPALIVE
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
    return p;
}

//EMSCRIPTEN_KEEPALIVE
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

//suppression
//EMSCRIPTEN_KEEPALIVE
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

EMSCRIPTEN_KEEPALIVE
Arbre creer_arbre(Arbre a, char mots[100][50], int nbMots) {
    for(int i=0;i<nbMots;i++)
        {
        a = Ajoutermot(a,mots[i],0);
        }
       return a;
}

EMSCRIPTEN_KEEPALIVE
void recherchelettre(char lettre,char mot_a_deviner[50],char mot_cachee[50])
{
    printf("recherchelettre mot dev :%s\n",mot_a_deviner);
    printf("recherchelettre lettre:%c\n",lettre);
    for(int i=0;i<strlen(mot_a_deviner);i++){
        if (mot_a_deviner[i] == lettre){
                mot_cachee[i] = lettre;
        }
    }
    printf("recherchelettre cach:%s\n",mot_cachee);
}
EMSCRIPTEN_KEEPALIVE
bool verif(char ch [50],int niveau)
{
    if (niveau == 1){
        if ( strlen(ch) > 4 ) {
            return false;
        }
        else{
            return true;
        }

    }
    else if (niveau == 2){

        if (strlen(ch) >= 4 && strlen(ch)<= 7){
            return true;
        }
        else
        {
         return false;
        }

    }else{

                if (strlen(ch) > 7){
                    printf("chaine =%s \n",ch);
                    return true;
                }
                else
                {
                    return false;
                }
    }
}

EMSCRIPTEN_KEEPALIVE
char * parcoursPrefixeIteratif(Arbre racine,int niv) {
    Arbre pile[100];
    int sommet = 0;
    pile[sommet] = racine;
    char ch[50] = "";
    int i = 0,j = 0;
    char mots[100][50] ;
    while ( sommet >= 0 ) {
        Noeud* noeudCourant = pile[sommet];
        sommet--;
        if ( noeudCourant == NULL ){
            i--;
        }else{
            ch[i] = noeudCourant->lettre;
            i++;
            // complexité ici
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
                    i = i-2;
                }
            }else{
                sommet++;
                pile[sommet] = noeudCourant->droite;
                if (noeudCourant->gauche != NULL) {
                    sommet++;
                    pile[sommet] = noeudCourant->gauche;
                }
            }
        }
    }
    if (j == 0 ){

        return "";
    }else{
        int indice = rand() % j;
        char mot[50]="f";
        return strcpy(mot,mots[indice]);
    }
}




// niveau 1 longueur maximale 4 et lettre qui doit etre commence la chaine
char * niveau1(Arbre a){
    char lettre;

    return parcoursPrefixeIteratif(a,1);
}

char * niveau2(Arbre a){
    return parcoursPrefixeIteratif(a,2);
}

char * niveau3(Arbre a){
    return parcoursPrefixeIteratif(a,3);
}



Arbre a = NULL;
int nbErreur = 0;
char * mot_a_deviner;
char mot_cachee[50],mot_cachee2[50];
char mots[100][50];
int nb;
int jeu_param_initialized = 0;


int initializeArbreFlag = 0;
EMSCRIPTEN_KEEPALIVE
void initializeArbre() {

    int nb = lireMots(mots);
    a = creer_arbre(a, mots, nb);
}
EMSCRIPTEN_KEEPALIVE
char * set_jeu_param(int nb) {
    if (!initializeArbreFlag) {
         initializeArbre();
         initializeArbreFlag = 1;
    }

    printf("run%d...\n",nb);
     switch (nb) {
        case 1:
            mot_a_deviner = niveau1(a);
            break;
        case 2:
            mot_a_deviner = niveau2(a);
            break;
        case 3:
            mot_a_deviner = niveau3(a);
            break;
        default:
            printf("Choix invalide\n");
            break;
    }
    for (int i=0;i<sizeof(mot_cachee);i++) {
        mot_cachee[i] = '\0';
    }

    for (int i = 0; i < strlen(mot_a_deviner); i++) { mot_cachee[i] = '*';}
    return mot_cachee;


}


EMSCRIPTEN_KEEPALIVE
char* graph_jeu_pendu(char lettre[1]) {
    
     printf("jeu lettre %c\n", lettre[0]);
        mot_cachee[strlen(mot_a_deviner)] = '\0';
        strcpy(mot_cachee2,mot_cachee);
        //int nbErreur = 0;

        if (nbErreur < 5 && strcmp(mot_cachee,mot_a_deviner)!=0 ) {
            recherchelettre(lettre[0],mot_a_deviner,mot_cachee);
            printf("----> %s \n",mot_cachee);
            if (strcmp(mot_cachee,mot_cachee2) == 0 ){nbErreur++;}
            printf("mot:%s\n",mot_a_deviner );
            strcpy(mot_cachee2,mot_cachee);
            if (strcmp(mot_cachee,mot_a_deviner)==0) {
                nbErreur = 0;
                return "vous avez gagne!";
            }
            return mot_cachee;
            /*if(nbErreur>0);
            {
                afficherPendu(nbErreur);
            }*/
        }

        else{
            nbErreur = 0;
            char * message2;
             strcpy(message2,"vous avez perdu! le mot est : ");

            //return strcat("vous avez perdu! le mot est : " ,mot_a_deviner);

    return  strcat(message2,mot_a_deviner);
        }

}


int niv; // Global pointer to store the user input


EMSCRIPTEN_KEEPALIVE
char* set_user_input(int nb) {

    niv = nb;
    printf("%d\n",niv);
    jeu_param_initialized = 1; // Set the flag to indicate initialization
    return set_jeu_param(niv);

}
// Function to initialize 'a'


EMSCRIPTEN_KEEPALIVE
int graph_recherche(char mot[50]) {
    if (!initializeArbreFlag) {
         initializeArbre();
         initializeArbreFlag = 1;
    }
    printf("%d", recherchemot(a,mot));
    return recherchemot(a,mot);
}



EMSCRIPTEN_KEEPALIVE
char* graph_supprimer(char mot[50]) {
    if (!initializeArbreFlag) {
         initializeArbre();
         initializeArbreFlag = 1;
    }
    supprimermot(&a,mot,0);
    return "mot supprimer";
}
EMSCRIPTEN_KEEPALIVE
char* graph_Ajouter(char mot[50]) {
    if (!initializeArbreFlag) {
         initializeArbre();
         initializeArbreFlag = 1;
    }
    a = Ajoutermot(a,mot,0);
    return "mot ajouter";
}

EMSCRIPTEN_KEEPALIVE
char* get_user_input() {
    return mot_a_deviner;
}


int main() {

    return 0;
}

