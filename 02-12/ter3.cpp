/****************Faire Pousser des Arbres en Pogrammant*************/
/* Fait le 04/02
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
#include<sstream>

#include "node.h"
#include "afficheps.h"
#include "creation.h"

using namespace std;
 

int main(int argc, char** argv)
{
  vector<string> reglesF; //les regles a respecter
  vector<node*> etageF;//etages selon le rang de creation du mot
  vector<char> motsF;//les mots formes
  cout <<  "Bonjour camarades !" << endl;//message de convivialité (parce que c'est important la convivialite)
  char* tabF[100];//recupere les regles
  char strF[80];//buffer pour les string
  char* filenameF = new char[11 * sizeof(char)];
  sprintf(filenameF, "generateur.txt");

  FILE* pFileF;
  if(argc == 2)
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

  double angle =lectureReglesF(filenameF, &motsF, &reglesF);
  
  char motRacineF = motsF.at(0);
  motsF.erase(motsF.begin());
  char *tmpTabF = new char[2];
  tmpTabF[0] = motRacineF;
  tmpTabF[1] = '\0';
  cout<<"mot tmp = "<<tmpTabF<<endl;
  
  node* racineF = new node(NULL, 500, 500, 90, tmpTabF);//sert actuellement a rien
  etageF.push_back(racineF);
  
  tabF[0] = new char[(strlen(strF) + 1) * sizeof(char)];
  strcpy(tabF[0], strF);
  char saisie[100];

  cout << "Appuyez sur une touche pour continuer, un nombre pour avancer directement au rang et quit pour quitter" << endl;
  cin >> saisie;

  while(strcmp(saisie, "quit") != 0)
  {
    if ((saisie [0]<='9')&&(saisie [0]>='0')){cout<<"c'est un nombre!"<<endl;//cas ou on passe plusieurs sequences en meme temps
    int s= atoi(saisie);
    cout<<s<<endl;
    for (int i=0; i<s;i++){ 
      cout << endl << "Resultat : " << endl << endl;
      createTreeRankByRankF(&etageF,&motsF, &reglesF, angle);//la creation en soit de l'arbre qui donnera le mot
    }
    cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
    cin >> saisie;
    }
    else{//cas etage par etage
      createTreeRankByRankF(&etageF,&motsF, &reglesF, angle);//la creation en soit
      cout << endl << "Resultat : " << endl ;
      cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
      cin >> saisie;}
  }
  delete filenameF;
  return 0;
}
