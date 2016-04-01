#include "arbre.h"

arbre::arbre()
{
  setOrdonnneeRacineX(0);
  setOrdonnneeRacineZ(0);
  setNbIterations (0);
  setAngleXY (0);
  setAngleZ (0);
  setPoids (0);
  setHauteur (0);

  vector<Probabilite> vp;
  vector<Contexte> c;
  vector<bool> vb;
  vector<char> cp;  
  vector<node*> etageF;

  setReglesP(vp);
  setSvgGravite(vb);
  setMotsP(cp);
  setAxiomeDeBase("");
  setEtageF(etageF);
  setContexte(c);

}
  
arbre::arbre( double x, double z, int i, double angleXY, double angleZ , double poids, double hauteur,
    vector<node*> etageF, vector<Probabilite> vp, vector<Contexte> c, vector<char> cp, vector<bool> vb, string ax)
{
  setOrdonnneeRacineX(x);
  setOrdonnneeRacineZ(z);
  setNbIterations (i);
  setAngleXY (angleXY);
  setAngleZ (angleZ);
  setPoids (poids);
  setHauteur (hauteur);

  setReglesP(vp);
  setSvgGravite(vb);
  setMotsP(cp);
  setAxiomeDeBase(ax);
  setEtageF(etageF);
  setContexte(c);
}

arbre::~arbre(){}

