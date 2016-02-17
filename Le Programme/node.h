#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>

#define PI 3.14159265

class node
{
public:
  node();
  node(node*, double, double,double, double, double, char*);
  node(double, double, double, bool, char*, node*);
  ~node();

  void ajoutEnfant(node*);
  void resetDV();

  bool getDV();
  void setDV(bool);

  char* getName();
  void setName(char*);

  double getX();
  void setX(double);

  double getY();
  void setY(double);

  double getInclinaisonXY();
  void setInclinaisonXY(double);

  double getInclinaisonZ();
  void setInclinaisonZ(double);

  node* getPere();
  void setPere(node*);

  node* getEnfant(int);
  void setEnfants(std::vector<node*>*);
  std::vector<node*>* getEnfants();


  double getZ();
  void setZ(double);

protected:
  bool dv;
  char* name;
  double x, y, z, inclinaisonXY, inclinaisonZ;
  node* pere;
  std::vector<node*> *enfants;
  double angleXY, angleZ;
};

#endif
