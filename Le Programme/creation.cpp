#include "creation.h"
/*************************/
/* probleme arret non respecter
/*
/**************************/

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
void lectureReglesF(char *filenameF, vector<char> *motsP, vector<Probabilite> *reglesP, double *angleXY, double *angleZ, string *axiomeDeBase)
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
  bool angleXYfait = false;
  while (getline(file, line))
  {
    b = false;
    for(unsigned int k = 0; k < line.size(); ++k)
    {
      // cout << " au debut line [k] = " << line[k] << endl;
      if(!angleXYfait)
      {
        if((line[k] >= '0') && (line[k] <= '9'))// recupere la premiere donnee correspondant à l'angleXYXY
        {
          *angleXY = (*angleXY) * 10 + line[k] - 48;
        }
        if(line[k] == ' ')
        {
          angleXYfait = true;
        }
      }
      else
      {
        if((line[k] >= '0')&&(line[k] <= '9'))// recupere la premiere donnee correspondant à l'angleXYXY
        {
          *angleZ = (*angleZ) * 10 + line[k] - 48;
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
            while (line[k] != '.') // pointeur dur la fin de la ligne
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
                while (line[k] != '.')// pointeur dur la fin de la ligne
                {
                  k++;
                }
                // cout << "axiome de base = " << line.substr(0, k);
                *axiomeDeBase = line.substr(0, k);
                // cout << "la ligne oubliee selon 1 est" << line << endl;
              }
            }
          }
          // cout << "la ligne oubliee selon 2 est" << line << endl;
        }
        // cout << "la ligne oubliee selon 3 est" << line << endl;
      }
      // cout << "la ligne oubliee selon  4 est" << line << endl;
    }
  }
  // cout << "fin lecture reglesF" << endl;
  file.close();
}


