#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 1000
// MAX_BUFFER_SIZE définit la taille maximale allouable
typedef struct Personnes {
  char forename[25], name[25];
  int age, country, departement, time, family;
} personnes;

typedef struct ListePersonnes{
  struct Personnes tab[30];
  int RowMax;
} listepersonnes;

void ecriture() { // La fonction permet d'écrire dans le fichier clients.csv
  FILE *fp =
      fopen("clients.csv", "a"); // ouverture / création du fichier clients.csv

  char forename[25] = "", name[25] = "", age[3] = "", country[50] = "",
       departement[6] = "", time[3] = "", family[15] = "", cond = 'F',
       alphabet[] =
           "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZîïéèêëô ",
       number[] =
           "0123456789"; // number et alphabet permettent plus bas de déterminer
                         // si on entre les bonnes valeurs dans les scanf des
                         // informations clients pour eviter des prenoms comme
                         // 0215654sqcf qui n'auraient pas de sens

  int i;
  printf("\n--------------------------------------\n");
  printf("\n     Programme d'ajout de client \n");
  printf("\n--------------------------------------\n\n");
  printf(
      "\nVeuillez saisir le prenom du client ou q si vous voulez quitter : ");
  scanf(
      "\n%[^\n]s",
      forename); //[^\n] permet de prendre en compte les espaces dans les chaîne
                 // de caractère pour les noms ou prénoms composés par exemple
  if (strcmp(forename, "q") == 0 ||
      strcmp(forename, "Q") ==
          0) { // Condition de sortie de fonction si q ou Q est écrit
    return;
  } else {
    i = strspn(
        forename,
        alphabet); // Renvoie la longueur de la plus grande sous-chaîne (en
                   // partant du début de la chaîne initiale) ne contenant que
                   // des caractères spécifiés dans la liste des caractères
                   // acceptés.Permet de définir si tout le mot est contenu dans
                   // l'aphabet pour éviter des chiffres
    while (
        i !=
        strlen(
            forename)) { // Condition jusqu'à ce que le prénom soit bien écrit
      printf("Erreur ! Veuillez n'ecrire que des lettres(Retournez au menu "
             "avec q) :");
      scanf("\n%[^\n]s", forename);
      i = strspn(forename, alphabet);
      if (strcmp(forename, "q") == 0 || strcmp(forename, "Q") == 0) {
        return;
      }
    }
    printf("\nVeuillez saisir le nom du client : ");
    scanf("\n%[^\n]s", name);
    i = strspn(name, alphabet);
    while (i != strlen(name)) {
      printf("Erreur ! Veuillez n'ecrire que des lettres :");
      scanf("\n%[^\n]s", name);
      i = strspn(name, alphabet);
    }
    printf("\nVeuillez saisir l'age du client : ");
    scanf("\n%[^\n]s", age);
    i = strspn(age, number); // Permet de définir si tout le mot ne contient
                             // bien que des chiffres pour éviter des lettres
    while (i != strlen(age)) {
      printf("Erreur ! Veuillez n'ecrire que des chiffres :");
      scanf("\n%[^\n]s", age);
      i = strspn(age, number);
    }
    printf("\nVeuillez saisir le pays du client : ");
    scanf("\n%[^\n]s", country);
    i = strspn(country, alphabet);
    while (i != strlen(country)) {
      printf("Erreur ! Veuillez n'ecrire que des lettres :");
      scanf("\n%[^\n]s", country);
      i = strspn(country, alphabet);
    }
    printf("\nVeuillez saisir le numero de departement du client : ");
    scanf("\n%[^\n]s", departement);
    i = strspn(departement, number);
    while (i != strlen(departement)) {
      printf("Erreur ! Veuillez n'ecrire que des chiffres :");
      scanf("\n%[^\n]s", departement);
      i = strspn(departement, number);
    }
    printf("\nVeuillez saisir le temps de sejour du client (en jour) : ");
    scanf("\n%[^\n]s", time);
    i = strspn(time, number);
    while (i != strlen(time)) {
      printf("Erreur ! Veuillez n'ecrire que des chiffres :");
      scanf("\n%[^\n]s", time);
      i = strspn(time, number);
    }
    printf("\nVeuillez saisir le nombre de membres avec le client : ");
    scanf("\n%[^\n]s", family);
    i = strspn(family, number);
    while (i != strlen(family)) {
      printf("Erreur ! Veuillez n'ecrire que des chiffres :");
      scanf("\n%[^\n]s", family);
      i = strspn(family, number);
    }
    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", forename, name, age, country,
            departement, time,
            family); //Écriture des informations dans le fichier
    fclose(fp);      // Fin de l'écriture
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
    printf("\n   Programme de lecture de client \n");
    printf("\n--------------------------------------\n\n");

    while (fgets(buffer, MAX_BUFFER_SIZE, fp)) {
      column = 0;
      char *value = strtok(
          buffer, ", "); // value prend la valeur de l'élement et s'arrête a la
                         // prochaine virgule (la virgule permet de prendre en
                         // compte des chaînes composées de plusieurs mots)
      row++;
      while (value) {
        switch (
            column) { // parcourt du fichier selon les colonnes grâce au tableau
                      // qui permet d'avoir nos informations indexées
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

        printf("%s", value); // printf en dehors du switch pour éviter une
                             // répétition inutile qui prendrai plus de lignes

        value = strtok(NULL, ", ");
        column++;
      }
    }
    fclose(fp);
  }
}

