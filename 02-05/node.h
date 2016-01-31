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
  node(node*, long, long, long, char*);
  node(long, long, bool, char*, node*);
  ~node();

  void ajoutEnfant(node*);
  void resetDV();

  bool getDV();
  void setDV(bool);

  char* getName();
  void setName(char*);

  long getX();
  void setX(long);

  long getY();
  void setY(long);

  long getInclinaison();
  void setInclinaison(long);

  node* getPere();
  void setPere(node*);

  node* getEnfant(int);
  void setEnfants(std::vector<node*>*);
  std::vector<node*>* getEnfants();

protected:
  bool dv;
  char* name;
  long x, y, inclinaison;
  node* pere;
  std::vector<node*> *enfants;
  long angle;
};

#endif
