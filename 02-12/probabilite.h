#ifndef __PROBABILITE_H__
#define __PROBABILITE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;


class Probabilite
{
public:
  Probabilite();
  Probabilite(double, string);
  ~Probabilite();

  double getProbabilite();
  void setProbabilite(double);

  string getString();
  void setString(string);
  
  string toString();
  
protected:
  string _regles;
  double _probabilite;
  };

#endif