void createTab(struct ListePersonnes *T) { // La procédure permet de créer un tableau
                              // d'élément de type structures Personnes
  int row = 0, column = 0;
  FILE *fp = fopen("clients.csv", "r");
  if (!fp) // Vérifie si le fichier s'est bien ouvert
    printf("Can't open file\n");
  else {
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(
        buffer, MAX_BUFFER_SIZE,
        fp)) { // Une boucle qui va permettre d'initialiser le tableau de
               // structures Personnes avec les valeurs du fichier clients.csv
      row++;
      column = 0;
      char *value = strtok(
          buffer, ", "); // value prend la valeur de l'élement et s'arrête a la
                         // prochaine virgule (la virgule permet de prendre en
                         // compte des chaînes composées de plusieurs mots)
      while (value) {     // tant que la valeur n'est pas nulle (donc qu'il y a
                          // encore des données a parcourir)
        switch (column) { // insertion des informations du fichier selon les
                          // colonnes dans le tableau
        case 0:
          strcpy(T->tab[row].forename, value);
          break;
        case 1:
          strcpy(T->tab[row].name, value);
          break;
        case 2:
          T->tab[row].age = strtol(value, (char **)NULL, 10);
          break;
        case 3:
          T->tab[row].country = strtol(value, (char **)NULL, 10);
          break;
        case 4:
          T->tab[row].departement = strtol(value, (char **)NULL, 10);
          break;
        case 5:
          T->tab[row].time = strtol(value, (char **)NULL, 10);
          break;
        case 6:
          T->tab[row].family = strtol(value, (char **)NULL, 10);
          break;
        }
        value = strtok(NULL, ",");
        column++;
      }
    }
    fclose(fp);
  }
  T->RowMax = row; // On passe par adresse rowMax qui permet d'avoir le nombre de
                 // ligne max
}

