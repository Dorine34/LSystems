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

/*
void reecriture(char**tab, int k);
*/

void lectureRegles(char *filename);
void createTreeUntilRank(vector<char> mots, vector<string> regles, node *noeud, int hauteur);
void createTreeRankByRank(vector<char> mots, vector<string> regles);
vector<node*> etage;
vector<char> mots; // a corriger
vector<string> regles; // a corriger

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

  char motRacine = mots.at(0);
  mots.erase(mots.begin());
  char *tmpTab = new char[2];
  tmpTab[0] = motRacine;
  tmpTab[1] = '\0';

  node* racine = new node(NULL, 612/2, 792/5, 90, tmpTab);
  etage.push_back(racine);
  //createTreeUntilRank(mots, regles, racine, 4);

  tab[0] = new char[(strlen(str) + 1) * sizeof(char)];
  strcpy(tab[0], str);

  char saisie[100];
  int rang = 1;

  cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
  cin >> saisie;

  while(strcmp(saisie, "quit") != 0)
  {
    rang++;
    createTreeRankByRank(mots, regles);
    cout << etage.size() << endl;
    cout << endl << "Resultat : " << endl << endl;

    affichageGraphique(racine);

    cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
    cin >> saisie;
  }
  delete filename;
  return 0;
}

void lectureRegles(char *filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    perror("File not found");
  }
  string line;
  bool b = false;
  while (getline(file, line)) {
    cout << line << endl;
    b = false;
    for (unsigned int k = 0; k < line.size(); ++k) {
      if (line[k] == '>') {
        mots.push_back(line[0]);
        b = true;
      } else if (line[k] == '.') {
    	if (b) {
			int beg = line.find('>') + 1;
			regles.push_back(line.substr(beg, k - beg));
    	} else {
    		mots.push_back(line[0]);
    	}
      }
    }
  }
  file.close();
  for (unsigned int k = 0; k < mots.size(); ++k) {
	cout << mots.at(k) << endl;
  }
}

void createTreeUntilRank(vector<char> mots, vector<string> regles, node *racine, int hauteur) {
	vector<node*> etage;
	vector<node*> etageSuivant;
	etage.push_back(racine);
	for (int i = 0; i < hauteur; ++i) {
		for (int j = 0; j < etage.size(); ++j) {
			int index = 0;
			for (int k = 0; k < mots.size(); ++k) {
				if (mots.at(k) == etage.at(j)->getName()[0]) {
					index = k;
					break;
				}
			}
      for (int k = 0; k < regles.at(index).size(); ++k) {
				char *tmpTab = new char[2];
				tmpTab[0] = regles.at(index).at(i);
				tmpTab[1] = '\0';
				node *enfant = new node(40, regles.at(index).at(i)=='a'? 40 : 60, !(regles.at(index).at(i) == 'a'), tmpTab, etage.at(j));
				etageSuivant.push_back(enfant);
				cout << regles.at(index).at(i) << "-";
			}
			cout << "   ";
		}
		etage.clear();
    for (int j = 0; j < etageSuivant.size(); ++j) {
      etage.push_back(etageSuivant.at(j));
    }
		etageSuivant.clear();
	}
}

void createTreeRankByRank(vector<char> mots, vector<string> regles) {
	vector<node*> etageSuivant;
  for (int i = 0; i < etage.size(); ++i) {
		int index = 0;
		for (unsigned int j = 0; j < mots.size(); ++j) {
			if (mots.at(j) == etage.at(i)->getName()[0]) {
				index = j;
				break;
			}
		}
		for (int j = 0; j < regles.at(index).size(); ++j) {
			char *tmpTab = new char[2];
			tmpTab[0] = regles.at(index).at(j);
			tmpTab[1] = '\0';
			node *enfant = new node(40, regles.at(index).at(j)=='a'? 40 : 60, !(regles.at(index).at(j) == 'a'), tmpTab, etage.at(i));
			etageSuivant.push_back(enfant);
			cout << regles.at(index).at(j) << "-";
		}
		cout << "   ";
	}
	cout << endl;
	etage.clear();
  for (int i = 0; i < etageSuivant.size(); ++i) {
		etage.push_back(etageSuivant.at(i));
	}
}

/*
void reecriture (char**tab, int k)
{
  char buff[1024];
  cout<<"boucle "<<k<<endl;
  FILE * pFile;
  int c, a, i=0;
  string str = tab[k-1];
  char bufferTest[1024];
  strcpy (bufferTest,"");

  while (str[i]!= '\0'){
    a=str[i];
    i++;
    pFile=fopen ("myfile.txt","r");
    if (pFile==NULL) perror ("impossible d'ouvrir le fichier !");
    else
      {
        do {
          c = fgetc (pFile);
          if (c==a){
            c = fgetc (pFile);
            if (c == '>'){
              c = fgetc (pFile);
              while (c!='.'){
                int f=sprintf(buff,"%c", (char)c);
                strcat(bufferTest,buff);
                //cout<< "buff="<<buff<<"et buffTest ="<<bufferTest<<endl;
                c = fgetc (pFile);
            }
          }
        }
      } while (c != EOF);
      fclose (pFile);
    }
  }
  tab [k]= (char*)malloc(strlen(bufferTest)+1);
  strcpy(tab[k], bufferTest);
  cout<<"rang"<<k<<" = "<<tab[k]<<endl;
  strcpy (bufferTest,"");
}
*/
