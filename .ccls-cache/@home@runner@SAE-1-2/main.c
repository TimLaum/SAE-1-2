#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 1000
// MAX_BUFFER_SIZE définit la taille maximale allouable
typedef struct Personnes {
  char forename[25], name[25], country[25];
  int age, departement, time, family;
} personnes;

typedef struct ListePersonnes {
  struct Personnes tab[30];
  int RowMax;
} listepersonnes;

void ecriture(struct ListePersonnes *T) { // La fonction permet d'écrire dans le
                                          // tableau de structure
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
    //Initialise une nouvelle structure dans le tableau de structure dans la structure ListePersonnes
    strcpy(T->tab[T->RowMax].forename,forename);
    strcpy(T->tab[T->RowMax].name,name);
    T->tab[T->RowMax].age=strtol(age, (char **)NULL, 10);
    strcpy(T->tab[T->RowMax].country,country);
    T->tab[T->RowMax].departement=strtol(departement, (char **)NULL, 10);
    T->tab[T->RowMax].time=strtol(time, (char **)NULL, 10);
    T->tab[T->RowMax].family=strtol(family, (char **)NULL, 10);
    T->RowMax=T->RowMax+1;
  }
}

void lecture_client(struct ListePersonnes *T) {//Affiche les clients contenu dans la structure
  if (T->RowMax==0)
    ecriture(T);
  else {
    int row;
    int column = 0;
    printf("\n--------------------------------------\n");
    printf("\n   Programme de lecture de client \n");
    printf("\n--------------------------------------\n\n");
    for(row=0;row<T->RowMax;row++){
      printf("\n%d)",row);
      printf("Prenom :%s/",T->tab[row].forename);
      printf("Nom :%s/",T->tab[row].name);
      printf("Age :%d/",T->tab[row].age);
      printf("Pays :%s/",T->tab[row].country);
      printf("Departement :%d/",T->tab[row].departement);
      printf("Temps de sejour :%d/",T->tab[row].time);
      printf("Nombre de membres :%d",T->tab[row].family);
    }
  }
}

void createTab(struct ListePersonnes *T){ // La procédure permet de créer un tableau
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
          strcpy(T->tab[row].country, value);
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
      row++;
    }
    fclose(fp);
  }
  T->RowMax = row; // On passe par adresse rowMax qui permet d'avoir le nombre
                   // de ligne max
}

