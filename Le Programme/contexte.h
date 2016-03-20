#ifndef __CONTEXTE_H__
#define __CONTEXTE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;


class Contexte
{
public:
  Contexte();
  Contexte(string, int, string);
  ~Contexte();

  int getPosDuCaractere();
  void setPosDuCaractere(int);

  string getReglesNouvelles();
  void setReglesNouvelles(string);
  void ajoutReglesNouvelles(char);
  

  string getReglesAnciennes();
  void setReglesAnciennes(string);
  void ajoutReglesAnciennes(char);

  string toString();
  
protected:

  string _reglesNouvelles;
  int _posDuCaractere;
  string _reglesAnciennes;
  
  };

#endif
