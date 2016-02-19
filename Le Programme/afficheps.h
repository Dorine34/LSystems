#ifndef __AFFICHAGE_PS__
#define __AFFICHAGE_PS__

#include "node.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <vector>
#include <math.h>//permet d'utiliser sqrt
#include <time.h>


void affichageGraphique(node* root);

void afficheVector(node *racine, std::ofstream* output);
void afficheEdge(node *racine, std::ofstream* output);
#endif