void createTreeRankByRankF(vector<node*> *etageF, double angleXY, double angleZ, vector<char> *motsP, vector<Probabilite> *reglesP)
{
  cout << "bienvenue dans le createTreeRankByRankF" << endl;
  ostringstream a;
  /*
  for(int j = 0; j < (*reglesP).size(); j++)
  {
    cout << "j = " << j << " motsP = " << (*motsP)[j] << " -> " << (*reglesP)[j].getString()
         << "de probabilite" << (*reglesP)[j].getProbabilite() << endl;
  }
*/
  srand(time(NULL));
  double r = rand()%(10) + 1;
  r = r/10;
  // cout << "la fonction random r = " << r << endl;
  double total = 0;

  vector<node*> etageSuivant;
  char *tmpTab = new char[2];

  for(int i = 0; i < (*etageF).size(); ++i)
  {
    char x = (*etageF).at(i)->getName()[0];

    // cout << "etape1 : x correspond a" << (*etageF).at(i)->getName() << endl;
    if((x == '[')||(x == ']')||(x == '+')||(x == '-'))
    {
      // cout << "etape2" << endl;
      tmpTab[0] = x;
      tmpTab[1] = '\0';
      a << x;
      node *enfant = new node(10, 60, 60, false, tmpTab, (*etageF).at(i));
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
        while ((r > total)&&(ctr < 10))
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
          // cout << "etape6" << endl;
          for(unsigned int j = 0; j < (*reglesP).at(index).getString().size(); ++j)
          {
            tmpTab[0] = (*reglesP).at(index).getString().at(j);
            // cout << " le truc bizarre devient :" << (*reglesP).at(index).getString().at(j) << "venant de " << (*reglesP).at(index).getString() << endl;
            tmpTab[1] = '\0';
            a << (*reglesP).at(index).getString().at(j);
            node *enfant = new node(40, (*reglesP).at(index).getString().at(j) == 'a'? 40 : 60, 60,
                                    !((*reglesP).at(index).getString().at(j) == 'a'), tmpTab, (*etageF).at(i));
            etageSuivant.push_back(enfant);
          }
        }
        // cout << "   ";
      }
      else
      {
        // cout << "etape7" << endl;
        tmpTab[0] = (*etageF).at(i)->getName()[0];
        // cout << " le truc bizarre devient :" << (*reglesP).at(index).getString().at(j) << "venant de " << (*reglesP).at(index).getString() << endl;
        tmpTab[1] = '\0';
        a << (*etageF).at(i)->getName()[0];
        node *enfant = new node(40, (*etageF).at(i)->getInclinaisonXY(), (*etageF).at(i)->getInclinaisonZ(), true,
                                tmpTab, (*etageF).at(i)->getPere());
        etageSuivant.push_back(enfant);
      }
    }
    r = rand()%(10) + 1;
    r = r/10;
  }
  // cout << endl;
  (*etageF).clear();
  for(int i = 0; i < etageSuivant.size(); ++i)
  {
    (*etageF).push_back(etageSuivant.at(i));
  }
  // cout << " a = " << a.str() << endl;
  PreparationArbre(a.str(), angleXY, angleZ);
  // cout << "au revoir de createTreeRankByRankF" << endl;
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
void PreparationArbre(string a, double angleXY, double angleZ)
{
  vector<node*> etageR; // etages dans la lecture du mot
  // cout << "entree dans preparationArbre" << endl;
  int m = 0;
  int cpt = 0;
  while ((a[m]) != '\0')
  {
    if(((a[m] > 64) && (a[m] < 91))
    || ((a[m] > 96) && (a[m] < 123)))
    {
      // cout << a[m];
      cpt++;
    }
    m++;
  }
  m = 0;
  char *tmp = new char[2];
  tmp[0] = 'R';
  tmp[1] = '\0';
  node* racineR = new node(NULL, 0, 0, 0, 90, 0, tmp);
  // cout << "inclinaisonXY racineR : " << racineR->getInclinaisonXY() << endl;
  etageR.push_back(racineR);
  node* pere = racineR;
  node* enfant ;
  double inclinaisonXY = 0;
  double inclinaisonZ = 0;
  // cout << "etape4 franchie" << endl;
  while ((a[m]) != '\0')
  {
  // cout << "avec m = " << m << endl;
    if(((a[m] > 64) && (a[m] < 91))
    || ((a[m] > 96) && (a[m] < 123)))
    {
      // cout << " cas1 :a[" << m << "] = " << a[m] << " en int " << (int)a[m] << endl;
      char tmpTab[2];
      tmpTab[0] = a[m];
      tmpTab[1] = '\0';
      enfant = new node(10, inclinaisonXY, inclinaisonZ, true, tmpTab, pere );
      // cout << "nom de l'enfant" << tmpTab << "nom du pere : " << pere->getName() << endl;
      /*
      cout << " inclinaisonXY enfant " << m << " : " << enfant->getInclinaisonXY()
           << "avec pere d'une inclinaisonXY de " << pere->getInclinaisonXY() << " et a[m] = " << a[m] << endl;
      */
      pere = enfant;
    }
    else
    {
      if(a[m] == '[')
      {
      // cout << "1er test inclinaisonXY = " << inclinaisonXY << endl;
        m = arbrePere(m, a, pere, angleXY, inclinaisonXY, angleZ, inclinaisonZ);
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
    }
    m++;
  }
  // cout << "main :x = " << racineR->getX() << " et y = " << racineR->getY() << endl;
  affichageGraphique(racineR);
  exportObj(racineR);
  // cout << "arbre prepare !" << endl;
}


/**********************
*arbre pere permet de creer l'arbre a partie d'un mot
*chaque noeud de l'arbre a des caracteristiques spécifiqués héritées du mot
*
***********/
//dans les cas des []
int arbrePere(int m, string a, node* pere, double angleXY, double inclinaisonXY, double angleZ, double inclinaisonZ)
{
  // cout << "bienvenue dans arbre pere avec pere d'une inclinaisonXY de " << pere->getInclinaisonXY() << " et inclinaisonXY = " << inclinaisonXY << endl;
  m++;
  while ((a[m]) != '\0')
  {
    // cout << "avec m = " << m << endl;
    if(a[m] == ']')
    {
      // cout << "arret de arbrePere avec m = " << m << endl;
      return m;
    }
    if(a[m] == '[')
    {
      // cout << "dans ce cas inclinaisonXY = " << inclinaisonXY << endl;
      m = arbrePere(m, a, pere, angleXY, inclinaisonXY, angleZ, inclinaisonZ);
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
    if(((a[m] > 64) && (a[m] < 91))
    || ((a[m] > 96) && (a[m] < 123)))
    {
      char tmpTab[2];
      tmpTab[0] = a[m];
      tmpTab[1] = '\0';
      node *enfant = new node(10, inclinaisonXY, inclinaisonZ, true, tmpTab, pere );
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
