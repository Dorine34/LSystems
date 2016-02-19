#ifndef __EXPORT_H__
#define __EXPORT_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>

#include "node.h"

int recurExport(node*, std::ofstream*, int);
// void exportObj(node*, std::string);
void exportObj(node*);

#endif
