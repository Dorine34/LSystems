#ifndef __CREATION_H__
#define __CREATION_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>//pour le graphe

#include<sstream>

#include "node.h"
#include "afficheps.h"
using namespace std;


double lectureReglesF(char *filenameF,vector<char> *motsF, vector<string> *reglesF);//return angle
void createTreeRankByRankF(vector<node*> *etageF, vector<char> *mots, vector<string> *regles, double angle);
void PreparationArbre(string a, double angle);
int arbrePere(int m, string a, node* pere, double angle, double inclinaison);
#endif