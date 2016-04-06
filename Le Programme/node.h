#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>

#include "defines.h"

class node
{
public:
  node();
  node(node*, t_double, t_double,t_double, t_double, t_double, char*, t_double, bool);
  node(t_double, t_double, t_double, t_double, bool, char*, node*);
  ~node();
  /*WIP*/
  t_double   DD_X;
  t_double   DD_Y;
  t_double   DD_Z;

  t_double   EE_X;
  t_double   EE_Y;
  t_double   EE_Z;

  t_double o_DD_X;
  t_double o_DD_Y;
  t_double o_DD_Z;

  t_double o_EE_X;
  t_double o_EE_Y;
  t_double o_EE_Z;

  void contour(int);
  /**/
  node& operator=(const node &n);

  void ajoutEnfant(node*);

  char* getName();
  void setName(char*);

  t_double getX();
  void setX(t_double);

  t_double getY();
  void setY(t_double);

  t_double getZ();
  void setZ(t_double);

  t_double getInclinaisonXY();
  void setInclinaisonXY(t_double);

  t_double getInclinaisonZ();
  void setInclinaisonZ(t_double);


  t_double getAngleXY();
  void setAngleXY(t_double);

  t_double getAngleZ();
  void setAngleZ(t_double);


  node* getPere();
  void setPere(node*);

  node* getEnfant(int);
  void voirEnfant();
  std::vector<node*>* getEnfants();
  void setEnfants(std::vector<node*>*);

  t_double getPoids();
  void setPoids(t_double);

  bool getgravite();
  void setgravite(bool);

private:
  char* name;
  t_double x, y, z, inclinaisonXY, inclinaisonZ, poids;
  node* pere;
  std::vector<node*> *enfants;
  t_double angleXY, angleZ;
  bool gravite;
};

#endif
