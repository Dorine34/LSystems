#include "probabilite.h"

  Probabilite::Probabilite(){
    _regles ="X";
    _probabilite=1;
  }
  Probabilite::Probabilite(t_double prob, string regles){
    _probabilite=prob;
    _regles=regles;
  }
  Probabilite::~Probabilite(){}

  t_double Probabilite::getProbabilite(){
    return _probabilite;
  }
  void Probabilite::setProbabilite(t_double prob){
    _probabilite=prob;
  }

  string Probabilite::getString(){
    return _regles;
  }
  void Probabilite::setString(string regles){
    _regles=regles;
  }

  string Probabilite::toString(){
    ostringstream a;
    a<<"la sequence"<<_regles<<" a "<<_probabilite<<" chance de tomber"<<endl;
    return a.str();
  }
