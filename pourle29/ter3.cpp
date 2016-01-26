#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>//pour le graphe

#include "node.h"
#include "afficheps.h"


using namespace std;

/***************
Objectifs : arbre dynamique donc tab dynamique -> actuellement arbre de taille k avec a rempli
structure de données pour chaque feuille de l'arbre
******************/
void reecriture(char* filename, char** tab, int k, node* racine);
node* parcours(node* racine, node* n, int a, int niveauDemande, int niveauActuel);
char* lireLigne(FILE *f);
void lectureRegles(char *filename);


int main(int argc, char** argv)
{
  cout <<  "Bonjour camarades !" << endl;
  char* tab[100];
  char str[80];
  char* filename = new char[11 * sizeof(char)];
  sprintf(filename, "myfile.txt");

  FILE* pFile;
  if(argc == 2)
  {
    delete filename;
    filename = new char[(strlen(argv[1]) + 1) * sizeof(char)];
    filename = argv[1];
  }
  pFile = fopen(filename, "r");

  if(pFile == NULL)
  {
    perror("Impossible d'ouvrir le fichier ");
    return -1;
  }
  else
  {
    fgets(str, 2, pFile) != NULL;
  }

  fclose(pFile);

  lectureRegles(filename);
  tab[0] = new char[(strlen(str) + 1) * sizeof(char)];
  strcpy(tab[0], str);

  node* racine = new node(612/2, 792/5, (long)90, tab[0], NULL);

  char saisie[100];
  int rang = 1;


  cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
  cin >> saisie;

  while(strcmp(saisie, "quit") != 0)
  {
//    reecriture(filename, tab, rang, racine);
    rang++;
    cout << endl << "Resultat : " << endl << endl;
    for(int i = 0; i < rang; i++)
    {
//      cout << "rang " << i << " : " << tab[i] << endl;
    }
    affichageGraphique(racine);

    cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
    cin >> saisie;
  }
/*  for(int i = 0; i < rang; i++)
  {
    delete tab[i];
  }
*/  delete filename;
  return 0;
}

char* lireLigne(FILE *f) {
  char c = fgetc(f);
  char *line = NULL;
  line = (char*) malloc(512 * sizeof(char));
  if (line == NULL)
    perror("memory");
  int k = 0;
  while (c != '.' && c != '\n' && c != '\0' && c != EOF) {
    line[k] = c;
    ++k;
    c = fgetc(f);
  }
  if (k == 0) {
    return NULL;
  }
  line[k] = '\0';
  return line;
}

void lectureRegles(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("File not found");
  }
  char *line = NULL;
  vector<char> mots; // <3
  vector<char*> regles;
  while ((line = lireLigne(file)) != NULL) {
    cout << line << endl;
    /*for (int k = 0; line[k] != '\0'; ++k) {
      if (line[k] == '>') {
        //char *l = new char[64]; // peut etre un peu con a voir apres
        //strncpy(l, line, k - 1); // a verifier le -1
        mots.push_back(line[0]);
      } else if (line[k] == '.') {
        char *l = new char[64];
        strncpy(l, line + 2, k - 2); // peut etre -3
        regles.push_back(l);
      }
    }*/
  }
  for (int k = 0; k < regles.size(); ++k) {
    cout << mots.at(k) << "  ->  " << regles.at(k) << endl;

  }
  fclose(file);
}




void reecriture(char* filename, char** tab, int k, node* racine)
{
  char buff[1024];
  cout << "boucle " << k << endl;
  FILE* pFile;
  int c, a, i = 0;
  string str = tab[k - 1]; //etages enregistres 0 a, 1 ab, 2 aba ... k-1 = étage parent à celui demandé
  char bufferTest[1024];
  strcpy(bufferTest, "");

  long dist = 40;
  long angle = 20;

  int *mots;
  string **regles;

  while(str[i] != '\0')
  {
    a = str[i];
    i++;
    pFile = fopen(filename, "r");
    if(pFile == NULL)
    {
      perror("Impossible d'ouvrir le fichier !");
    }
    else
    {
      node* noeud_a_memoriser = racine;
      int niveau = 0, fils = 0;
      do
      {
        c = fgetc(pFile);
        if(c == a) // recherche de la regle pour a
        {
          c = fgetc(pFile);
          if(c == '>')
          {
            c = fgetc(pFile); //ajout des elements a a
            noeud_a_memoriser = parcours(racine, racine, a, k, niveau);
            while(c != '.')
            {
//              noeud_a_memoriser->ajoutEnfant(new node((long)10, (long)20, true, tmp, noeud_a_memoriser));
              int f = sprintf(buff, "%c",(char)c);
              strcat(bufferTest, buff);
              //cout <<  "buff = " << buff << " et buffTest = " << bufferTest << endl;
              c = fgetc(pFile);
            }
            noeud_a_memoriser->setDV(true);
          }
        }
        noeud_a_memoriser = racine;
        racine->resetDV();
      }while(c != EOF);
      fclose(pFile);
    }
  }
  tab[k] = new char[strlen(bufferTest) + 1];
  strcpy(tab[k], bufferTest);
  cout << "rang " << k << " = " << tab[k] << endl;
  strcpy(bufferTest, "");
}

node* parcours(node* racine, node* n, int a, int niveauDemande, int niveauActuel)
{
  n->setDV(true);
  for(int i = 0; i < n->getEnfants()->size(); ++i)
  {
    if(!n->getEnfant(i)->getDV())
    {
      if(niveauDemande == niveauActuel && n->getName()[0] == (char)a)
      {
        n->setDV(false);
        return n;
      }
      else
      {
        if (niveauActuel < niveauDemande)
        {
          return parcours(racine, n->getEnfant(i), a, niveauDemande, niveauActuel + 1);
        }
      }
    }
  }
}
