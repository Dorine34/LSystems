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
  node(node*, double, double,double, double, double, char*, double, bool);
  node(double, double, double, double, bool, char*, node*);
  ~node();

  node& operator=(const node &n);

  void ajoutEnfant(node*);

  char* getName();
  void setName(char*);

  double getX();
  void setX(double);

  double getY();
  void setY(double);

  double getZ();
  void setZ(double);

  double getInclinaisonXY();
  void setInclinaisonXY(double);

  double getInclinaisonZ();
  void setInclinaisonZ(double);


  double getAngleXY();
  void setAngleXY(double);

  double getAngleZ();
  void setAngleZ(double);
  

  node* getPere();
  void setPere(node*);

  node* getEnfant(int);
  void voirEnfant();
  std::vector<node*>* getEnfants();
  void setEnfants(std::vector<node*>*);

  double getPoids();
  void setPoids(double);

  bool getgravite();
  void setgravite(bool);
  
private:
  char* name;
  double x, y, z, inclinaisonXY, inclinaisonZ, poids;
  node* pere;
  std::vector<node*> *enfants;
  double angleXY, angleZ;
  bool gravite;
};

#endif
