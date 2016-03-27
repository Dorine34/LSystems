#ifndef __CREATION_H__
#define __CREATION_H__

#include <cstdio>
#include <cstdlib>
#include <fstream>//pour le graphe
#include <iostream>
#include <sstream>
#include <string>

#include "afficheps.h"
#include "export.h"
#include "node.h"
#include "probabilite.h"
#include "contexte.h"

using namespace std;

void lectureReglesF(char *filenameF, vector<char> *motsP, vector<Probabilite> *reglesP, vector<Contexte> *contextes, double *angleXY, double *angleZ, double *poids, double *hauteur, string *axiomeDeBase);//return angleXY
void createTreeRankByRankF(vector<node*> *etageF, double angleXY, double angleZ, 
    double hauteur, vector<char> *motsP, vector<Probabilite> *reglesP, double poids, vector<Contexte> *contextes, vector<bool> *svgGravite);
void PreparationArbre(string a, double angleXY, double angleZ, double hauteur, double poids, vector<Contexte> *contextes, vector<bool> *svgGravite);
int arbrePere(int m, string a, node* pere, double angleXY,  double inclinaison, double angleZ, 
  double inclinaisonZ, double hauteur, vector<bool> *svgGravite, double poids, double modifPoids);
void premierAxiome ( string *axiomeDeBase, double * poids, double * hauteur, double * angleXY, double * angleZ, vector<node*> *etageF);
void rechercheContextes(vector<node*> *etageF,string& a,int cpt, vector<Contexte> * contextes, int hauteur);
bool verificationContexteString (string &a,int cpt, vector<Contexte> * contextes, int i, int j, int *base);
void insereRN(string &a, int base, vector<Contexte> * contextes, int i);

//void remplacement(string &a,int cpt, vector<Contexte> * contextes, int i, int *base);
#endif