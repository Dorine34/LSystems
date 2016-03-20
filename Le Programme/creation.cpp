#include "creation.h"


/**********
partie avec les contextes est a verifier
surtour qu'ils n heritent pas des enfants du pere
**************/
double puissanceMoins10(double x, int p)
{
  for(int i = 0; i < p; i++)
  {
    x = x * 0.1;
  }
  return x;
}
/*********Permet de sauvegarder les regles**********/
/**
reglesP : les regles de construction
angleXY : l'angleXY de rotation
axiome de base : le premier axiome
**/
// permet de faciliter l acces aux regles
void lectureReglesF(char *filenameF, vector<char> *motsP, vector<Probabilite> *reglesP,  vector<Contexte> *contextes, double *angleXY, double *angleZ, double *poids, double *hauteur, string *axiomeDeBase)
{
  // cout << "bienvene dans lectureReglesF" << endl;
  int cpt = 0;
  *angleXY = 0;
  *axiomeDeBase = "";
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
      // cout << " au debut line [k] = " << line[k] << endl;
      if(!angleXYFait)
      {
        // cout << "line[" << k << "]=" << line[k] << endl;
        if((k >= 8) && (line[k] != '.'))// recupere la premiere donnee correspondant Ã  l'angleXYXY
        {
          *angleXY = (*angleXY) * 10 + line[k] - 48;
        }
        if(line[k] == '.')
        {
          angleXYFait = true;
          cout << "angleXY=" << *angleXY << endl;
        }
      }
      else
      {
        if(!angleZFait)// recupere la premiere donnee correspondant Ã  l'angleXYXY
        {
          if((k >= 7) && (line[k] != '.'))// recupere la premiere donnee correspondant Ã  l'angleXYXY
            {
              *angleZ = (*angleZ) * 10 + line[k] - 48;
            }
          if(line[k] == '.')
          {
            angleZFait = true;
            cout << "angleZ=" << *angleZ << endl;
          }
        }
        else
        {
          if(!poidsArbreFait)
          {
          // cout << "line[" << k << "]=" << line[k] << endl;
            if((k>=8)&&(line[k] != '.'))// recupere la premiere donnee correspondant Ã  l'angleXYXY
            {
              *poids = (*poids) * 10 + line[k] - 48;
            }
            if(line[k] == '.')
            {
              poidsArbreFait = true;
              cout << "poids=" << *poids << endl;
            }
          }
          else
          {
            if(!longueurBrancheFait)
              {
                // cout << "line[" << k << "]=" << line[k] << endl;
                if((k >= 9) && (line[k] != '.'))// recupere la premiere donnee correspondant Ã  l'angleXYXY
                {
                  *hauteur = (*hauteur) * 10 + line[k] - 48;
                }
                if(line[k] == '.')
                {
                  longueurBrancheFait = true;
                  // cout << "hauteur=" << *hauteur << endl;
                }
              }
            else
            {
              if(!contexteFait)
              {
                if ((k >= 9) && (line[k] != '.'))
                {
                  Contexte co ("",0,"");
                  bool baseFaite=false;
                  bool fait =false;
                  int pos=k;
                  while ((line[k] != ',') && (line[k] != '.'))
                  {
                    //cout<<"line[k]= "<<line[k]<<"et pos= "<<pos<< "et k-pos="<<k-pos<<endl;
                    if (line[k] == '=')
                    {
                      baseFaite = true;
                    }
                    if (!baseFaite)
                    {
                      if ((line[k] != '>')&&(line[k] != '<'))
                      {
                        co.ajoutReglesAnciennes(line[k]);
                        //cout<<"line[k]= "<<line[k]<<"et pos= "<<pos<< "et k-pos="<<k-pos<<endl;
                      }
                      else
                      {
                        if (line[k] == '<')
                        {
                          pos-=1;
                          //cout<<" pas augmente de 1 cas < : k-pos="<<k-pos<<endl;
                          co.setPosDuCaractere(k-pos);
                          fait =true;
                        }
                        if ((line[k] == '>')&&(fait==false))
                        {
                          //cout<<"cas > : k-pos="<<k-pos<<endl;
                          co.setPosDuCaractere(k-pos);
                        }
                      }
                    }
                    else
                    {
                      if (line[k] != '=')
                      {
                        //cout<<" co ="<<co.getReglesNouvelles()<<endl;
                        co.ajoutReglesNouvelles(line[k]);
                        //cout<<"ajout de k="<<k<<" correspondant a "<<line[k]<<endl;
                      }
                    }
                    k++;
                  }
                  contextes->push_back(co);
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
                  (*motsP).push_back(line[k + 1]);
                  // cout << "cas () rajout de " << line[k+1] << endl;
                  while(line[k] != '.')// pointeur dur la fin de la ligne
                  {
                    k++;
                  }
                  int deb = line.find('=') + 1;
                  p1.setString(line.substr(deb, k - deb));
                  (*reglesP).push_back(p1);
                }
                else
                {
                  if(line[k] == '=') // cas normal, non probabiliste
                  {
                    (*motsP).push_back(line[0]);
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
                        (*reglesP).push_back(p1);
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
                      *axiomeDeBase = line.substr(0, k);
                      // cout << "la ligne oubliee selon 1 est" << line << endl;
                    }
                  }
                }
              }
            }
            // cout << "la ligne oubliee selon 2 est" << line << endl;
          }
        }
        // cout << "la ligne oubliee selon 3 est" << line << endl;
      }
      // cout << "la ligne oubliee selon  4 est" << line << endl;
    }
  }
  // cout << "fin lecture reglesF" << endl;
  file.close();
}


