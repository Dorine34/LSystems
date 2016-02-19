/****************Faire Pousser des Arbres en Pogrammant*************/
/* Fait le 20/02
/*
/* Petite coquille avec les ordonnées
/*
/* 
/*****************Yin, Arcadia et Oxidire*******************/


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
  vector<char> motsP;//les mots formes a partir de probabilite

  char* tabF[100];//recupere les regles
  char strF[80];//buffer pour les string
  
  char* filenameF = new char[11 * sizeof(char)];
  sprintf(filenameF, "generateur.txt");

/**ouverture du fichier**/
  FILE* pFileF;
  if(argc == 2 || argc == 3)
  {
    delete filenameF;
    filenameF = new char[(strlen(argv[1]) + 1) * sizeof(char)];
    filenameF = argv[1];
  }
  pFileF = fopen(filenameF, "r");

  if(pFileF == NULL)
  {
    perror("Impossible d'ouvrir le fichier ");
    return -1;
  }
  else
  {
    fgets(strF, 2, pFileF) != NULL;
  }

  fclose(pFileF);

  string axiomeDeBase;
  double angleXY;
  double angleZ = 0;
  lectureReglesF(filenameF, &motsP, &reglesP, &angleXY, &angleZ, &axiomeDeBase);
/*
  cout << endl << "tableau enregistre :" << endl;
  for(int j  = 0; j<reglesP.size(); j++)
  {
      cout << "j = " << j << " motsP = " << motsP[j] << " -> " << reglesP[j].getString() << "de probabilite" << reglesP[j].getProbabilite() << endl;
    }
*/
    cout << "angleXY = " << angleXY << " et angleZ = " << angleZ << endl;
  //cout << "axiome de base = " << axiomeDeBase << "de taille :" << axiomeDeBase.size() << endl;
  char motRacineF;
  node* racineF;
  node *racine;
  if(axiomeDeBase.size() == 1)
  {
    motRacineF = axiomeDeBase[0];
    
    char *tmpTabF = new char[2];
    tmpTabF[0] = motRacineF;
    tmpTabF[1] = '\0';
    //cout << "mot tmp = " << tmpTabF << endl;
    racineF = new node(NULL, 0, 0, 0, 0, 0, tmpTabF);//sert actuellement a rien
    etageF.push_back(racineF);
  }
  else {
    motRacineF = 'R';
    char *tmpTabF = new char[2];
    tmpTabF[0] = motRacineF;
    tmpTabF[1] = '\0';
   // cout << "mot tmp = " << tmpTabF << endl;
    racineF = new node(NULL, 0, 0, 0, 0, 0, tmpTabF);
    etageF.push_back(racineF);
    if(axiomeDeBase.size() != 1)
    {//cas ou l axiome de base est multiple, on cree ici le premier etage
      etageF.pop_back();
      char*nom = (char *) malloc(axiomeDeBase.size());
      node*pere = racineF;
      node*enfant;
      int m = 0;
      int n = 0;
      double inclinaisonXY = 0;
      double inclinaisonZ = 0;
      while(n<axiomeDeBase.size())
      {
        nom[m] = axiomeDeBase[n];
        //cout << "nom[m] = " << nom[m] << endl;
        if (((nom[m] >64)&&(nom[m] <91))||((nom[m] >96)&&(nom[m] <123)))
        {
          nom[m+1] = '\0'; m = -1;
          enfant = new node(10, inclinaisonXY, inclinaisonZ, true, nom, pere );
          //cout << "nom de l'enfant" << nom << "nom du pere : " << pere->getName() << endl;
          pere = enfant;
          etageF.push_back(enfant);
        }
        else {
          if(nom[m] == '[')
          {
  //            cout << "1er test inclinaisonXY  = " << inclinaisonXY << endl;
            m = arbrePere(m, nom, pere, angleXY, inclinaisonXY, angleZ, inclinaisonZ);
          }
          if(nom[m] == '+')
          {
            inclinaisonXY-= angleXY;
            // cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
          }
          if(nom[m] == '-')
          {
            inclinaisonXY += angleXY;
            //cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
          }

          nom[m+1] = '\0';
          m = -1;
          enfant = new node(10, inclinaisonXY, inclinaisonZ, true, nom, pere );
          //cout << "nom de l'enfant" << nom << "nom du pere : " << pere->getName() << endl;
          pere = enfant;
          etageF.push_back(enfant);
        }
        m++;
        n++;
      }
      nom[axiomeDeBase.size()+1] = '\0';
    //  cout << "le nom est :" << nom << endl;
      racine = new node(10, angleXY, angleZ, true, nom, racineF);
      //etageF.push_back(racine);
      free(nom);
    }
  }
  /*cout << "etageF = " << endl;
  for(int i = 0; i<etageF.size();i++)
  {
    cout << etageF.at(i)->getName() << " x = " << etageF.at(i)->getX() << " y = " << etageF.at(i)->getY() << endl;
  }
  */
  //cout << " rajout de " << axiomeDeBase[0];

  //affichageGraphique(etageF.at(0));




  tabF[0] = new char[(strlen(strF) + 1) * sizeof(char)];
  strcpy(tabF[0], strF);
  char saisie[100];

  if(argc == 3)
  {
    int arg = atoi(argv[2]);
    cout << arg << endl;
    for(int i = 0; i<arg;i++)
    { 
      createTreeRankByRankF(&etageF, angleXY, angleZ, &motsP, &reglesP);//la creation en soit de l'arbre qui donnera le mot
    }
    // exportObj(etageF.at(0), filenameF);
    return 0;
  }

  cout << "Appuyez sur une touche pour continuer, un nombre pour avancer directement au rang et quit pour quitter" << endl;
  cin >> saisie;

  while(strcmp(saisie, "quit") != 0)
  {
    if ((saisie [0]<= '9')&&(saisie [0]>= '0'))
    {
      cout << "c'est un nombre!" << endl;//cas ou on passe plusieurs sequences en meme temps
      int s = atoi(saisie);
      cout << s << endl;
      for(int i = 0; i<s;i++)
      { 
        cout << endl << "Resultat : " << endl << endl;
        createTreeRankByRankF(&etageF, angleXY, angleZ, &motsP, &reglesP);//la creation en soit de l'arbre qui donnera le mot
      }
      cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
      cin >> saisie;
    }
    else
    {//cas etage par etage
      createTreeRankByRankF(&etageF, angleXY, angleZ, &motsP, &reglesP);//la creation en soit
      cout << endl << "Resultat : " << endl ;
      cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
      cin >> saisie;
    }
  }
  delete filenameF;
  return 0;
}
