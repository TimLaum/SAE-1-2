#include "stdio.h"
#include "stdlib.h"
/*
int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
    fichier = fopen("test.txt", "r");
    if (fichier != NULL)
    {
        for (int i = 0; i < 3 ; ++i) {
        // Boucle de lecture des caractères un à un
        caractereActuel = fgetc(fichier); // On lit le 1er caractère

            while (caractereActuel != EOF) {
                printf("%c", caractereActuel); // On l'affiche
                caractereActuel = fgetc(fichier); // On lit le caractère
            }
            rewind(fichier);
        }
        fclose(fichier);
    }
    return 0;
}
*/