void createTreeRankByRankF(vector<node*> *etageF, double angleXY, double angleZ, double hauteur,
                                  vector<char> *motsP, vector<Probabilite> *reglesP, double poids,
                                   vector<Contexte> *contextes)
{
  cout << "Bienvenue dans le createTreeRankByRankF" << endl;
  ostringstream a;

  for(unsigned int j = 0; j < (*reglesP).size(); j++)
  {
    cout << "j = " << j << " motsP = " << (*motsP)[j] << " -> " << (*reglesP)[j].getString()
         << "de probabilite" << (*reglesP)[j].getProbabilite() << endl;
  }
  srand(time(NULL));
  double r = rand()%(10) + 1;
  r = r/10;
  //cout << "la fonction random r = " << r << endl;
  double total = 0;
  vector<node*> etageSuivant;
  char *tmpTab = new char[2];
  // cout << "je suis ici" << endl;
  for(unsigned int i = 0; i < (*etageF).size(); ++i)
  {
    char x = (*etageF).at(i)->getName()[0];
    //cout <<endl<<endl<< "etape1 : x correspond a" << (*etageF).at(i)->getName() << endl;
    if((x == '[') || (x == ']')
    || (x == '+') || (x == '-')
    || (x == '/') || (x == '\\'))
    {
      // cout << "cas4" << endl;
      // cout << endl << endl << " cas : etape2 avec pere=" << (*etageF).at(i) << endl;
      tmpTab[0] = x;
      tmpTab[1] = '\0';
      a << x;
      node *enfant = new node(hauteur, (*etageF).at(i)->getInclinaisonXY(), (*etageF).at(i)->getInclinaisonZ(), true, tmpTab, (*etageF).at(i));
      etageSuivant.push_back(enfant);
    }
    else
    {
      // cout << "etape2a" << endl;
      int index = -1;
      for(unsigned int j = 0; j < (*motsP).size(); ++j)
      {
        // cout << "etape3" << endl;
        // cout << (*motsP).at(j) << " correspond a  " << (*etageF).at(i)->getName()[0] << endl;
        if((*motsP).at(j) == (*etageF).at(i)->getName()[0])
        {
          index = j;
          /*
          cout << "Trouve ! avec j = " << j << " motsP = " << (*motsP).at(j) << " et "
              << (*etageF).at(i)->getName()[0] << " ===> " << (*reglesP).at(index).toString() << endl;
          */
          break;
        }
      }
      if(index != -1)// dans ce cas, il n y a pas de regles correspondant
      {
        /*
        cout << "Non Trouve ! avec" << " motsP = " << (*motsP).at(index) << " et "
            << (*etageF).at(i)->getName()[0] << " ===> " << (*reglesP).at(index).toString() << endl;
        */
        total = (*reglesP).at(index).getProbabilite();
        int ctr = 0;
        // cout << " ici " << (*reglesP).at(index).toString() << " r = " << r << "et total = " << total << endl;
        while((r > total) && (ctr < 10))
        {
          // cout << "etape5" << endl;
          ctr++;
          for(unsigned int j = index + 1; j < (*motsP).size(); ++j)
          {
            if((*motsP).at(j) == (*etageF).at(i)->getName()[0])
            {
              index = j;
              // cout << endl << "Dans ce cas :" << r << ">" << total;
              total += (*reglesP).at(index).getProbabilite();
              // cout << " et total devient :" << total << "car on lui a rajoute" << (*reglesP).at(index).getProbabilite() << endl;
              // cout << "le nouvel index devient :" << (*reglesP).at(index).toString() << "r = " << r << "et total = " << total << endl;
              break;
            }
          }
        }
        if(ctr != 10)
        {
          //cout << "etape6" << endl;
          for(unsigned int j = 0; j < (*reglesP).at(index).getString().size(); ++j)
          {
            tmpTab[0] = (*reglesP).at(index).getString().at(j);
            //cout << " le truc bizarre devient :" << (*reglesP).at(index).getString().at(j) << "venant de " << (*reglesP).at(index).getString() << endl;
            tmpTab[1] = '\0';
            a << (*reglesP).at(index).getString().at(j);
            node *enfant = new node(hauteur,angleXY, angleZ, true, tmpTab, (*etageF).at(i));
            etageSuivant.push_back(enfant);
          }
        }
        // cout << "   ";
      }
      else
      {
        //cout << "etape7" << endl;
        tmpTab[0] = (*etageF).at(i)->getName()[0];
        // cout << " le truc bizarre devient :" << (*reglesP).at(index).getString().at(j) << "venant de " << (*reglesP).at(index).getString() << endl;
        tmpTab[1] = '\0';
        a << (*etageF).at(i)->getName()[0];
        node *enfant = new node(hauteur, (*etageF).at(i)->getInclinaisonXY(), (*etageF).at(i)->getInclinaisonZ(), true,
                                tmpTab, (*etageF).at(i)->getPere());
        etageSuivant.push_back(enfant);
      }
    }
    r = rand()%(10) + 1;
    r = r/10;
  }
  // cout << endl;
  etageF->clear();

  for(unsigned int i = 0; i < etageSuivant.size(); ++i)
  {
    etageF->push_back(etageSuivant.at(i));
    //cout<<"etageSuivant i ="<<(etageSuivant.at(i));
  }
  /************Partie Contexte**************/
  //cout << " a = " << a.str() << endl;
  int cpt=a.str().length();
  string c;
  c=a.str();
  cout<<"pour la regle :"<<(*contextes)[0].toString();
  while (cpt>=0)
  {
    rechercheContextes(etageF,c,cpt,contextes, hauteur);
    cpt--;
  }
  //cout << "apres les operations, on a : c = " << c << endl;





/************ Fin Partie Contexte**************/

  PreparationArbre(c, angleXY, angleZ, hauteur, poids, contextes);
  // cout << "au revoir de createTreeRankByRankF" << endl;
}

