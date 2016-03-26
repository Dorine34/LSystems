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
  Contexte(string, int, string, bool);
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
  
  bool getGravite();
  void setGravite(bool);

protected:

  string _reglesNouvelles;
  int _posDuCaractere;
  string _reglesAnciennes;
  bool _gravite;  
  };

#endif
