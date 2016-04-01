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

void rechercheContextes(vector<node*> *etageF,string& a,int cpt, vector<Contexte> * contextes, int hauteur);
bool verificationContexteString (string &a,int cpt, vector<Contexte> * contextes, int i, int j, int *base);
void insereRN(string &a, int base, vector<Contexte> * contextes, int i);
#endif