void insereRN(string &a, int base, vector<Contexte> * contextes, int i)
{
  //cout <<"bienvenue dans aInserer"<<endl;
  string Ainserer=(*contextes)[i].getReglesNouvelles();
  //cout<< "a inserer="<<Ainserer << endl;
  ostringstream o;
  for (unsigned int i=0; i<base; i++)
  {
    o<<a[i];
  }
  for (unsigned int i=0; i<Ainserer.length(); i++)
  {
    o<<Ainserer[i];
  }
  
  for (unsigned int i=base+1; i<a.length(); i++)
  {
    o<<a[i];
  }
  a=o.str();

}

void rechercheContextes(vector<node*> *etageF,string& a, int cpt, vector<Contexte> * contextes, int hauteur){
  //cout<< "Bienvenue dans rechercheContextes :"<<endl;
  char *tmpTab = new char[2];
  int j=1;
  int base=1;
  for (unsigned int i=0; i<contextes->size();i++)
  {
    if (((*contextes)[i].getReglesAnciennes()[0])==a[cpt])
    {
      //cout<<endl<<"Bravo, les premiers elements concordent !"<<endl;
      if (((*contextes)[i].getReglesAnciennes()).length()==1)
      {
        //cout<<"cas où regles anciennes ==1";
        //a.replace(base,(*contextes)[i].getReglesNouvelles().length(),(*contextes)[i].getReglesNouvelles());        
        //cout<<"Dans contextes :(*contextes)[i].getPosDuCaractere()+cpt-2="<<(*contextes)[i].getPosDuCaractere()+cpt-2<<endl;
        insereRN(a,base,contextes,i);
      } 
      else
      {
        cpt++;
        //base=cpt;
        //cout mettre un while qd le remplacement sera fait
        while (verificationContexteString (a,cpt, contextes, i, j, &base))
        {
          //cout<<endl<<"YOUPI,cpt="<<cpt<<" et base="<< base<<endl;
          //cout<<"Remplacement de"<<a[base]<< " au niveau :"<<base<<endl;
          //a.replace(base,(*contextes)[i].getReglesNouvelles().length(),(*contextes)[i].getReglesNouvelles());        
          insereRN(a,base,contextes,i);  
          //cout<<"a apres remplacement"<<a<<" et base2="<<base<<endl;
          /*
          cout<<"cas1: base="<<base<<endl;
          cout<<"etageF :"<<(*etageF)[base]->getName()<<endl;
          */

          /**Remplacement dans etageF**/
          vector<node*> etageSuivant;
          int k=0;
          while(k<base)
          {
            //cout<<(*etageF)[k]->getName()<<" ";
            etageSuivant.push_back((*etageF)[k]);
            k++;
          }
          node* enfant;
          node*test;
          while (k<(*contextes)[i].getReglesNouvelles().length()+base)
          {
          
            tmpTab[0] = a[k] ;
            tmpTab[1] = '\0';
            enfant = new node(hauteur, (*etageF)[0]->getInclinaisonXY(), (*etageF)[0]->getInclinaisonZ(), true,tmpTab ,test);  
            //cout<<(enfant)->getName()<<" ";
            etageSuivant.push_back(enfant);
            k++;
          }
          
          while (k<(*contextes)[i].getReglesNouvelles().length()+(*etageF).size()-1)
          {
            //cout<<(*etageF)[k-(*contextes)[i].getReglesNouvelles().length()+1]->getName()<<" ";
            etageSuivant.push_back((*etageF)[k-(*contextes)[i].getReglesNouvelles().length()+1]);
            k++;
          }
          // cout << endl;
          etageF->clear();
          etageF->push_back(etageSuivant[0]);
          for(unsigned int i = 1; i < etageSuivant.size(); ++i)
          {
            etageSuivant[i]->setPere(etageSuivant[i-1]);
            etageF->push_back(etageSuivant.at(i));
          }          
          /***/
          base=1;
        }
      }
    }
  }
}

