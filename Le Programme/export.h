#ifndef __EXPORT_H__
#define __EXPORT_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>

#include "node.h"

typedef double t_double;

class Export
{
public:
  Export(node*, bool);
  Export(std::vector<node*>, bool);
  ~Export();
private:
  int last;
  std::ofstream out;

  void exportObj(node*, bool, int);
  /**/
  std::string exportVertices(t_double, t_double, t_double);
  /**/
  std::string exportRoot(node*);
  std::string exportEdge(node*, node*, node*, int);
  /**/
  std::string exportApex(int);
  std::string exportTrunk(int pere);
  /**/
  int recurExportSimple(node*);
  int recurExportTrunk(node*);



  void promptXYZ(t_double, t_double, t_double);
};

#endif
