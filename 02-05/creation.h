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


long lectureReglesF(char *filenameF,vector<char> *motsF, vector<string> *reglesF);//return angle
void createTreeRankByRankF(vector<node*> *etageF, vector<char> *mots, vector<string> *regles, long angle);
void PreparationArbre(string a, long angle);
int arbrePere(int m, string a, node* pere, long angle, long inclinaison);
#endif