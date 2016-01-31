#ifndef __AFFICHAGE_PS__
#define __AFFICHAGE_PS__

#include <iostream>
#include <fstream>

#include "node.h"

void affichageGraphique(node* root);

void afficheVector(node *racine, std::ofstream* output);
void afficheEdge(node *racine, std::ofstream* output);

#endif