arbre& arbre::operator=(const arbre &a)
{
  
  setOrdonnneeRacineX(a._ordonneeRacineX);
  setOrdonnneeRacineZ(a._ordonneeRacineZ);
  setNbIterations (a._nombreIterations);
  setAngleXY (a._angleXY);
  setAngleZ (a._angleZ);
  setPoids (a._poids);
  setHauteur (a._hauteur);
  setReglesP(a._reglesP);
  setSvgGravite(a._svgGravite);
  setMotsP(a._motsP);
  setAxiomeDeBase(a._axiomeDeBase);
  setEtageF(a._etageF);
  setContexte(a._contextes);
  return *this;
}

  
  double arbre::getOrdonneeRacineX()
  {
    return _ordonneeRacineX;
  }
  void arbre::setOrdonnneeRacineX(double r)
  {
    _ordonneeRacineX=r;
  }  


  double arbre::getOrdonneeRacineZ()
  {
    return _ordonneeRacineZ;
  }
  void arbre::setOrdonnneeRacineZ(double r)
  {
    _ordonneeRacineZ=r;
  }

  int arbre::getNbIterations ()
  {
    return _nombreIterations;
  }
  void arbre::setNbIterations (int i)
  {
    _nombreIterations=i;
  }

  double arbre::getAngleXY ()
  {
    return _angleXY;
  }
  void arbre::setAngleXY (double a)
  {
    _angleXY=a;
  }
  
  double arbre::getAngleZ ()
  {
    return _angleZ;
  }
  void arbre::setAngleZ (double a)
  {
    _angleZ=a;
  }
  
  double arbre::getPoids ()
  {
    return _poids;
  }
  void arbre::setPoids (double a)
  {
    _poids=a;
  }
  
  double arbre::getHauteur ()
  {
    return _hauteur;
  }
  void arbre::setHauteur (double a)
  {
    _hauteur=a;
  }

  vector <node*> arbre::getEtageF()
  {
    return _etageF;
  }
  void arbre::setEtageF(vector <node*> n)
  {
    _etageF=n;
  }
  void arbre::rajoutNode(node* n)
  {
    _etageF.push_back(n);
  }


  vector<Probabilite> arbre::getReglesP ()
  {
    return _reglesP;
  }
  void arbre::setReglesP(vector<Probabilite> p)
  {
    _reglesP=p;
  }
  void arbre::rajoutProba(Probabilite p)
  {
    _reglesP.push_back(p);
  }

  vector<Contexte> arbre::getContexte ()
  {
    return _contextes;
  }
  void arbre::setContexte(vector<Contexte> c)
  {
    _contextes=c;
  }
  void arbre::rajoutContexte(Contexte c)
  {
    _contextes.push_back(c);
  }

  vector<char> arbre::getMotsP()
  {
    return _motsP;
  }  
  void arbre::setMotsP(vector<char> m)
  {
    _motsP=m;
  }
  void arbre::rajoutMot(char c)
  {
    _motsP.push_back(c);
  }


  vector<bool> arbre::getSvgGravite()
  {
    return _svgGravite;
  }
  void arbre::setSvgGravite(vector<bool> s)
  {
    _svgGravite= s;
  }  
  void arbre::rajoutGravite(bool s)
  {
    _svgGravite.push_back(s);
  }

  string arbre::getAxiomeDeBase()
  {
    return _axiomeDeBase;
  }
  void arbre::setAxiomeDeBase(string ax)
  {
    _axiomeDeBase=ax;
  }

  void arbre::lectureReglesF(char *filenameF)
  {
    int cpt = 0;
    setAngleXY(0);
    setAngleZ(0);
    setAxiomeDeBase("");

    double probabilite = 0;
    ifstream file(filenameF);
    if(!file.is_open())
    {
      perror("File not found");
    }
    string line;
    bool b = false;
    bool premierAxiome = false;
    bool angleXYFait = false;
    bool angleZFait = false;
    bool poidsArbreFait = false;
    bool longueurBrancheFait = false;
    bool contexteFait = false;
    
  while(getline(file, line))
  {
    b = false;
    for(unsigned int k = 0; k < line.size(); ++k)
    {
      if(!angleXYFait)
      {
        if((k >= 8) && (line[k] != '.'))// recupere la premiere donnee correspondant Ã  l'angleXYXY
        {
          setAngleXY(getAngleXY()*10+line[k] - 48);
          //*angleXY = (*angleXY) * 10 + line[k] - 48;
        }
        if(line[k] == '.')
        {
          angleXYFait = true;
          cout << "angleXY=" << getAngleXY() << endl;
          //cout << "angleXY=" << *angleXY << endl;
        }
      }
      else
      {
        if(!angleZFait)// recupere la premiere donnee correspondant Ã  l'angleXYXY
        {
          if((k >= 7) && (line[k] != '.'))// recupere la premiere donnee correspondant Ã  l'angleXYXY
            {
              setAngleZ(getAngleZ()*10+line[k] - 48);
              //*angleZ = (*angleZ) * 10 + line[k] - 48;
            }
          if(line[k] == '.')
          {
            angleZFait = true;
            cout << "angleZ=" << getAngleZ() << endl;
            //cout << "angleZ=" << *angleZ << endl;
          }
        }
        else
        {
          if(!poidsArbreFait)
          {
          // cout << "line[" << k << "]=" << line[k] << endl;
            if((k>=8)&&(line[k] != '.'))// recupere la premiere donnee correspondant Ã  l'angleXYXY
            {
              setPoids(getPoids()*10+line[k] - 48);
              //*poids = (*poids) * 10 + line[k] - 48;
            }
            if(line[k] == '.')
            {
              poidsArbreFait = true;
              cout << "poids=" << getPoids() << endl;
              //cout << "poids=" << *poids << endl;
            }
          }
          else
          {
            if(!longueurBrancheFait)
              {
                // cout << "line[" << k << "]=" << line[k] << endl;
                if((k >= 9) && (line[k] != '.'))// recupere la premiere donnee correspondant Ã  l'angleXYXY
                {
                  setHauteur(getHauteur()*10+line[k] - 48);
                  //*hauteur = (*hauteur) * 10 + line[k] - 48;
                }
                if(line[k] == '.')
                {    
                  longueurBrancheFait = true;
                  cout << "hauteur=" << getHauteur() << endl;
                  //cout << "hauteur=" << *hauteur << endl;
                }
              }
            else
            {
              //cout<<"bonjour je m'appelle test1!"<<endl;
              if(!contexteFait)
              {
                //cout<<"bonjour je m'appelle test1 contexte non fait!"<<endl;
                if ((k >= 9) && (line[k] != '.'))
                {
                  //cout<<"bonjour debut contexte!"<<endl;
                  int gravite=false;
                  if (line[k]=='g')
                  {
                    //cout<<"bonjour je m'appelle test1! gravite"<<endl;
                    //cout<<" enclenchement de la gravite :";
                    k++;
                    gravite=true;
                  }
                  //cout<<"bonjour je m'appelle test1 co!"<<endl;
                  Contexte co ("",0,"", gravite);
                  bool baseFaite=false;
                  bool fait =false;
                  int pos=k;
                  //cout<<"bonjour je m'appelle test1 pas co!"<<endl;
                  while ((line[k] != ',') && (line[k] != '.'))
                  {
                    //cout<<"bonjour^^ je m'appelle test1!"<<endl;
                    //cout<<"line[k]= "<<line[k]<<"et pos= "<<pos<< "et k-pos="<<k-pos<<endl;
                    if (line[k] == '=')
                    {
                      baseFaite = true;
                    }
                    if (!baseFaite)
                    {
                      if ((line[k] != '>')&&(line[k] != '<'))
                      {
                        //cout<<"bonjour je m'appelle test1a!"<<endl;
                        co.ajoutReglesAnciennes(line[k]);
                        //cout<<"line[k]= "<<line[k]<<"et pos= "<<pos<< "et k-pos="<<k-pos<<endl;
                      }
                      else
                      {
                        //cout<<"bonjour je m'appelle test1a!"<<endl;
                        if (line[k] == '<')
                        {
                          pos-=1;
                          //cout<<" pas augmente de 1 cas < : k-pos="<<k-pos<<endl;
                          //cout<<"bonjour je m'appelle test1aa!"<<endl;
                          co.setPosDuCaractere(k-pos);
                          fait =true;
                        }
                        if ((line[k] == '>')&&(fait==false))
                        {
                          //cout<<"cas > : k-pos="<<k-pos<<endl;
                          //cout<<"bonjour je m'appelle test1b!"<<endl;
                          co.setPosDuCaractere(k-pos);
                        }
                      }
                    }
                    else
                    {
                      if (line[k] != '=')
                      {
                        //cout<<" co ="<<co.getReglesNouvelles()<<endl;
                        //cout<<"bonjour je m'appelle test1c!"<<endl;
                        co.ajoutReglesNouvelles(line[k]);
                        //cout<<"ajout de k="<<k<<" correspondant a "<<line[k]<<endl;
                      }
                    }
                    k++;
                  }
                  //cout<<"bonjour je m'appelle test2!"<<endl;
                  rajoutContexte(co);
                  //cout<<"bonjour je m'appelle test3!"<<endl;
                  //contextes->push_back(co);
                }
                if(line[k] == '.')
                {
                  contexteFait = true;
                }
              }
              else
              {
                if(line[k] == '(')// cas probabiliste qui commence par une parenthese
                {
                  // cout << "cas probabiliste" << endl;
                  k++;
                  while(((line[k] >= '0')&&(line[k] <= '9')) || (line[k] == ','))
                  {
                    if(line[k] == ',')
                    {
                      k++;
                    }
                    probabilite = probabilite * 10 + line[k] - 48;// recuperation de la probabilite en entier
                    cpt++;
                    k++;
                  }
                  probabilite = puissanceMoins10(probabilite, cpt - 1);// probabilite en double
                  // cout << "La probabilite = " << probabilite << endl;
                  Probabilite p1(probabilite, "");// creation de probabilite
                  probabilite = 0;
                  cpt = 0;
                  rajoutMot(line[k + 1]);
                  //(*motsP).push_back(line[k + 1]);
                  // cout << "cas () rajout de " << line[k+1] << endl;
                  while(line[k] != '.')// pointeur dur la fin de la ligne
                  {
                    k++;
                  }
                  int deb = line.find('=') + 1;
                  p1.setString(line.substr(deb, k - deb));
                  rajoutProba(p1);
                  //(*reglesP).push_back(p1);
                }
                else
                {
                  if(line[k] == '=') // cas normal, non probabiliste
                  {
                    rajoutMot(line[0]);
                    //(*motsP).push_back(line[0]);
                    // cout << "cas = rajout de " << line[0] << endl;
                    b = true;
                  }
                  else
                  {
                    if(line[k] == '.')
                    {
                      if(b)
                      {
                        int beg = line.find('=') + 1;
                        Probabilite p1(1, line.substr(beg, k - beg));
                        rajoutProba(p1);
                        //(*reglesP).push_back(p1);
                      }
                    }
                    if(!premierAxiome)
                    {
                      premierAxiome = true;
                      while(line[k] != '.')// pointeur dur la fin de la ligne
                      {
                        k++;
                      }
                      // cout << "axiome de base = " << line.substr(0, k);
                      setAxiomeDeBase(line.substr(0, k));
                      //*axiomeDeBase = line.substr(0, k);
                      // cout << "la ligne oubliee selon 1 est" << line << endl;
                    }
                  }
                }
              }
            }
             //cout << "la ligne oubliee selon 2 est" << line << endl;
          }
        }
         //cout << "la ligne oubliee selon 3 est" << line << endl;
      }
       //cout << "la ligne oubliee selon  4 est" << line << endl;
    }
    //cout << "la ligne oubliee selon  5 est" << line << endl;
  }
   //cout << "fin lecture reglesF" << endl;
  file.close();  
  //cout << "le fichier s'est ferme avec succes" << endl;
}

