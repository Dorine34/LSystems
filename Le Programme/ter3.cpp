/****************Faire Pousser des Arbres en Pogrammant
 * Fait le 20/02
 *
 * Petite coquille avec les ordonnées
 *
 *
 *****************Yin, Arcadia et Oxidire*******************/


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

using namespace std;

int main(int argc, char** argv)
{
  cout << "Bonjour camarades !" << endl;//message de convivialité (parce que c'est important la convivialite)

  vector<node*> etageF;//etages selon le rang de creation du mot
  vector<Probabilite> reglesP;// contraintes rangees par domaine
  vector<Contexte> contextes;// contexte sensitif
  vector<char> motsP;//les mots formes a partir de probabilite
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

  string axiomeDeBase;
  double angleXY;
  double angleZ = 0;
  double poids;
  double hauteur;

  lectureReglesF(filenameF, &motsP, &reglesP, &contextes, &angleXY, &angleZ, &poids, &hauteur, &axiomeDeBase);

  cout << endl << "contexte enregistre :" << endl;
  for(unsigned int j  = 0; j < contextes.size(); j++)
  {
    cout << "j = " <<j <<" et"<<contextes[j].toString()<<endl;
  }
  /*
  cout << endl << "tableau enregistre :" << endl;
  for(unsigned int j  = 0; j < reglesP.size(); j++)
  {
    cout << "j = " << j << " motsP = " << motsP[j] << " -> " << reglesP[j].getString() << "de probabilite" << reglesP[j].getProbabilite() << endl;
  }
  */

  cout << "angleXY = " << angleXY << " et angleZ = " << angleZ << endl;
  cout << "axiome de base = " << axiomeDeBase << "de taille :" << axiomeDeBase.size() << endl;

  premierAxiome(&axiomeDeBase, &poids, &hauteur, &angleXY, &angleZ, &etageF);

  char saisie[100];

  if(argc == 3)
  {
    int arg = atoi(argv[2]);
    cout << arg << endl;
    for(int i = 0; i < arg; ++i)
    {
      createTreeRankByRankF(&etageF, angleXY, angleZ, hauteur, &motsP, &reglesP, poids, &contextes);//la creation en soit de l'arbre qui donnera le mot
      //contextLie(&etageF,&contextes);
      //contextesLies(&etageF,&contextes);
    }
    for (unsigned int i = 0; i < etageF.size(); ++i)
    {
      delete etageF.at(i);
    }
    // exportObj(etageF.at(0), filenameF);
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
        createTreeRankByRankF(&etageF, angleXY, angleZ, hauteur, &motsP, &reglesP, poids, &contextes);//la creation en soit de l'arbre qui donnera le mot
        //contextLie(&etageF,&contextes);
        //contextesLies(&etageF,&contextes);
      }

      cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
      cin >> saisie;
    }
    else
    {//cas etage par etage
      createTreeRankByRankF(&etageF, angleXY, angleZ, hauteur, &motsP, &reglesP, poids, &contextes);//la creation en soit
      //contextLie(&etageF,&contextes);
      //contextesLies(&etageF,&contextes);
  
      cout << endl << "Resultat : " << endl ;
      cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
      cin >> saisie;
    }
  }
  /*
  cout << "pour conclure :" << endl;

  for(int i = 0; i < etageF.size(); ++i)
  {
    cout << etageF.at(i)->getName()[0] << " a un poids de " << etageF.at(i)->getPoids() << endl;
    delete(etageF.at(i));
  }
  */  
  for (unsigned int i = 0; i < etageF.size(); ++i)
  {
    delete etageF.at(i);
  }
  // delete filenameF;
  return 0;
}
