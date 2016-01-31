/****************Faire Pousser des Arbres en Pogrammant*************/
/* Fait le 31/01
/* A ameliorer
/*****************Yin, Arcadia et Oxidire*******************/


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>//pour le graphe

#include<iomanip>
#include<cassert>
#include<sstream>


#include "node.h"
#include "afficheps.h"


using namespace std;


long lectureReglesF(char *filenameF);//return angle

void createTreeRankByRankF(vector<char> mots, vector<string> regles, long angle);
void PreparationArbre(string a, long angle);
int arbrePere(int m, string a, node* pere, long angle, long inclinaison);


vector<node*> etageF;//etages selon le rang de creation du mot
vector<node*> etageR;//etages dans la lecture du mot
vector<char> motsF; 
vector<string> reglesF; 


int main(int argc, char** argv)
{
  cout <<  "Bonjour camarades !" << endl;
  
  char* tabF[100];
  char strF[80];
  char* filenameF = new char[11 * sizeof(char)];
  sprintf(filenameF, "generateur.txt");

  FILE* pFileF;
  if(argc == 2)
  {
    delete filenameF;
    filenameF = new char[(strlen(argv[1]) + 1) * sizeof(char)];
    filenameF = argv[1];
  }
  pFileF = fopen(filenameF, "r");

  if(pFileF == NULL)
  {
    perror("Impossible d'ouvrir le fichier ");
    return -1;
  }
  else
  {
    fgets(strF, 2, pFileF) != NULL;
  }

  fclose(pFileF);

  long angle =lectureReglesF(filenameF);
  
  char motRacineF = motsF.at(0);
  motsF.erase(motsF.begin());
  char *tmpTabF = new char[2];
  tmpTabF[0] = motRacineF;
  tmpTabF[1] = '\0';
  cout<<"mot tmp = "<<tmpTabF<<endl;
  
  node* racineF = new node(NULL, 500, 500, 500, tmpTabF);
  etageF.push_back(racineF);
  
  tabF[0] = new char[(strlen(strF) + 1) * sizeof(char)];
  strcpy(tabF[0], strF);


  char saisie[100];
  int rang = 1;

  cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
  cin >> saisie;

  while(strcmp(saisie, "quit") != 0)
  {
    rang++;
    createTreeRankByRankF(motsF, reglesF, angle);//la creation en soit
    cout << endl << "Resultat : " << endl << endl;
    cout << "Appuyez sur une touche pour continuer et quit pour quitter" << endl;
    cin >> saisie;
  }
  delete filenameF;
  return 0;
}

long lectureReglesF(char *filenameF) { //permet de faciliter l acces aux regles
  long angle =0;

  ifstream file(filenameF);
  if (!file.is_open()) {
    perror("File not found");
  }
  string line;
  bool b = false;
  while (getline(file, line)) {
    b = false;
    for (unsigned int k = 0; k < line.size(); ++k) {
      if ((line[k]>='0')&&(line[k]<='9')){
        angle=angle*10+line[k]-48;
      }
      else{
      if (line[k] == '=') {
        motsF.push_back(line[0]);
        b = true;
      } else if (line[k] == '.') {
                if (b) {
                  int beg = line.find('=') + 1;
                  reglesF.push_back(line.substr(beg, k - beg));
                } else {
                motsF.push_back(line[0]);
                }
            }
          }
      }
  }
  file.close();
  cout<<"Fin de lectureReglesF"<<endl;
  return angle;
}


void createTreeRankByRankF(vector<char> motsF, vector<string> reglesF, long angle) {
  cout<<"bienvenue dans le cas F"<<endl;
  ostringstream a;
   
  vector<node*> etageSuivant;
  char *tmpTab = new char[2];
  for (int i = 0; i < etageF.size(); ++i) {
     char x= etageF.at(i)->getName()[0];
      if ((x=='[')||(x==']')||(x=='+')||(x=='-')){
        tmpTab[0] = x;
        tmpTab[1] = '\0';
        a<<x;

      node *enfant = new node(40, 60, false, tmpTab, etageF.at(i));
      etageSuivant.push_back(enfant);
      }
      else{
    int index = 0;
    for (unsigned int j = 0; j < motsF.size(); ++j) {
      if (motsF.at(j) == etageF.at(i)->getName()[0]) {
        index = j;
        break;
      }
    }
    for (int j = 0; j < reglesF.at(index).size(); ++j) {
      tmpTab[0] = reglesF.at(index).at(j);
      tmpTab[1] = '\0';
      a<<reglesF.at(index).at(j);
      node *enfant = new node(40, reglesF.at(index).at(j)=='a'? 40 : 60, !(reglesF.at(index).at(j) == 'a'), tmpTab, etageF.at(i));
      etageSuivant.push_back(enfant);
      }
    }
    cout << "   ";
    }
    cout << endl;
    etageF.clear();
    for (int i = 0; i < etageSuivant.size(); ++i) {
      etageF.push_back(etageSuivant.at(i));
    }
      cout<< " a = "<< a.str()<<endl;
      PreparationArbre(a.str(), angle);
}

