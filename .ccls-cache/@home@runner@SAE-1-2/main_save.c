/*
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 1000
//MAX_BUFFER_SIZE définit la taille maximale allouable 
struct Personnes {
  char forename[25], firstname[25], age[3], country[50], departement[6],
      time[3], family[15];
};

void ecriture() {//La fonction permet d'écrire dans le fichier clients.csv
  FILE *fp =fopen("clients.csv", "a"); // ouverture / création du fichier clients.csv

  char forename[25] = "", firstname[25] = "", age[3] = "", country[50] = "",
       departement[6] = "", time[3] = "", family[15] = "";
  int i;
  printf("\n--------------------------------------\n");
  printf("\n     Programme d'ajout de client \n");
  printf("\n--------------------------------------\n\n");
  printf("\nVeuillez saisir le prenom du client ou q si vous voulez quitter : ");
  scanf("%[^\n]s", forename);
  if (strcmp(forename, "q") == 0) {
    return;
  } else {
    printf("\nVeuillez saisir le nom du client : ");
    scanf("%[^\n]s", firstname);
    printf("\nVeuillez saisir l'age du client : ");
    scanf("%[^\n]s", age);
    printf("\nVeuillez saisir le pays du client : ");
    scanf("%[^\n]s", country);
    printf("\nVeuillez saisir le departement du client : ");
    scanf("%[^\n]s", departement);
    printf("\nVeuillez saisir le temps de sejour du client (en jour) : ");
    scanf("%[^\n]s", time);
    printf("\nVeuillez saisir le nombre de membres avec le client : ");
    scanf("%[^\n]s", family);
    fprintf(fp, "\n%s,%s,%s,%s,%s,%s,%s", forename, firstname, age, country,departement, time, family);//Écriture des informations dans le fichier
    fclose(fp); // Fin de l'écriture
  }
}

void lecture_fichier() {
  FILE *fp;
  fp = fopen("clients.csv", "r");
  if (!fp)
    ecriture();
  else {
    char buffer[MAX_BUFFER_SIZE];

    int row = 0;
    int column = 0;
    printf("\n--------------------------------------\n");
    printf("\n Programme de lecture de client \n");
    printf("\n--------------------------------------\n\n");

    while (fgets(buffer, MAX_BUFFER_SIZE, fp)) {
      column = 0;
      char *value = strtok(buffer, ", ");
      row++;
      while (value) {
        switch (column) { // parcourt du fichier selon les colonnes grâce au tableau qui permet d'avoir nos informations indexées
        case 0:
          printf("%d) Prenom :", row);
          break;
        case 1:
          printf(" / Nom :");
          break;
        case 2:
          printf(" / Age :");
          break;
        case 3:
          printf(" / Pays :");
          break;
        case 4:
          printf(" / Departement :");
          break;
        case 5:
          printf(" / Temps de sejour :");
          break;
        case 6:
          printf(" / Nombre de membres :");
          break;
        }

        printf("%s", value); // printf en dehors du switch pour éviter une répétition inutile qui prendrai plus de lignes

        value = strtok(NULL, ", ");
        column++;
      }
      printf("\n");
    }
    fclose(fp);
  }
}

void createTab(struct Personnes tab[30], int *rowMax) {//La procédure permet de créer un tableau d'élément de type structures Personnes
  int row = 0, column = 0;
  FILE *fp = fopen("clients.csv", "r");
  if (!fp)//Vérifie si le fichier s'est bien ouvert
    printf("Can't open file\n");
  else {
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, MAX_BUFFER_SIZE, fp)) {//Une boucle qui va permettre d'initialiser le tableau de structures Personnes avec les valeurs du fichier clients.csv
      row++;
      column = 0;
      char *value = strtok(buffer, ", ");
      while (value) {//tant que la valeur n'est pas nulle (donc qu'il y a encore des données a parcourir)
        switch (column) {//insertion des informations du fichier selon les colonnes dans le tableau 
        case 0:
          strcpy(tab[row].forename, value);
          break;
        case 1:
          strcpy(tab[row].firstname, value);
          break;
        case 2:
          strcpy(tab[row].age, value);
          break;
        case 3:
          strcpy(tab[row].country, value);
          break;
        case 4:
          strcpy(tab[row].departement, value);
          break;
        case 5:
          strcpy(tab[row].time, value);
          break;
        case 6:
          strcpy(tab[row].family, value);
          break;
        }
        value = strtok(NULL, ",");//value prend la valeur de l'élement et s'arrête a la prochaine virgule (la virgule permet de prendre en compte des string composés de plusieurs mots)
        column++;
      }
    }

    fclose(fp);
  }
  *rowMax = row;//On passe par adresse rowMax qui permet d'avoir le nombre de ligne max
}

void searchClient(int *compt, int *ligne,int verif) {//La fonction permet de rechercher un client par son nom en passant par un traitement de données par tableau de type Personnes
  FILE *fp;
  fp = fopen("clients.csv", "r");
  char searchFN[25];
  struct Personnes tab[30];
  int row = 1, cond = 0, rowMax = 0;
  *compt = 0;
  if(verif==0){
  printf("\n--------------------------------------\n");
  printf("\n Programme de recherche de client \n");
  printf("\n--------------------------------------\n\n");
  }
  printf("\nDonnez le nom de la personne recherchee ou q si vous voulez "
         "quitter :");
  scanf("\n%[^\n]s", searchFN);// Le %[^\n]s permet de chercher des chaînes de caractères avec des espaces
  if (strcmp(searchFN, "q") == 0) {//Condition permettant de quitter la fonctions si on entre la lettre q
    return;
  }
  if (!fp)
    ecriture();
  else {
    createTab(tab, &rowMax);//appel de la fonction pour créer un tableau de type Personnes pour séquenter nos données
    while (row <= rowMax) {//Boucle pour parcourir tout le tableau
      if (strcmp(searchFN, tab[row].firstname) == 0) {//Compare chaque nom du tableau avec le mot rechercher(seachFN)
        //Affichage de ou des personnes trouvés
        printf("Ligne %d : \n", row);
        printf("%s", tab[row].forename);
        printf(" %s", tab[row].firstname);
        printf(" %s", tab[row].age);
        printf(" %s", tab[row].country);
        printf(" %s", tab[row].departement);
        printf(" %s", tab[row].time);
        printf(" %s", tab[row].family);
        *ligne = row;//On passe par adresse la variable ligne qu'on initialise avec la variable row pour pouvoir récupérer hors de la procédure la ligne d'une nom recherché
        row++;
        cond = 1;
        *compt = *compt + 1;
      } else {
        row++;
      }
    }
    if (cond == 0) {
      printf("\nIl n'y a personne possedant ce nom.");
    }
  }
  fclose(fp);
}

void retireClient() {//La fonction permet de supprimer un client du fichier clients.csv
  FILE *fp;
  FILE *fpswitch;
  fp = fopen("clients.csv", "r");
  char searchFN[25];
  struct Personnes tab[30];
  int row = 1, rowMax = 0, compt = 0, ligne = 0, choix = 1;
  if (!fp)
    ecriture();//Appel de la fonction ecriture
  else {
    printf("\n--------------------------------------\n");
    printf("\n Programme de suppression de client \n");
    printf("\n--------------------------------------\n\n");
    searchClient(&compt, &ligne,1);//Appel de la fonction de recherche dans client
    if (ligne != 0) {
      fpswitch = fopen("cswitch.csv", "a");//Créer et ouvre le fichier cswitch.csv qui va servir de nouveau clients.csv après la fin de la fonction
      createTab(tab, &rowMax);
      if (compt > 1) {//Condition permettant de choisir le client que l'on veut supprimer si il y plusieurs
        printf("\nDonnez la ligne du client que vous souhaitez supprimer ou "
               "ecrivez 0 pour quitter: ");
        scanf("%d", &ligne);
      }
      for (row = 1; row <= rowMax; row++) {//Parcours la table de Personnes en entier et écrit dans le fichier cswitch.csv tous les clients à part celui que l'on veut supprimer
        if (row != ligne) {
          fprintf(fpswitch, "%s,%s,%s,%s,%s,%s,%s", tab[row].forename,
                  tab[row].firstname, tab[row].age, tab[row].country,
                  tab[row].departement, tab[row].time, tab[row].family);
        }
      }
      if (remove("clients.csv") == 0) {//Supprime le 1er fichier clients.csv et vérifie qu'il a bien été supprimé
        printf(" Le client a été supprimé avec succès.\n");
      } else {
        printf("Impossible de supprimer le client\n");
      }
      rename("cswitch.csv", "clients.csv");//Change le nom de cswitch.csv en clients.csv pour qu'il prenne la place de celui supprimer
      fclose(fpswitch);
    }
  }
  fclose(fp);
}

int main() {//Sert de menu principal
  int c = 0, l = 0;
  char choice[20];
  FILE *fp = fopen("clients.csv","r");
  if (!fp)
    ecriture();
  else {
    printf("--------------------------------------\n");
    printf("\n        Bienvenue dans le menu\n");
    printf("\n--------------------------------------");
    while (choice[0] != '0') {
      printf("\n\nQue souhaitez-vous faire?");
      printf("\n0.Quitter le menu\n1.Consulter les informations des "
             "clients\n2.Ajouter un client\n3.Supprimer un "
             "client\n4.Rechercher un client suivant son nom\n :");
      scanf("%s", choice);
      while (choice[0] < '0' || strlen(choice) != 1 ||
             choice[0] > '4' || strlen(choice) != 1) {//Vérifie que le choix demandé est valable
        printf(
            "\nIl y a une erreur ! Veuillez bien saisir un nombre correct :");
        scanf("\n%s", choice);
      }

      switch (choice[0]) {// [0] pour ne prendre en compte que le premier caractère écrit pour éviter les fautes de frappes
      case '0':
        printf("A bientot ! ");// Condition de départ si l'utilisateur souhaite quitter le menu
        break;
      case '1':
        lecture_fichier(); //Appel de la fonction pour lire les informations du fichier clients.csv
        break;
      case '2':
        ecriture();// Appel de la fonction pour écrire dans le fichier de nouvelles donées
        break;
      case '3':
        retireClient();// Appel de la fonction pour supprimer un client
        break;
      case '4':
        searchClient(&c, &l,0);// Appel de la fonction pour rechercher un client
        break;
      }
    }
  }
  fclose(fp);
  return 0;
}
*/