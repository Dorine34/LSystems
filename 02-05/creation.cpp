#include "creation.h"


long lectureReglesF(char *filenameF, vector<char> *motsF, vector<string> *reglesF) { //permet de faciliter l acces aux regles
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
        (*motsF).push_back(line[0]);
        b = true;
      } else if (line[k] == '.') {
                if (b) {
                  int beg = line.find('=') + 1;
                  (*reglesF).push_back(line.substr(beg, k - beg));
                } else {
                (*motsF).push_back(line[0]);
                }
            }
          }
      }
  }
  file.close();
  //cout<<"Fin de lectureReglesF"<<endl;
  return angle;
}


void createTreeRankByRankF(vector<node*> *etageF, vector<char> *motsF, vector<string> *reglesF, long angle) {
  //cout<<"bienvenue dans le cas F"<<endl;
  ostringstream a;
   
  vector<node*> etageSuivant;
  char *tmpTab = new char[2];

  for (int i = 0; i < (*etageF).size(); ++i) {
     char x= (*etageF).at(i)->getName()[0];
      if ((x=='[')||(x==']')||(x=='+')||(x=='-')){
        tmpTab[0] = x;
        tmpTab[1] = '\0';
        a<<x;

      node *enfant = new node(60, 60, false, tmpTab, (*etageF).at(i));
      etageSuivant.push_back(enfant);
      }
      else{
    int index = 0;
    for (unsigned int j = 0; j < (*motsF).size(); ++j) {
      if ((*motsF).at(j) == (*etageF).at(i)->getName()[0]) {
        index = j;
        break;
      }
    }    for (int j = 0; j < (*reglesF).at(index).size(); ++j) {
      tmpTab[0] = (*reglesF).at(index).at(j);
      tmpTab[1] = '\0';
      a<<(*reglesF).at(index).at(j);
      node *enfant = new node(40, (*reglesF).at(index).at(j)=='a'? 40 : 60, !((*reglesF).at(index).at(j) == 'a'), tmpTab, (*etageF).at(i));
      etageSuivant.push_back(enfant);
      }
    }
    cout << "   ";
    }
    cout << endl;
    (*etageF).clear();
    for (int i = 0; i < etageSuivant.size(); ++i) {
      (*etageF).push_back(etageSuivant.at(i));
    }
      cout<< " a = "<< a.str()<<endl;
      PreparationArbre(a.str(), angle);
}

void PreparationArbre(string a, long angle){//a represente une ligne de caracteres
    vector<node*> etageR;//etages dans la lecture du mot

    //cout<<"entree dans preparationArbre"<<endl;
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
  node* racineR = new node(NULL, 50, 400, 90, tmp);
  cout<<"inclinaison racineR : "<<racineR->getInclinaison()<<endl;
  etageR.push_back(racineR);
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
//          cout<<" inclinaison enfant "<<m<<" : "<<enfant->getInclinaison()<<"avec pere d'une inclinaison de "<<pere->getInclinaison()<<" et a[m]="<<a[m]<<endl;
          pere=enfant;
        }
        else {
          if (a[m]=='['){
  //            cout<<"1er test inclinaison ="<<inclinaison<<endl;
              m= arbrePere(m, a, pere, angle,inclinaison);
            }
          if(a[m]=='+'){inclinaison+= angle;
           }
          if(a[m]=='-'){inclinaison-= angle;
          }
        }        
        m++;
        
  }
  //cout<<"main :x= "<<racineR->getX()<<" et y= "<< racineR->getY() <<endl;
  affichageGraphique(racineR);
}

int arbrePere(int m, string a, node* pere,long angle,long inclinaison){//dans les cas des []
 // cout<<"bienvenue dans arbre pere avec pere d'une inclinaison de "<<pere->getInclinaison()<<" et angle ="<<angle<<endl;
  m++;
  while ((a[m])!='\0'){
      if (a[m]=='['){
   //     cout<<"dans ce cas inclinaison ="<<inclinaison<<endl;
       return (arbrePere(m, a, pere, angle, inclinaison));}
      if(a[m]=='+'){ inclinaison +=angle;
     //   cout<<"apres un +, l'inclinaison devient"<<inclinaison<<endl;
      }
      if(a[m]=='-'){ inclinaison -=angle;
       // cout<<"apres un -, l'inclinaison devient"<<inclinaison<<endl;
      }
      if (a[m]==']'){ return (m+1);}
      if (((a[m] >64)&&(a[m] <91))||((a[m] >96)&&(a[m] <123)))
        {
              char tmpTab[2];
              tmpTab[0] = a[m];
              tmpTab[1] = '\0';
              node *enfant = new node(60, inclinaison,true, tmpTab,pere );                 
         //     cout<<" inclinaison enfant "<<m<<" : "<<enfant->getInclinaison()<<"avec pere d'une inclinaison de "<<pere->getInclinaison()<<" et a[m]="<<a[m]<<endl;
              pere=enfant;
        }
        m++;
    }
    return m;
}
