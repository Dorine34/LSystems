#ifndef __PROBABILITE_H__
#define __PROBABILITE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>
#include <sstream>

#include "defines.h"

using namespace std;

class Probabilite
{
public:
  Probabilite();
  Probabilite(t_double, string);
  ~Probabilite();

  t_double getProbabilite();
  void setProbabilite(t_double);

  string getString();
  void setString(string);

  string toString();

protected:
  string _regles;
  t_double _probabilite;
  };

#endif
