#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
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
void afficher(Arbre a)
{
if (a != NULL){
    printf("%c \n",a->lettre);
    afficher(a->gauche);
    afficher(a->droite);
   }
}
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
void afficherPendu(int nbErreur) {
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
    char ch[50] = "";
    char sh[50] = "";
    int i = 0; //variable pour parcourir l'arbre
    char mots[100][50] ;
    int j = 0; // le nombre de mots selectionnée selon niveau
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
                        printf("--> %s \n",ch);
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
                    printf("----> %s \n",ch);
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
        printf("Desolee il n existe pas du mot dans le niveau %d \n",niv);
        return "";
    }else{
        int indice = rand() % j;
        char mot[50]="";
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



/*void commencer_Jeu_du_pendu(Arbre a,char mots[100][50],int nb)
{
    int niveau;
    char * mot_a_deviner;
    printf("Choisir le niveau \n");
    scanf("%d",&niveau);

    switch (niveau) {
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

    //afficher(a);
    if ( strcmp(mot_a_deviner,"") != 0){

        printf(" mot ---> %s \n",mot_a_deviner);

        char mot_cachee[strlen(mot_a_deviner) + 1],mot_cachee2[strlen(mot_a_deviner) + 1];
        for (int i = 0; i < strlen(mot_a_deviner); i++) { mot_cachee[i] = '*';}
        mot_cachee[strlen(mot_a_deviner)] = '\0';
        strcpy(mot_cachee2,mot_cachee);
        int nbErreur = 0;
        char lettre;
        while (nbErreur < 5 && strcmp(mot_cachee,mot_a_deviner)!=0 ) {
            printf("Proposer une lettre \n");
            scanf(" %c",&lettre);
            recherchelettre(lettre,mot_a_deviner,mot_cachee);
            printf("----> %s \n",mot_cachee);
            if (strcmp(mot_cachee,mot_cachee2) == 0 ){nbErreur++;}
            strcpy(mot_cachee2,mot_cachee);

            if(nbErreur>0)
            {
                afficherPendu(nbErreur);
            }
        }
        if (nbErreur < 5 && strcmp(mot_cachee,mot_a_deviner)==0 ){
            printf("vous avez gagne \n");
        }
        else{
            printf("vous avez perdu \n");
        }
    }
}*/


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
    nbErreur = 0; 
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
            char * message;
            strcpy(message, "vous avez perdu! le mot est : " );
            return strcat(message ,mot_a_deviner);
        }
    
}
EMSCRIPTEN_KEEPALIVE
int get_NbErreur() {
    return nbErreur;
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




/*int main() {
    printf("Bienvenue dans le jeu du Pendu!\n\n");
    char mots[100][50];
    int nb = lireMots(mots);
    Arbre a = NULL;
    a = creer_arbre(a,mots,nb);
    int choix;
    char choixMenu;
    char ch[50];
	do{
        printf("    menu  \n ");
        printf("1. Jouer \n");
        printf("2. Ajouter mot \n");
        printf("3. Supprimer mot \n");
        printf("4. Rechercher mot \n");
        printf("5. Quitter \n");

        printf("votre choix \n");
        scanf("%d",&choix);

   switch (choix)
{
    case 1:
        commencer_Jeu_du_pendu(a, mots, nb);
        break;

    case 2:
        printf("donner le mot a ajouter \n");
        scanf("%s", ch);
        a = Ajoutermot(a, ch, 0);
        //affiche(a);
        break;

    case 3:
        printf("donner le mot a supprimer \n");
        scanf("%s", ch);
        if (recherchemot(a, ch)){
            supprimermot(&a, ch, 0);
        } else {
            printf("mot n'existe pas ");
        }
        break;

    case 4:
        printf("donner le mot a rechercher \n");
        scanf("%s", ch);
        if (recherchemot(a,ch)) {
            printf("le mot existe dans le dictionnaire \n");
        } else {
            printf("le mot n'existe pas dans le dictionnaire \n ");
        }
        break;

    case 5:
        exit(1);
        break;
    default:
        printf("Choix invalide\n");
}
        printf("Voulez-vous continuer a jouer? (O: Oui, N: Non) ");
        scanf(" %c",&choixMenu);
	}
	while(toupper(choixMenu)=='O');
    return 0;
}*/