string arbre::toString()
{
  ostringstream a;
  a<<" RacineX= "<<_ordonneeRacineX<<endl
  <<"RacineZ"<<_ordonneeRacineZ<<endl
  <<"nombre d'iterations :"<<  _nombreIterations<<endl
  <<"_angleXY : "<<_angleXY<<endl
  <<"_angleZ : "<<_angleZ <<endl
  <<"_poids : "<< _poids<<endl
  <<"_hauteur"<< _hauteur<<endl
  <<"etageF :"<<endl;
  
  for (int i=0; i<_etageF.size(); i++)
  {
    a<<_etageF[i]->getName()<<" ";
  }
  
  a<<endl<<" reglesP :"<<endl;
  for (unsigned int i=0; i<_reglesP.size(); i++)
  {
    a<<_reglesP[i].toString()<<" ";
  }

  a<<endl<<"_contextes :"<<endl;
  for (unsigned int i=0; i<_contextes.size(); i++)
  {
    a<<_contextes[i].toString()<<" ";
  }

  a<<endl<<"motsP"<<endl;
  for (unsigned int i=0; i<_motsP.size(); i++)
  {
    a<<_motsP[i]<<" ";
  }

  a<<endl<<"svg gravite :"<<endl;  
  for (unsigned int i=0; i<_svgGravite.size(); i++)
  {
    a<<_svgGravite[i]<<" ";
  }
  a<<endl<<"axiomeDeBase : "<<_axiomeDeBase<<endl;
  
  return a.str();
}