void searchClient(struct ListePersonnes *T,int *compt, int *ligne,int verif) { 
                               // La fonction permet de rechercher un client par
                               // son nom ou prenom en passant par un traitement
                               // de données par tableau de type Personnes
  
  FILE *fp;
  fp = fopen("clients.csv", "r");
  char searchFN[25],searchN[25];
  int row = 1, cond = 0;
  *compt = 0;
  if (verif == 0) {
    printf("\n--------------------------------------\n");
    printf("\n Programme de recherche de client \n");
    printf("\n--------------------------------------\n");
  }
  printf("\n-N si vous cherchez le nom d'un client\n-P si vous cherchez le "
         "prenom\n-NP si vous voulez chercher par nom et prénom\n-Q si vous "
         "voulez quitter :");
  scanf("%s", searchFN); // Le %[^\n]s permet de chercher des chaînes de
                         // caractères avec des espaces
  while ((strcmp(searchFN, "q") != 0 && strcmp(searchFN, "Q") != 0) &&
         (strcmp(searchFN, "p") != 0 && strcmp(searchFN, "P") != 0) &&
         (strcmp(searchFN, "n") != 0 && strcmp(searchFN, "N") != 0) &&
         (strcmp(searchFN, "np") != 0 && strcmp(searchFN, "NP") != 0)) {
    printf("\nIl y a erreur! Veillez a bien ecrire ce qu'il est demande : ");
    scanf("%s", searchFN); // Le %[^\n]s permet de chercher des chaînes de
                           // caractères avec des espaces
  }
  if (strcmp(searchFN, "q") == 0 ||
      strcmp(searchFN, "Q") == 0) { // Condition permettant de quitter la
                                    // fonctions si on entre la lettre q ou Q
    return;
  }
  if (!fp)
    ecriture();
  else {
    createTab(T); // appel de la fonction pour créer un tableau de
                             // type Personnes pour séquenter nos données
    if (strcmp(searchFN, "n") == 0 || strcmp(searchFN, "N") == 0) {
      printf("\nVeuillez saisir le nom que vous souhaitez :");
      scanf("\n%[^\n]s", searchN);
      while (row <= T->RowMax) { // Boucle pour parcourir tout le tableau
        if (strcmp(searchN, T->tab[row].name) ==
            0) { // Compare chaque nom du tableau avec le mot
                 // rechercher(seachFN)
                 // Affichage de ou des personnes trouvés
          printf("\nLigne %d : \n", row);
          printf("%s", T->tab[row].forename);
          printf(" %s", T->tab[row].name);
          printf(" %d", T->tab[row].age);
          printf(" %d", T->tab[row].country);
          printf(" %d", T->tab[row].departement);
          printf(" %d", T->tab[row].time);
          printf(" %d", T->tab[row].family);
          *ligne =row; // On passe par adresse la variable ligne qu'on
                       // initialise avec la variable row pour pouvoir récupérer
                       // hors de la procédure la ligne d'une nom recherché
          row++;
          cond = 1;
          *compt = *compt + 1;
        } else {
          row++;
        }
      }
    }
      if (strcmp(searchFN, "p") == 0 || strcmp(searchFN, "P") == 0) {
        printf("\nVeuillez saisir le prenom que vous souhaitez :");
        scanf("\n%[^\n]s", searchFN);
        while (row <= T->RowMax) { // Boucle pour parcourir tout le tableau
          if (strcmp(searchFN, T->tab[row].forename) ==
              0) { // Compare chaque nom du tableau avec le mot
                   // rechercher(seachFN)
            // Affichage de ou des personnes trouvés
            printf("\nLigne %d : \n", row);
            printf("%s", T->tab[row].forename);
            printf(" %s", T->tab[row].name);
            printf(" %d", T->tab[row].age);
            printf(" %d", T->tab[row].country);
            printf(" %d", T->tab[row].departement);
            printf(" %d", T->tab[row].time);
            printf(" %d", T->tab[row].family);
            *ligne =
                row; // On passe par adresse la variable ligne qu'on initialise
                     // avec la variable row pour pouvoir récupérer hors de la
                     // procédure la ligne d'une nom recherché
            row++;
            cond = 1;
            *compt = *compt + 1;
          } else {
            row++;
          }
        }
      }
    else{
      if (strcmp(searchFN, "np") == 0 || strcmp(searchFN, "NP") == 0){
        printf("\nVeuillez saisir le prenom et nom que vous souhaitez :");
        scanf("\n%[^\n]s", searchFN);
        scanf("\n%[^\n]s",searchN);
        while (row <= T->RowMax) { // Boucle pour parcourir tout le tableau
          if (strcmp(searchFN, T->tab[row].forename) ==
              0 && strcmp(searchN, T->tab[row].name) ==
              0){ // Compare chaque nom du tableau avec le mot
                   // rechercher(seachFN)
            // Affichage de ou des personnes trouvés
            printf("Ligne %d : \n", row);
            printf("%s", T->tab[row].forename);
            printf(" %s", T->tab[row].name);
            printf(" %d", T->tab[row].age);
            printf(" %d", T->tab[row].country);
            printf(" %d", T->tab[row].departement);
            printf(" %d", T->tab[row].time);
            printf(" %d\n", T->tab[row].family);
            *ligne =
                row; // On passe par adresse la variable ligne qu'on initialise
                     // avec la variable row pour pouvoir récupérer hors de la
                     // procédure la ligne d'une nom recherché
            row++;
            cond = 1;
            *compt = *compt + 1;
          } else {
            row++;
          }
        }
      if (cond == 0) {
        printf("\nIl n'y a personne possedant ce nom.\n");
      }
      }
    }
  }
  fclose(fp);
}