void searchClient(struct ListePersonnes *T, int *compt, int *ligne, int verif) {
  // La fonction permet de rechercher un client par
  // son nom ou prenom en passant par un traitement
  // de données par tableau de type Personnes
  char searchFN[25], searchN[25];
  int row = 0, cond = 0;
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
  if (T->RowMax==0){
    ecriture(T);
  }
  else {
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
          printf(" %s", T->tab[row].country);
          printf(" %d", T->tab[row].departement);
          printf(" %d", T->tab[row].time);
          printf(" %d", T->tab[row].family);
          *ligne =
              row; // On passe par adresse la variable ligne qu'on
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
          printf(" %s", T->tab[row].country);
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
    else {
      if (strcmp(searchFN, "np") == 0 || strcmp(searchFN, "NP") == 0) {
        printf("\nVeuillez saisir le prenom et nom que vous souhaitez :");
        scanf("\n%[^\n]s", searchFN);
        scanf("\n%[^\n]s", searchN);
        while (row <= T->RowMax) { // Boucle pour parcourir tout le tableau
          if (strcmp(searchFN, T->tab[row].forename) == 0 &&
              strcmp(searchN, T->tab[row].name) ==
                  0) { // Compare chaque nom du tableau avec le mot
                       // rechercher(seachFN)
            // Affichage de ou des personnes trouvés
            printf("Ligne %d : \n", row);
            printf("%s", T->tab[row].forename);
            printf(" %s", T->tab[row].name);
            printf(" %d", T->tab[row].age);
            printf(" %s", T->tab[row].country);
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
}
void changement_suppression_Client(struct ListePersonnes *T,int indice1,int indice2){//Permet à ce que la structure d'indice2 dans le tableau dans ListePersonnes soit copié dans la structure d'indice1
  strcpy(T->tab[indice1].forename,T->tab[indice2].forename);
  strcpy(T->tab[indice1].name,T->tab[indice2].name);
  T->tab[indice1].age=T->tab[indice2].age;
  strcpy(T->tab[indice1].country,T->tab[indice2].country);
  T->tab[indice1].departement=T->tab[indice2].departement;
  T->tab[indice1].time=T->tab[indice2].time;
  T->tab[indice1].family=T->tab[indice2].family;
}
void retireClient(struct ListePersonnes *T) { // La fonction permet de supprimer
                                             // un client du tableau de structures
  char searchFN[25];
  int row = 1, compt = 0, ligne = 0, choix = 1;
  if (T->RowMax==0){
    ecriture(T); // Appel de la fonction ecriture
  }
  else {
    printf("\n--------------------------------------\n");
    printf("\n Programme de suppression de client \n");
    printf("\n--------------------------------------\n\n");
    searchClient(T, &compt, &ligne,
                 1); // Appel de la fonction de recherche dans client
    if (ligne != 0) {
      if (compt > 1) { // Condition permettant de choisir le client que l'on
                       // veut supprimer si il y plusieurs
        printf("\nDonnez la ligne du client que vous souhaitez supprimer ou "
               "ecrivez 0 pour quitter: ");
        scanf("%d", &ligne);
      }
      for(row=ligne;row<T->RowMax-2;row++){
        changement_suppression_Client(T,row,row+1);
      }
      T->RowMax=T->RowMax-1;
      printf("\nLe client a bien ete supprime !");
    }
  }
}

void merge(struct ListePersonnes *T, int low, int mid, int high, char* key) {
  int i, j, k;
  struct ListePersonnes L, R; // Définition de deux noms de structures qui serviront a comparer et echanger les valeurs dans la structure T au final. L correspond a la partie gauche de T et R a la partie droite. 
  int n1 = mid - low + 1; //valeur qui délimite la partie gauche
  int n2 = high - mid; //valeur qui délimite la partie droite
  for (i = 0; i < n1; i++) {// Attribution des données de la partie gauche de T
    L.tab[i] = T->tab[low + i];
  }
  for (j = 0; j < n2; j++) {// Attribution des données de la partie gauche de T
    R.tab[j] = T->tab[mid + 1 + j];
  }
  i = 0;
  j = 0;
  k = low;
  while (i < n1 && j < n2) { // Condition qui permet de diviser jusqu'a ce que chaque élément soit 2 par deux maximum
    if (strcmp(key, "name") == 0) { //Tri par nom
      if (strcmp(L.tab[i].name, R.tab[j].name) <= 0) {
        T->tab[k] = L.tab[i];
        i++;
      } else {
        T->tab[k] = R.tab[j];
        j++;
      }
    } else if (strcmp(key, "country") == 0) { //Tri par pays
      if (strcmp(L.tab[i].country, R.tab[j].country) <= 0) {
        T->tab[k] = L.tab[i];
        i++;
      } else {
        T->tab[k] = R.tab[j];
        j++;
      }
    }
    k++;
  }
  while (i < n1) {
    T->tab[k] = L.tab[i];
    i++;
    k++;
  }
  while (j < n2) {
    T->tab[k] = R.tab[j];
    j++;
    k++;
  }
}

void mergeSort(struct ListePersonnes *T, int low, int high, char* key) {
  if (low < high) { //Condition d'arrêt de la fonction récursive
    int mid = low + (high - low) / 2;
    mergeSort(T, low, mid, key);//Appel récursif sur la partie gauche du tableau
    mergeSort(T, mid + 1, high, key);//Appel récursif sur la partie droite du tableau
    merge(T, low, mid, high, key);//Appel de la fonction qui remplit T avec les données une fois triées à chaque étape du tri
  }
}


void transfere_en_CSV(struct ListePersonnes *T){
  FILE *fp;
  FILE *fpswitch;
  fp = fopen("clients.csv", "r");
  int row = 1, compt = 0, ligne = 0, choix = 1;
  fpswitch =fopen("cswitch.csv","w"); // Créer et ouvre le fichier cswitch.csv qui va servir de
                      // nouveau clients.csv après la fin de la fonction
  for (row = 0; row < T->RowMax;row++) { // Parcours la table de Personnes en entier et écrit dans le
                                        // fichier cswitch.csv tous les clients
    fprintf(fpswitch, "%s,%s,%d,%s,%d,%d,%d\n", T->tab[row].forename,
    T->tab[row].name, T->tab[row].age, T->tab[row].country,
    T->tab[row].departement, T->tab[row].time, T->tab[row].family);
  } 
  remove("clients.csv"); // Supprime le 1er fichier clients.csv
  rename("cswitch.csv","clients.csv"); // Change le nom de cswitch.csv en clients.csv pour
                                       // qu'il prenne la place de celui supprimé
  fclose(fpswitch);
  fclose(fp);
}

int main() {
  int i;
  struct ListePersonnes T;
  char key[10];
  // Sert de menu principal
  int c = 0, l = 0, result = 0, repTri = 0,appel=0;
  char choice[20];
  createTab(&T);
  FILE *fp = fopen("clients.csv", "r");
  if (!fp){
    ecriture(&T);
  }
    while (choice[0] != '0') {
      printf("\n--------------------------------------\n");
      printf("\n        Bienvenue dans le menu\n");
      printf("\n--------------------------------------");

      printf("\n\nQue souhaitez-vous faire?");
      printf("\n0.Quitter le menu\n1.Consulter les informations des "
             "clients\n2.Ajouter un client\n3.Supprimer un "
             "client\n4.Rechercher un client suivant son nom ou "
             "prenom\n5.Moyenne des ages des clients\n6.Trier les clients\n :");
      scanf("\n%[^\n]s", choice);
      while (choice[0] < '0' || strlen(choice) != 1 || choice[0] > '6' ||
             strlen(choice) != 1) { // Vérifie que le choix demandé est valable
        printf(
            "\nIl y a une erreur ! Veuillez bien saisir un nombre correct :");
        scanf("\n%s", choice);
      }

      switch (choice[0]) { // [0] pour ne prendre en compte que le premier
                           // caractère écrit pour éviter les fautes de frappes
      case '0':
        transfere_en_CSV(&T);
        printf("\nA bientot ! ");
        break;
      case '1':
        lecture_client(&T); // Appel de la fonction pour lire les informations du
                           // fichier clients.csv
        break;

      case '2':
        ecriture(&T); // Appel de la fonction pour écrire dans le fichier de
                      // nouvelles données
        break;

      case '3':
        retireClient(&T); // Appel de la fonction pour supprimer un client
        break;

      case '4':
        searchClient(&T, &c, &l, 0);
        // Appel de la fonction pour rechercher un client
        break;

      case '5': //Moyenne des âges des clients du csv (facultatif)
        createTab(&T);
        result = 0;
        if (T.RowMax == 0) {
          printf("\nImpossible car le fichier est vide");
        }
        else {
          for (i = 1; i <= T.RowMax; i++) {
            result += T.tab[i].age;
          }
          result = result / T.RowMax;
          printf("\nLa moyenne des ages des clients est de : %d\n", result);
        }
        break;
      case '6': // Appel de la fonction de tri et d'affichage de cette liste triée
        printf("\n--------------------------------------\n");
        printf("\n Programme de tri des clients \n");
        printf("\n--------------------------------------\n\n");
        do{
          printf("\nVoulez-vous trier par nom ou pays ? (name / country) ");
          scanf("\n%s",key);
          if(strcmp(key,"name")!=0 && strcmp(key,"country")!=0){
            printf("\nVeuillez saisir ce qui est demandé !\n");
          }
        }while(strcmp(key,"name")!=0 && strcmp(key,"country")!=0);
        mergeSort(&T,0,T.RowMax-1,key);
        lecture_client(&T);
        printf("\n\nTri termine !\n");
      }
    }
  fclose(fp);
  return 0;
}