double arbre::puissanceMoins10(double x, int p)
{
  for(int i = 0; i < p; i++)
  {
    x = x * 0.1;
  }
  return x;
}



void arbre::createTreeRankByRankF()
{
  //cout << "Bienvenue dans le createTreeRankByRankF" << endl;
  ostringstream a;

  for(unsigned int j = 0; j < _reglesP.size(); j++)
  {
    cout << "j = " << j << " motsP = " << _motsP[j] << " -> " << _reglesP[j].getString()
         << "de probabilite" << _reglesP[j].getProbabilite() << endl;
  }
  srand(time(NULL));
  double r = rand()%(10) + 1;
  r = r/10;
  //cout << "la fonction random r = " << r << endl;
  double total = 0;
  vector<node*> etageSuivant;
  char *tmpTab = new char[2];
  // cout << "je suis ici" << endl;
  for(unsigned int i = 0; i < _etageF.size(); ++i)
  {
    //cout<<"Bonjour !! l'inclinaison de "<< _etageF.at(i)->getName()<<" est :"<<_etageF.at(i)->getInclinaisonXY()<<endl;
    char x = _etageF.at(i)->getName()[0];
    //cout <<endl<<endl<< "etape1 : x correspond a" << _etageF.at(i)->getName() << endl;
    if((x == '[') || (x == ']')
    || (x == '+') || (x == '-')
    || (x == '/') || (x == '\\')
    || (x == '~') || (x == '*'))
    {
      // cout << "cas4" << endl;
      // cout << endl << endl << " cas : etape2 avec pere=" << _etageF.at(i) << endl;
      tmpTab[0] = x;
      tmpTab[1] = '\0';
      a << x;
      node *enfant;
      //cout<<endl<<endl<<"test1 avec"<<_etageF.at(i)->getName()<<endl;
      if (_etageF.at(i)->getgravite())
      {
        //cout<<endl<<"l'arbre est sous le joug de la gravite"<<endl;
        enfant = new node(_etageF.at(i)->getPoids(),_hauteur, 180, _etageF.at(i)->getInclinaisonZ(), true, tmpTab, _etageF.at(i));
      }
      else
      {
        enfant = new node(_etageF.at(i)->getPoids(), _hauteur, _etageF.at(i)->getInclinaisonXY(), _etageF.at(i)->getInclinaisonZ(), false, tmpTab, _etageF.at(i));
      }
      etageSuivant.push_back(enfant);
    }
    else
    {
      int index = -1;
      for(unsigned int j = 0; j < _motsP.size(); ++j)
      {
        if(_motsP.at(j) == _etageF.at(i)->getName()[0])
        {
          index = j;
          break;
        }
      }
      if(index != -1)// dans ce cas, il n y a pas de regles correspondant
      {
        /*
        cout << "Non Trouve ! avec" << " motsP = " << _motsP.at(index) << " et "
            << _etageF.at(i)->getName()[0] << " ===> " << _reglesP.at(index).toString() << endl;
        */
        total = _reglesP.at(index).getProbabilite();
        int ctr = 0;
        // cout << " ici " << _reglesP.at(index).toString() << " r = " << r << "et total = " << total << endl;
        while((r > total) && (ctr < 10))
        {
          // cout << "etape5" << endl;
          ctr++;
          for(unsigned int j = index + 1; j < _motsP.size(); ++j)
          {
            if(_motsP.at(j) == _etageF.at(i)->getName()[0])
            {
              index = j;
              // cout << endl << "Dans ce cas :" << r << ">" << total;
              total += _reglesP.at(index).getProbabilite();
              // cout << " et total devient :" << total << "car on lui a rajoute" << _reglesP.at(index).getProbabilite() << endl;
              // cout << "le nouvel index devient :" << _reglesP.at(index).toString() << "r = " << r << "et total = " << total << endl;
              break;
            }
          }
        }
        if(ctr != 10)
        {
          //cout << "etape6" << endl;
          for(unsigned int j = 0; j < _reglesP.at(index).getString().size(); ++j)
          {
            tmpTab[0] = _reglesP.at(index).getString().at(j);
            //cout << " le truc bizarre devient :" << _reglesP.at(index).getString().at(j) << "venant de " << _reglesP.at(index).getString() << endl;
            tmpTab[1] = '\0';
            a << _reglesP.at(index).getString().at(j);

            node *enfant;
            //cout<<endl<<"test3 avec"<<_etageF.at(i)->getName()<<endl;
            if (_etageF.at(i)->getgravite())
            {
              //cout<<endl<<"l'arbre est sous le joug de la gravite"<<endl;
              enfant = new node(_poids, _hauteur, 180, _angleZ, true, tmpTab, _etageF.at(i));
            }
            else
            {
              enfant = new node(_poids, _hauteur,_angleXY, _angleZ, false, tmpTab, _etageF.at(i));
            }
            etageSuivant.push_back(enfant);
          }
        }
        // cout << "   ";
      }
      else
      {
        //cout << "etape7" << endl;
        tmpTab[0] = _etageF.at(i)->getName()[0];
        // cout << " le truc bizarre devient :" << _reglesP.at(index).getString().at(j) << "venant de " << _reglesP.at(index).getString() << endl;
        tmpTab[1] = '\0';
        a << _etageF.at(i)->getName()[0];

        node *enfant;
        //cout<<endl<<"test1 avec"<<_etageF.at(i)->getName()<<endl;

        if (_etageF.at(i)->getgravite())
        {
          //cout<<endl<<"l'arbre est sous le joug de la gravite"<<endl;
          enfant = new node(_etageF.at(i)->getPoids(), _hauteur, 180, _etageF.at(i)->getInclinaisonZ(), true,
                                tmpTab, _etageF.at(i)->getPere());
        }
        else
        {
          enfant = new node(_etageF.at(i)->getPoids(), _hauteur, _etageF.at(i)->getInclinaisonXY(), _etageF.at(i)->getInclinaisonZ(), false,
                                tmpTab, _etageF.at(i)->getPere());
        } 
        etageSuivant.push_back(enfant);
      }
    }
    r = rand()%(10) + 1;
    r = r/10;
  }
  // cout << endl;
  _etageF.clear();

  for(unsigned int i = 0; i < etageSuivant.size(); ++i)
  {
    _etageF.push_back(etageSuivant.at(i));
    //cout<<"etageSuivant i ="<<(etageSuivant.at(i));
  }
  /************Partie Contexte**************/
  //cout << " a = " << a.str() << endl;
  int cpt=a.str().length();
  string c;
  c=a.str();
  //cout<<"pour la regle :"<<_contextes[0].toString();
  while (cpt>=0)
  {
    rechercheContextes(&_etageF,c,cpt,&_contextes, _hauteur);
    cpt--;
  }
  cout << "apres les operations, on a : c = " << c << endl;

/************ Fin Partie Contexte**************/
  _svgGravite.clear();
  for(unsigned int i = 0; i < _etageF.size(); ++i)
  {
    /*
    cout<<"l'inclinaison de "<< _etageF.at(i)->getName()<<" est :"<<_etageF.at(i)->getInclinaisonXY()
    << "avec une gravite "<<_etageF.at(i)->getgravite()
    <<"et un pere"<<_etageF.at(i)->getPere()->getName()<<endl;
  */
    _svgGravite.push_back(_etageF.at(i)->getgravite());
    //cout<<_etageF.at(i)->getgravite()<<"rajoute"<<endl;
  }
  /*
  cout<<"c="<<c<<"avec svg =";
  for(unsigned int i = 0; i < _etageF.size(); ++i)
  {
    cout<<_svgGravite.at(i);
  }  
  cout<<endl;
*/
  preparationArbre(c);
  // cout << "au revoir de createTreeRankByRankF" << endl;
}

