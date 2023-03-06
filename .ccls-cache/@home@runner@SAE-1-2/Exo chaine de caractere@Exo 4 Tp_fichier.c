#include "stdio.h"
#include "stdlib.h"

int main(){
    FILE* fichier = NULL;
    int annee;
    char mois[20],nom[20],prenom[20];
    fichier = fopen("test.txt", "a+");
    if (fichier != NULL) {
        printf("\nQuel est votre nom,prenom,mois de naissance et annee de naissance ?");
        scanf("%s %s %s %d",&nom,&prenom, &mois,&annee);
        fprintf(fichier, "Bonjour cher(e) %s %s\nL'année %d fut donc éclairée par votre arrivée\nEt chaque mois de %s pour longtemps sera fêté\n", prenom,nom,annee,mois);
        fclose(fichier);
    }
    return 0;
}
*/