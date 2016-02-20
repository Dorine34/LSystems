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

using namespace std;

void lectureReglesF(char *filenameF, vector<char> *motsP, vector<Probabilite> *reglesP, double *angleXY, double *angleZ, double *poids, double *hauteur, string *axiomeDeBase);//return angleXY
void createTreeRankByRankF(vector<node*> *etageF, double angleXY, double angleZ, double hauteur, vector<char> *motsP, vector<Probabilite> *reglesP, double poids);
void PreparationArbre(string a, double angleXY, double angleZ, double hauteur, double poids);
int arbrePere(int m, string a, node* pere, double angleXY,  double inclinaison, double angleZ, double inclinaisonZ, double hauteur);
void premierAxiome ( string *axiomeDeBase, double * poids, double * hauteur, double * angleXY, double * angleZ, vector<node*> *etageF);

#endif