void arbre::preparationArbre(string a)
{
  //cout<<"entree dans prepration arbre avec a="<<a<<endl;  
  vector<node*> etageR; // etages dans la lecture du mot
  //cout << "entree dans preparationArbre avec angleXY=" <<_angleXY<<"et angleZ="<<_angleZ<< endl;
  int m = 0;
  int cpt = 0;
  while((a[m]) != '\0')
  {
    if(((a[m] >= 'A') && (a[m] <= 'Z'))
    || ((a[m] >= 'a') && (a[m] <= 'z')))
    {
      cpt++;
    }
    m++;
  }
  m = 0;
  char *tmp = new char[2];
  tmp[0] = 'R';
  tmp[1] = '\0';
  node* racineR = new node(NULL, 0, 0, 0, 90, 0, tmp, _poids, false);
  // cout << "inclinaisonXY racineR : " << racineR->getInclinaisonXY() << endl;
  etageR.push_back(racineR);
  node* pere = racineR;
  node* enfant;
  double inclinaisonXY = 0;
  double inclinaisonZ = 0;
  double modifPoids=0;
  // cout << "etape4 franchie" << endl;
  while((a[m]) != '\0')
  {
  // cout << "avec m = " << m << endl;
    if(((a[m] >= 'A') && (a[m] <= 'Z'))
    || ((a[m] >= 'a') && (a[m] <= 'z')))
    {
      //cout << " cas1 de prep :a[" << m << "] = " << a[m] << " en int " << (int)a[m] << endl;
      char tmpTab[2];
      tmpTab[0] = a[m];
      tmpTab[1] = '\0';
      if ((pere->getgravite())|| (_svgGravite.at(m)))
      {
        enfant = new node(_poids, _hauteur, 180, inclinaisonZ, true, tmpTab, pere );
      }
      else
      {
        enfant = new node(_poids, _hauteur, inclinaisonXY, inclinaisonZ, false, tmpTab, pere );
      }
      // cout << "nom de l'enfant" << tmpTab << "nom du pere : " << pere->getName() << endl;
      /*
      cout << " inclinaisonXY enfant " << m << " : " << enfant->getInclinaisonXY()
           << "avec pere d'une inclinaisonXY de " << pere->getInclinaisonXY() << " et a[m] = " << a[m] << endl;
      */
      //cout << endl << endl << "enfant =" << enfant->getName() << "pere=" << pere->getName() << endl;
      pere = enfant;
    }
    else
    {
      // cout<<"cas1"<<endl;
      if(a[m] == '[')
      {
        // cout << endl << endl << "2eme cas =" << pere->getName() << endl;
        // cout << "1er test inclinaisonZ = " << inclinaisonZ <<"angle Z="<<_angleZ<< endl;
        // cout << "Tandis que inclinaisonXY = " << inclinaisonXY <<"angle XY="<<_angleXY<< endl;
        m = arbrePere(m, a, pere, inclinaisonXY, inclinaisonZ, modifPoids);
      }
      if(a[m] == '+')
      {
        inclinaisonXY -= _angleXY;
        // cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
      }
      if(a[m] == '-')
      {
        inclinaisonXY += _angleXY;
        // cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
      }
      if(a[m] == '/')
      {
        inclinaisonZ += _angleZ;
        //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
      }
      if(a[m] == '\\')
      {
        inclinaisonZ -= _angleZ;
        //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
      }
      if(a[m] == '~')
      {
        modifPoids -= _poids;
        //cout<<"le poids devient :"<<modifPoids<<endl;
      }
      if(a[m] == '*')
      {
        modifPoids += _poids;
        //cout<<"le poids devient :"<<modifPoids<<endl;
      }
    }
    m++;
  }
  // cout << "main :x = " << racineR->getX() << " et y = " << racineR->getY() << endl;
  //contextesLies( racineR, contextes);

  affichageGraphique(racineR);
  exportObj(racineR);
  for (unsigned int i = 0; i < etageR.size(); ++i)
  {
    delete etageR.at(i);
  }
  delete tmp;
  // cout << "arbre prepare !" << endl;
}