void PreparationArbre(string a, long angle){//a represente une ligne de caracteres
    cout<<"entree dans preparationArbre"<<endl;
   int m=0;
   int cpt=0;
   while ((a[m])!='\0'){
      if (((a[m] >64)&&(a[m] <91))||((a[m] >96)&&(a[m] <123)))
      {//cout<<a[m];
      cpt++;}
      m++;
      }
        
  m=0;
  char *tmp = new char[2];
  tmp[0] = 'R';
  tmp[1] = '\0';
  node* racineR = new node(NULL, 300, 200, 90, tmp);
    //  cout<<"etape2 franchie"<<endl;
  etageR.push_back(racineR);
  //cout<<"etape3 franchie"<<endl;
  node* pere=racineR;
  node *enfant ;
  long inclinaison=0;
  //cout<<"etape4 franchie"<<endl;
    while ((a[m])!='\0'){
        if (((a[m] >64)&&(a[m] <91))||((a[m] >96)&&(a[m] <123)))
        {
          //cout<< " cas1 :a["<<m<<"]="<<a[m] <<" en int "<<(int)a[m]<<endl;
          char tmpTab[2];
          tmpTab[0] = a[m];
          tmpTab[1] = '\0';
      
          enfant = new node(60, inclinaison,true, tmpTab,pere );
          //cout<<"Sprint inclinaison enfant "<<m<<" : "<<inclinaison<<"avec pere d'une inclinaison de "<<pere->getInclinaison()<<" et a[m]="<<a[m]<<endl;
          pere=enfant;
        }
        else {
          //cout<< " cas2 :a["<<m<<"]="<<a[m] <<" en int "<<(int)a[m]<<endl;

          if (a[m]=='['){
              m= arbrePere(m, a, pere, angle,inclinaison);
            }
          if(a[m]=='+'){inclinaison+= angle;
        //cout<<"inclinaison 1 :apres un +, l'inclinaison devient"<<inclinaison<<endl;
          }
          if(a[m]=='-'){inclinaison-= angle;
          //  cout<<"inclinaison 1 :apres un +, l'inclinaison devient"<<inclinaison<<endl;
          }
        }        
        m++;
        
  }
  affichageGraphique(racineR);
}

int arbrePere(int m, string a, node* pere,long angle,long inclinaison){//dans les cas des []
  cout<<"bienvenue dans arbre pere avec pere d'une inclinaison de "<<pere->getInclinaison()<<endl;
  m++;
  while ((a[m])!='\0'){
      if (a[m]=='['){ return (arbrePere(m, a, pere, angle, inclinaison));}
      if(a[m]=='+'){ inclinaison +=angle;
        //cout<<"apres un +, l'inclinaison devient"<<inclinaison<<endl;
      }
      if(a[m]=='-'){ inclinaison -=angle;
      //  cout<<"apres un -, l'inclinaison devient"<<inclinaison<<endl;
      }
      if (a[m]==']'){ return (m+1);}
      if (((a[m] >64)&&(a[m] <91))||((a[m] >96)&&(a[m] <123)))
        {
              char tmpTab[2];
              tmpTab[0] = a[m];
              tmpTab[1] = '\0';
              node *enfant = new node(40, inclinaison,true, tmpTab,pere );                 
              //cout<<" Sprint inclinaison2 enfant  "<<m<<" : "<<inclinaison<<"avec pere d'une inclinaison de "<<pere->getInclinaison()<<" et a[m]="<<a[m]<<endl;
              pere=enfant;
        }
        m++;
    }
    return m;
}
