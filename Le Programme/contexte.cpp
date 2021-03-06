#include "contexte.h"


Contexte::Contexte()
{
  _reglesNouvelles= 'A';
  _posDuCaractere= 0;
  _reglesAnciennes= 'A';
  _gravite=false;
}

Contexte::Contexte(string rn, int a, string ra, bool g)
{
  _reglesNouvelles= rn;
  _posDuCaractere= a;
  _reglesAnciennes= ra;
  _gravite=g;
}

Contexte::~Contexte(){}

int Contexte::getPosDuCaractere()
{
  return _posDuCaractere;
}
void Contexte::setPosDuCaractere( int a)
{
  cout<<" (contexte )le caractere devient"<<a<<endl;
  _posDuCaractere=a; 
}

string Contexte::getReglesNouvelles()
{
  return _reglesNouvelles;
}
void Contexte::setReglesNouvelles(string rn )
{
  _reglesNouvelles=rn;
}

void Contexte::ajoutReglesNouvelles(char c)
{
  _reglesNouvelles+=c; 
}

string Contexte::getReglesAnciennes()
{
  return _reglesAnciennes;
}
void Contexte::setReglesAnciennes(string ra)
{
  _reglesAnciennes=ra;
}

void Contexte::ajoutReglesAnciennes(char c)
{
  _reglesAnciennes+=c;
}


bool Contexte::getGravite()
{
  return _gravite; 
}
void Contexte::setGravite(bool g)
{
  _gravite=g;
}
  
string Contexte::toString()
{
  ostringstream a;
    a<<"l'ancienne regle"<<_reglesAnciennes<<" , la nouvelle regles "<<_reglesNouvelles<<", la position :"<<_posDuCaractere;
    if (_gravite)
    {
      a<<" et la gravite est enclenchee";
    } 
    a<<endl;
    return a.str(); 
}