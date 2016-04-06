#ifndef __ARBRE_H__
#define __ARBRE_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>


#include "node.h"
#include "probabilite.h"
#include "contexte.h"
#include "creation.h"
#include "export.h"

#include <fstream>      // std::ifstream


using namespace std;
class arbre
{
public:
  arbre();
  arbre( double, double, int, double, double, double, double,
    vector<node*>, vector<Probabilite>, vector<Contexte>, vector<char>, vector<bool>, string);

  ~arbre();

  arbre& operator=(const arbre &a);


  double getOrdonneeRacineX();
  void setOrdonnneeRacineX(double r);
  double getOrdonneeRacineZ();
  void setOrdonnneeRacineZ(double r);
  int getNbIterations ();
  void setNbIterations (int i);

  double getAngleXY ();
  void setAngleXY (double a);

  double getAngleZ ();
  void setAngleZ (double a);

  double getPoids ();
  void setPoids (double a);

  double getHauteur ();
  void setHauteur (double a);

  vector <node*> getEtageF();
  void setEtageF(vector <node*> n);
  void rajoutNode(node* n);

  vector<Probabilite> getReglesP ();
  void setReglesP(vector<Probabilite> p);
  void rajoutProba(Probabilite p);

  vector<Contexte> getContexte ();
  void setContexte(vector<Contexte> c);
  void rajoutContexte(Contexte c);

  vector<char> getMotsP();
  void setMotsP(vector<char> m);
  void rajoutMot(char c);

  vector<bool> getSvgGravite();
  void setSvgGravite(vector<bool> s);
  void rajoutGravite(bool s);

  string getAxiomeDeBase();
  void setAxiomeDeBase(string ax);

  void lectureReglesF(char *filenameF);
  string toString();
  void premierAxiome();

  void createTreeRankByRankF();
  void preparationArbre(string a);
  double puissanceMoins10(double x, int p);
  int arbrePere(int m, string a, node* pere,  double inclinaisonXY,
              double inclinaisonZ, double modifPoids);

private:

  double _ordonneeRacineX, _ordonneeRacineZ;
  int _nombreIterations;
  double _angleXY, _angleZ, _poids, _hauteur;

  vector<node*> _etageF;//etages selon le rang de creation du mot
  vector<Probabilite> _reglesP;// contraintes rangees par domaine
  vector<Contexte> _contextes;// contexte sensitif
  vector<char> _motsP;//les mots formes a partir de probabilite
  vector<bool> _svgGravite; //permet de svg les gravites en fonction des contextes
  string _axiomeDeBase;
};

#endif
