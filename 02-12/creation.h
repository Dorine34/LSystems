#ifndef __CREATION_H__
#define __CREATION_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>//pour le graphe

#include <sstream>

#include "node.h"
#include "afficheps.h"
#include "probabilite.h"
using namespace std;


double lectureReglesF(char *filenameF, vector<char> *motsP, vector<Probabilite> *reglesP);//return angle
void createTreeRankByRankF(vector<node*> *etageF, double angle, vector<char> *motsP, vector<Probabilite> *reglesP);
void PreparationArbre(string a, double angle);
int arbrePere(int m, string a, node* pere, double angle, double inclinaison);
#endif