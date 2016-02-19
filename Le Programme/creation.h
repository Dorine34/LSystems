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

void lectureReglesF(char *filenameF, vector<char> *motsP, vector<Probabilite> *reglesP, double *angleXY, double *angleZ, string *axiomeDeBase);//return angleXY
void createTreeRankByRankF(vector<node*> *etageF, double angleXY, double angleZ, vector<char> *motsP, vector<Probabilite> *reglesP);
void PreparationArbre(string a, double angleXY, double angleZ);
int arbrePere(int m, string a, node* pere, double angleXY, double inclinaison, double angleZ, double inclinaisonZ);
#endif
