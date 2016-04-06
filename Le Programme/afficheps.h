#ifndef __AFFICHAGE_PS__
#define __AFFICHAGE_PS__

#include "node.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <vector>
#include <time.h>

#include "defines.h"

void affichageGraphique(node* root);

void afficheVector(node *racine, std::ofstream* output);
void afficheEdge(node *racine, std::ofstream* output);
#endif
