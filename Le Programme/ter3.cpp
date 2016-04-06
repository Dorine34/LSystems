#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>//pour le graphe
#include <sstream>

#include "node.h"
#include "afficheps.h"
#include "creation.h"
#include "probabilite.h"
#include "export.h"
#include "arbre.h"

using namespace std;

int main(int argc, char** argv)
{
  cout << "Bonjour camarades !" << endl;//message de convivialité (parce que c'est important la convivialite)
  char* filenameF = new char[11];

  sprintf(filenameF, "generateur.txt");

  /**ouverture du fichier**/
  FILE* pFileF;
  if(argc == 2 || argc == 3)
  {
    delete filenameF;
    filenameF = new char[(strlen(argv[1]) + 1)];
    filenameF = argv[1];
  }
  pFileF = fopen(filenameF, "r");

  if(pFileF == NULL)
  {
    perror("Impossible d'ouvrir le fichier ");
    return -1;
  }

  fclose(pFileF);

/****ceci est mes nouveaux rajouts********/
  arbre* arbre1 = new arbre ();
  cout<<"definition de l'arbre :"<<endl;
  //cout<<arbre1->toString()<<endl;
  arbre1->lectureReglesF(filenameF);
  //cout<<arbre1->toString()<<endl;
  cout << endl << "contexte enregistre :" << endl;
  /** partie correspondant à arbre**/
  cout<<"et concernant arbre :"<<endl;
  arbre1->premierAxiome();
  cout<<arbre1->toString()<<endl;

  char saisie[100];

  if(argc == 3)
  {
    int arg = atoi(argv[2]);
    cout << arg << endl;
    for(int i = 0; i < arg; ++i)
    {
      arbre1->createTreeRankByRankF();

    }
    return 0;
  }

  cout << "Appuyez sur une touche pour continuer, un nombre pour avancer directement au rang et quit pour quitter" << endl;
  cin >> saisie;

  while(strcmp(saisie, "quit") != 0)
  {
    if((saisie[0] <= '9') && (saisie[0]>= '0'))
    {
      cout << "c'est un nombre!" << endl;//cas ou on passe plusieurs sequences en meme temps
      int s = atoi(saisie);
      cout << s << endl;
      for(int i = 0; i<s;i++)
      {
        cout << endl << "Resultat : " << endl << endl;
        arbre1->createTreeRankByRankF();
      }

      cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
      cin >> saisie;
    }
    else
    {//cas etage par etage
      arbre1->createTreeRankByRankF();

      cout << endl << "Resultat : " << endl ;
      cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
      cin >> saisie;
    }
  }
  return 0;
}