bool verificationContexteString (string &a,int cpt, vector<Contexte> * contextes, int i, int j, int *base)
{
  //cout<<"Bienvenue dans verificationContexteString avec "<<a[cpt]<<"base="<<(*base)<< ", cpt="<< cpt<< "et RA= "<< (*contextes)[i].getReglesAnciennes()[j]<< "et j="<< j<<endl;
  //(*base)=j;
  while (cpt<a.length())
  {
    if (j==(*contextes)[i].getReglesAnciennes().length())
    {
      return true;
    }
    if(((a[cpt] >= 'A') && (a[cpt] <= 'Z'))
      || ((a[cpt] >= 'a') && (a[cpt] <= 'z')))
    {
      //cout<<"C'est une lettre ! a[cpt]= "<<a[cpt]<<"avec cpt="<<cpt<<endl;
      if ( (a[cpt]==(*contextes)[i].getReglesAnciennes()[j]))
      {
        //cout<<"cpt="<< cpt<<", base="<<(*base)<<"j="<<j<<" et position du caractere="<<(*contextes)[i].getPosDuCaractere()<<endl;
        
        if ((*contextes)[i].getPosDuCaractere()>(*base))
        {
          //cout<<endl<<"base  ("<<(*base)<<"<"<<(*contextes)[i].getPosDuCaractere()<<"donc base augmente de 1"<<endl;
          (*base)++;
        }
        if ((*contextes)[i].getPosDuCaractere()==(*base))
        {
          //cout<<"base a le bon nombre de lettre donc base= cpt)"<<cpt<<endl;;
          (*base)=cpt;
        }
      
        //cout<<"c'est la même lettre !"<<endl;
        j++;
        cpt++;
      }
      else
      {
        //cout<<"c'est faux avec "<<a[cpt]<<endl;
        return false;
      }
    }
    else
    {
      if (a[cpt]=='[')
      {
        cpt++;
        //cout<<"c'est un [, on boucle avec cpt="<<cpt<< " i= "<<i<<"j="<<j<<endl;
        if( verificationContexteString(a,cpt, contextes,i,j, base))
        {
          //cout<<endl<<"YOUPI ca marche ! (cpt="<<cpt<<" et base="<<(*base)<<endl;
          return true; 
        }
        else
        {
          int nbParOuvrante=1;
          int nbParFermante=0;
          while (nbParFermante != nbParOuvrante)
          {
            if (a[cpt]==']')
            {
              nbParFermante++;
            }
            if (a[cpt]=='[')
            {
              nbParOuvrante++;
            }
            cpt++;
          }
        }
      }
      else
      {
        //cout<<"on est ici 5"<<endl;
        if (a[cpt]==']')
        {
          //cout<<"on est ici 6"<<endl;
          return false;
        }
        else
        {
          //cout<<"Hello : on a a[cpt]="<<a[cpt]<<"cpt="<<cpt+1<<"et "<<1<<endl;
          cpt++;
        }
        //cout<<"on est ici 1"<<endl;
      }
      //cout<<"on est ici 2"<<endl;
    }
    //cout<<"on est ici 3"<<endl;
  }
  return false;
}