int arbre::arbrePere(int m, string a, node* pere,  double inclinaisonXY, double inclinaisonZ, double modifPoids)
{
  //cout << "bienvenue dans arbre pere avec pere d'une inclinaisonZ de " << pere->getInclinaisonZ() << " et inclinaisonXY = " << inclinaisonXY << endl;
  m++;
  while((a[m]) != '\0')
  {
    //cout<<"cas2"<<endl;
    // cout << "avec m = " << m << endl;
    if(a[m] == ']')
    {
      // cout << "arret de arbrePere avec m = " << m << endl;
      return m;
    }
    if(a[m] == '[')
    {
      // cout << "dans ce cas inclinaisonXY = " << inclinaisonXY << endl;
      m = arbrePere(m, a, pere,  inclinaisonXY, inclinaisonZ, modifPoids);
      // cout << "retour de arbrePere avec m = " << m << endl;
    }
    if(a[m] == '+')
    {
      inclinaisonXY -= _angleXY;
      // cout << "apres un +, l'inclinaisonXY devient" << inclinaisonXY << endl;
    }
    if(a[m] == '-')
    {
      inclinaisonXY += _angleXY;
      // cout << "apres un -, l'inclinaisonXY devient" << inclinaisonXY << endl;
    }
    if(a[m] == '/')
    {
      inclinaisonZ += _angleZ;
      //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
    }
    if(a[m] == '\\')//utilisation de l'ascii car '\' fait des choses bizarres
    {
      //cout <<"avec a[m]="<<a[m]<< "l'inclinaisonZ Ã©tait :" << inclinaisonZ;
      inclinaisonZ -= _angleZ;
      //cout << "et  devient :" << inclinaisonZ << endl;
    }
    if(a[m] == '~')
    {
      modifPoids -= _poids;
      //cout<<"le poids devient :"<<modifPoids<<endl;
    }
    if(a[m] == '*')
    {
      modifPoids += _poids;
      //cout<<"le poids devient :"<<modifPoids<<endl;
    }

    if(((a[m] >= 'A') && (a[m] <= 'Z'))
    || ((a[m] >= 'a') && (a[m] <= 'z')))
    {
      char tmpTab[2];
      tmpTab[0] = a[m];
      tmpTab[1] = '\0';
      node *enfant;
      if ((pere->getgravite())|| (_svgGravite.at(m)))
      {
          enfant = new node(_poids, _hauteur, 180, inclinaisonZ,true, tmpTab, pere);  
      }
      else 
      {
        enfant = new node(_poids, _hauteur, inclinaisonXY, inclinaisonZ,false, tmpTab, pere);
      }
      /*
      cout << " inclinaisonXY enfant " << m << " : " << enfant->getInclinaisonXY()
           << "avec pere d'une inclinaisonXY de " << pere->getInclinaisonXY() << " et a[m] = " << a[m] << endl;
      */
      pere = enfant;
    }
    m++;
  }
  // cout << "cas final" << endl;
  return m;// ne sert jamais
}


