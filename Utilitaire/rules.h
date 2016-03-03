#ifndef __RULES_H__
#define __RULES_H__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define STOP  0
#define KILL  1
#define SETD  2
#define XY    3
#define Z     4
#define LARG  5
#define LONG  6
#define AXIO  7
#define ADD   8
#define PRIN  9

class Rules
{
public:
  Rules();
  ~Rules();

  int getXY();
  void setXY(int);
  
  int getZ();
  void setZ(int);
  
  int getLargeur();
  void setLargeur(int);
  
  int getLongueur();
  void setLongueur(int);
  
  std::string getAxiom();
  void setAxiom(std::string);
  
  std::string getRule(int);
  std::vector<std::string> getRules();
  void setRules(std::vector<std::string>);
  void addRule(std::string);

private:
  int angXY, angZ, largeur, longueur;
  std::string axiom;
  std::vector<std::string> rules;
  void choice();
  void write();
  void printVar();
};

#endif