/**************************
* preparationArbre permet de mettre les elements en place pour la creation de l'arbre
*le principe consiste a assembler les bouts de mots pour obtenir le mot final
*
*m permet de se situer dans la lecture du mot
*etageR correspond a un mot
*on sauvegarde chaque etage de creaton du mot afin de pouvoir s'en servir si on veut creer un etage superieur
*
*************/

// a represente une ligne de caracteres
void PreparationArbre(string a, double angleXY, double angleZ, double hauteur, double poids, vector<Contexte> *contextes)
{
  cout<<"entree dans prepration arbre avec a="<<a<<endl;  
  vector<node*> etageR; // etages dans la lecture du mot
  //cout << "entree dans preparationArbre avec angleXY=" <<angleXY<<"et angleZ="<<angleZ<< endl;
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
  node* racineR = new node(NULL, 0, 0, 0, 90, 0, tmp, poids);
  // cout << "inclinaisonXY racineR : " << racineR->getInclinaisonXY() << endl;
  etageR.push_back(racineR);
  node* pere = racineR;
  node* enfant;
  double inclinaisonXY = 0;
  double inclinaisonZ = 0;
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
      enfant = new node(hauteur, inclinaisonXY, inclinaisonZ, true, tmpTab, pere );
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
        // cout << "1er test inclinaisonZ = " << inclinaisonZ <<"angle Z="<<angleZ<< endl;
        // cout << "Tandis que inclinaisonXY = " << inclinaisonXY <<"angle XY="<<angleXY<< endl;
        m = arbrePere(m, a, pere, angleXY, inclinaisonXY, angleZ, inclinaisonZ, hauteur);
      }
      if(a[m] == '+')
      {
        inclinaisonXY -= angleXY;
        // cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
      }
      if(a[m] == '-')
      {
        inclinaisonXY += angleXY;
        // cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
      }
      if(a[m] == '/')
      {
        inclinaisonZ += angleZ;
        //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
      }
      if(a[m] == '\\')
      {
        inclinaisonZ -= angleZ;
        //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
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


/**********************
*arbre pere permet de creer l'arbre a partie d'un mot
*chaque noeud de l'arbre a des caracteristiques spÃ©cifiquÃ©s hÃ©ritÃ©es du mot
*
***********/
//dans les cas des []
int arbrePere(int m, string a, node* pere, double angleXY, double inclinaisonXY, double angleZ, double inclinaisonZ, double hauteur)
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
      m = arbrePere(m, a, pere, angleXY, inclinaisonXY, angleZ, inclinaisonZ, hauteur);
      // cout << "retour de arbrePere avec m = " << m << endl;
    }
    if(a[m] == '+')
    {
      inclinaisonXY -= angleXY;
      // cout << "apres un +, l'inclinaisonXY devient" << inclinaisonXY << endl;
    }
    if(a[m] == '-')
    {
      inclinaisonXY += angleXY;
      // cout << "apres un -, l'inclinaisonXY devient" << inclinaisonXY << endl;
    }
    if(a[m] == '/')
    {
      inclinaisonZ += angleZ;
      //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
    }
    if(a[m] == '\\')//utilisation de l'ascii car '\' fait des choses bizarres
    {
      //cout <<"avec a[m]="<<a[m]<< "l'inclinaisonZ Ã©tait :" << inclinaisonZ;
      inclinaisonZ -= angleZ;
      //cout << "et  devient :" << inclinaisonZ << endl;
    }

    if(((a[m] >= 'A') && (a[m] <= 'Z'))
    || ((a[m] >= 'a') && (a[m] <= 'z')))
    {
      char tmpTab[2];
      tmpTab[0] = a[m];
      tmpTab[1] = '\0';
      node *enfant = new node(hauteur, inclinaisonXY, inclinaisonZ, true, tmpTab, pere);
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
/******
Mais a quoi sert premierAxiome ?
lors des premiers axiomes multiples
****/
void premierAxiome(string *axiomeDeBase, double* poids, double* hauteur, double* angleXY, double* angleZ, vector<node*>*etageF)
{
  char motRacineF;
  node* racineF;
  // node *racine;
  if(axiomeDeBase->size() == 1)
  {
    motRacineF = (*axiomeDeBase)[0];
    char *tmpTabF = new char[2];
    tmpTabF[0] = motRacineF;
    tmpTabF[1] = '\0';
    //cout << "mot tmp = " << tmpTabF << endl;
    racineF = new node(NULL, 0, 0, 0, 0, 0, tmpTabF, *poids);//sert actuellement a rien
    etageF->push_back(racineF);
    delete tmpTabF;
  }
  else
  {
    motRacineF = 'R';
    char *tmpTabF = new char[2];
    tmpTabF[0] = motRacineF;
    tmpTabF[1] = '\0';
    // cout << "mot tmp = " << tmpTabF << endl;
    racineF = new node(NULL, 0, 0, 0, 0, 0, tmpTabF, *poids);
    etageF->push_back(racineF);
    if(axiomeDeBase->size() != 1)
    {
      // cas ou l axiome de base est multiple, on cree ici le premier etage
      etageF->pop_back();
      char* nom = new char[axiomeDeBase->size()];
      node* pere = racineF;
      node* enfant;
      int m = 0;
      int n = 0;
      double inclinaisonXY = 0;
      double inclinaisonZ = 0;
      while((unsigned)n < axiomeDeBase->size())
      {
        nom[m] = (*axiomeDeBase)[n];
        //cout << "nom[m] = " << nom[m] << endl;
        if(((nom[m] >= 'A') && (nom[m] <= 'Z'))
        || ((nom[m] >= 'a') && (nom[m] <= 'z')))
        {
          nom[m+1] = '\0'; m = -1;

          enfant = new node(*hauteur, inclinaisonXY, inclinaisonZ, true, nom, pere );
          //cout << "nom de l'enfant" << nom << "nom du pere : " << pere->getName() << endl;
          pere = enfant;
          etageF->push_back(enfant);
        }
        else {
          //cout<<"cas3"<<endl;
          if(nom[m] == '[')
          {
            // cout << "1er test inclinaisonXY  = " << inclinaisonXY << endl;
            m = arbrePere(*hauteur, nom, pere, *angleXY, inclinaisonXY, *angleZ, inclinaisonZ, *poids);
          }
          if(nom[m] == '+')
          {
            inclinaisonXY-= *angleXY;
            // cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
          }
          if(nom[m] == '-')
          {
            inclinaisonXY += *angleXY;
            //cout << "l'inclinaisonXY devient :" << inclinaisonXY << endl;
          }
          if(nom[m] == '/')
          {
            inclinaisonZ += *angleZ;
            //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
          }
          if(nom[m] == '\\')
          {
            inclinaisonZ -= *angleZ;
            //cout << "l'inclinaisonZ devient :" << inclinaisonZ << endl;
          }
          nom[m+1] = '\0';
          m = -1;
          enfant = new node(*hauteur, inclinaisonXY, inclinaisonZ, true, nom, pere );
          //cout << "nom de l'enfant" << nom << "nom du pere : " << pere->getName() << endl;
          pere = enfant;
          etageF->push_back(enfant);
        }
        m++;
        n++;
      }
      nom[axiomeDeBase->size()+1] = '\0';
      //cout << "le nom est :" << nom << endl;
      // racine = new node(*hauteur, *angleXY, *angleZ, true, nom, racineF);
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
  // cout << " rajout de " << axiomeDeBase[0];
  // affichageGraphique(etageF.at(0));

}