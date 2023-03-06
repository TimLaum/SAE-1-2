/*
#include "stdio.h"
#include "stdlib.h"
#define TAILLE_MAX 1000
int main(int argc, char *argv[]){
    FILE* fichier = NULL;
    int score = 0,age = 0; // Tableau des 3 meilleurs scores
    char nom[20] ,chaine[TAILLE_MAX] = "";;
    fichier = fopen("test.txt", "r");
    if (fichier != NULL)
    {
        do{

            fscanf(fichier, "%s %d %d", &nom, &age, &score);
            printf("Hi %s ! you are %d years old and you have scored %d points in the championship this year, congratulations !\n",nom,age,score );
            }while(fgets(chaine, TAILLE_MAX, fichier) != NULL);
        fclose(fichier);
    }
    return 0;
}
*/