void retireClient(struct ListePersonnes T) { // La fonction permet de supprimer un client du fichier
                      // clients.csv
  FILE *fp;
  FILE *fpswitch;
  fp = fopen("clients.csv", "r");
  char searchFN[25];
  int row = 1, compt = 0, ligne = 0, choix = 1;
  if (!fp)
    ecriture(); // Appel de la fonction ecriture
  else {
    printf("\n--------------------------------------\n");
    printf("\n Programme de suppression de client \n");
    printf("\n--------------------------------------\n\n");
    searchClient(&T,&compt,&ligne,1); // Appel de la fonction de recherche dans client
    if (ligne != 0) {
      fpswitch =
          fopen("cswitch.csv",
                "w"); // Créer et ouvre le fichier cswitch.csv qui va servir de
                      // nouveau clients.csv après la fin de la fonction
      createTab(&T);
      if (compt > 1) { // Condition permettant de choisir le client que l'on
                       // veut supprimer si il y plusieurs
        printf("\nDonnez la ligne du client que vous souhaitez supprimer ou "
               "ecrivez 0 pour quitter: ");
        scanf("%d", &ligne);
      }
      for (row = 1; row <= T.RowMax;
           row++) { // Parcours la table de Personnes en entier et écrit dans le
                    // fichier cswitch.csv tous les clients à part celui que
                    // l'on veut supprimer
        if (row != ligne) {
          fprintf(fpswitch, "%s,%s,%d,%d,%d,%d,%d\n", T.tab[row].forename,
                  T.tab[row].name, T.tab[row].age, T.tab[row].country,
                  T.tab[row].departement, T.tab[row].time, T.tab[row].family);
        }
      }
      if (remove("clients.csv") == 0 &&
          ligne != 0) { // Supprime le 1er fichier clients.csv et vérifie qu'il
                        // a bien été supprimé
        printf(" \nLe client a été supprimé avec succès.\n");
      } else if (ligne != 0) {
        printf("Impossible de supprimer le client\n");
      }
      rename("cswitch.csv",
             "clients.csv"); // Change le nom de cswitch.csv en clients.csv pour
                             // qu'il prenne la place de celui supprimer
      fclose(fpswitch);
    }
  }
  fclose(fp);
}

int main() {
  int i;
  struct ListePersonnes T;
  // Sert de menu principal
  int c = 0, l = 0, result = 0;
  char choice[20];
  FILE *fp = fopen("clients.csv", "r");
  if (!fp)
    ecriture();
  else {
    while (choice[0] != '0') {
      printf("\n--------------------------------------\n");
      printf("\n        Bienvenue dans le menu\n");
      printf("\n--------------------------------------");

      printf("\n\nQue souhaitez-vous faire?");
      printf("\n0.Quitter le menu\n1.Consulter les informations des "
             "clients\n2.Ajouter un client\n3.Supprimer un "
             "client\n4.Rechercher un client suivant son nom ou "
             "prenom\n5.Moyenne des ages des clients\n :");
      scanf("\n%[^\n]s", choice);
      while (choice[0] < '0' || strlen(choice) != 1 || choice[0] > '5' ||
             strlen(choice) != 1) { // Vérifie que le choix demandé est valable
        printf(
            "\nIl y a une erreur ! Veuillez bien saisir un nombre correct :");
        scanf("\n%s", choice);
      }

      switch (choice[0]) { // [0] pour ne prendre en compte que le premier
                           // caractère écrit pour éviter les fautes de frappes
      case '0':
        printf("A bientot ! "); // Condition de départ si l'utilisateur souhaite
                                // quitter le menu
        break;
      case '1':
        lecture_fichier(); // Appel de la fonction pour lire les informations du
                           // fichier clients.csv
        break;
      case '2':
        ecriture(); // Appel de la fonction pour écrire dans le fichier de
                    // nouvelles donées
        break;
      case '3':
        retireClient(T); // Appel de la fonction pour supprimer un client
        break;
      case '4':
        searchClient(&T,&c, &l,0);
        // Appel de la fonction pour rechercher un client
        break;
      case '5':
        createTab(&T);
        result = 0;
        for (i = 1; i <= T.RowMax; i++) {
          result += T.tab[i].age;
        }
        result = result / T.RowMax;
        printf("\nLa moyenne des ages des clients est de : %d\n", result);
      }
    }
  }
  fclose(fp);
  return 0;
}