void arbre::premierAxiome()
{
  //cout<<"bienvenue dans premier axiome"<<endl;
  char motRacineF;
  node* racineF;
  vector<bool> svgGravite;
  for (unsigned int i=0; i < _axiomeDeBase.size(); i++)
  {
    svgGravite.push_back(false);
  }
  // node *racine;
  if(_axiomeDeBase.size() == 1)
  {

    motRacineF = _axiomeDeBase[0];
    char *tmpTabF = new char[2];
    tmpTabF[0] = motRacineF;
    tmpTabF[1] = '\0';
    //cout << "mot tmp = " << tmpTabF << endl;
    racineF = new node(NULL, 0, 0, 0, 0, 0, tmpTabF, _poids, false);//sert actuellement a rien
    _etageF.push_back(racineF);
    delete tmpTabF;
  }
  else
  {
    motRacineF = 'R';
    char *tmpTabF = new char[2];
    tmpTabF[0] = motRacineF;
    tmpTabF[1] = '\0';
    // cout << "mot tmp = " << tmpTabF << endl;
    racineF = new node(NULL, 0, 0, 0, 0, 0, tmpTabF, _poids, false);
    _etageF.push_back(racineF);
    if(_axiomeDeBase.size() != 1)
    {
      // cas ou l axiome de base est multiple, on cree ici le premier etage
      _etageF.pop_back();
      char* nom = new char[_axiomeDeBase.size()];
      node* pere = racineF;
      node* enfant;
      int m = 0;
      int n = 0;
      double inclinaisonXY = 0;
      double inclinaisonZ = 0;
      double modifPoids= 0;
      while((unsigned)n < _axiomeDeBase.size())
      {
        nom[m] = _axiomeDeBase[n];
        //cout << "nom[m] = " << nom[m] << endl;
        if(((nom[m] >= 'A') && (nom[m] <= 'Z'))
        || ((nom[m] >= 'a') && (nom[m] <= 'z')))
        {
          nom[m+1] = '\0'; m = -1;
          
          enfant = new node(_poids, _hauteur, inclinaisonXY, inclinaisonZ, false, nom, pere );
          
          //cout << "nom de l'enfant" << nom << "nom du pere : " << pere->getName() << endl;
          pere = enfant;
          _etageF.push_back(enfant);
        }
        else {
          //cout<<"cas3"<<endl;
          if(nom[m] == '[')
          {
            // cout << "1er test inclinaisonXY  = " << inclinaisonXY << endl;
            m = arbrePere(m, nom, pere,  inclinaisonXY, inclinaisonZ, modifPoids);
          }
          if(nom[m] == '+')
          {
            inclinaisonXY-= _angleXY;
            // cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
          }
          if(nom[m] == '-')
          {
            inclinaisonXY += _angleXY;
            //cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
          }
          if(nom[m] == '/')
          {
            inclinaisonZ += _angleZ;
            //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
          }
          if(nom[m] == '\\')
          {
            inclinaisonZ -= _angleZ;
            //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
          }
          if(nom[m] == '~')
          {
            modifPoids -= _poids;
            //cout<<"le poids devient :"<<modifPoids<<endl;
          }
          if(nom[m] == '*')
          {
            modifPoids += _poids;
            //cout<<"le poids devient :"<<modifPoids<<endl;
          }
          nom[m+1] = '\0';
          m = -1;
          enfant = new node(_poids, _hauteur, inclinaisonXY, inclinaisonZ, false, nom, pere );
          //cout << "nom de l'enfant" << nom << "nom du pere : " << pere->getName() << endl;
          pere = enfant;
          _etageF.push_back(enfant);
        }
        m++;
        n++;
      }
      nom[_axiomeDeBase.size()+1] = '\0';
      //cout << "le nom est :" << nom << endl;
      // racine = new node(_hauteur, _angleXY, _angleZ, true, nom, racineF);
      //etageF.push_back(racine);
      delete tmpTabF;
      delete nom;
    }
  }
  /*
  cout << "etageF = " << endl;
  for(unsigned int i = 0; i<etageF.size();i++)
  {
    cout << etageF.at(i)->getName() << " x = " << etageF.at(i)->getX() << " y = " << etageF.at(i)->getY() << endl;
  }
  */
  // cout << " rajout de " << _axiomeDeBase[0];
  // affichageGraphique(etageF.at(0));

}