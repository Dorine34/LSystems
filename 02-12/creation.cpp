#include "creation.h"
/*************************/
/* probleme arret non respecter
/*
/**************************/

double puissanceMoins10(double x, int p){
  for (int i=0; i<p; i++){
    x=x*0.1;
  }
  return x;
}
/*********Permet de sauvegarder les regles**********/
double lectureReglesF(char *filenameF,vector<char> *motsP, vector<Probabilite> *reglesP) { //permet de faciliter l acces aux regles
  
  int cpt =0;
  double angle =0;
  double probabilite=0;
  
  ifstream file(filenameF);
  if (!file.is_open()) {
    perror("File not found");
  }
  
  string line;
  bool b = false;
  
  while (getline(file, line)) {
    b = false;
    
    for (unsigned int k = 0; k < line.size(); ++k) {
      if ((line[k]>='0')&&(line[k]<='9')){//recupere la premiere donnee correspondant à l'angle
        angle=angle*10+line[k]-48;
      }
      else{
      if (line[k] == '('){ //cas probabiliste qui commence par une parenthese
        k++;
        while (((line[k]>='0')&&(line[k]<='9'))||(line[k]==',')){
          if (line[k]==',')k++;
            probabilite=probabilite*10+line[k]-48;//recuperation de la probabilite en entier
            cpt++;
            k++;
          }
          probabilite =puissanceMoins10(probabilite, cpt-1);//probabilite en double
          cout<<"La probabilite ="<<probabilite<<endl;
          Probabilite p1(probabilite,"");//creation de probabilite
          probabilite=0; cpt=0;
          (*motsP).push_back(line[k+1]);
          
          while (line[k] != '.'){k++;}//pointeur dur la fin de la ligne
          int deb = line.find('=') + 1;
          p1.setString(line.substr(deb, k - deb));
          (*reglesP).push_back(p1);
      }
      else{
        if (line[k] == '=') {//cas normal, non probabiliste
        (*motsP).push_back(line[0]);
        b = true;
        } else if (line[k] == '.') {
                if (b) {
                  int beg = line.find('=') + 1;
                  Probabilite p1(1,line.substr(beg, k - beg));
                  (*reglesP).push_back(p1);
                } 
              }
            }
          }
        }
    }
  file.close();
  return angle;
}


void createTreeRankByRankF(vector<node*> *etageF, double angle, vector<char> *motsP, vector<Probabilite> *reglesP) {
  cout<<"bienvenue dans le cas F"<<endl;
  ostringstream a;
   /*for (int j =0; j<(*reglesP).size(); j++){
      cout << "j="<< j<<" motsP="<<(*motsP)[j]<< " -> "<<(*reglesP)[j].getString()<< "de probabilite"<< (*reglesP)[j].getProbabilite()<<endl;
    }
*/
  srand(time(NULL));
  double r=rand()%(10)+1;
  r=r/10;
  //cout<<"la fonction random r="<<r<<endl;
  double total=0;

  vector<node*> etageSuivant;
  char *tmpTab = new char[2];

  for (int i = 0; i < (*etageF).size(); ++i) {
     char x= (*etageF).at(i)->getName()[0];
      if ((x=='[')||(x==']')||(x=='+')||(x=='-')){
        tmpTab[0] = x;
        tmpTab[1] = '\0';
        a<<x;
      node *enfant = new node(10, 60, false, tmpTab, (*etageF).at(i));
      etageSuivant.push_back(enfant);
      }
      else{
    int index = 0;
    for (unsigned int j = 0; j < (*motsP).size(); ++j) {
      //cout<<(*motsP).at(j)<<" correspond a "<<(*etageF).at(i)->getName()[0]<<endl;
      if ((*motsP).at(j) == (*etageF).at(i)->getName()[0]) {
        index = j;
    //    cout<<"Trouve ! avec j="<< j <<" motsP="<<(*motsP).at(j)<< " et " << (*etageF).at(i)->getName()[0]<< " ===>"<<(*reglesP).at(index).toString()<<endl;
        break;
      }
    } 
    total=(*reglesP).at(index).getProbabilite();
    int ctr=0;
    //cout<<" ici1 "<<(*reglesP).at(index).toString()<<"r="<<r<< "et total="<<total<<endl;
    while ((r>total)&&(ctr<10)){
      ctr++;
      //cout<<endl<<endl<<"Dans ce cas :"<< r<<">"<<total<<endl;  
      total+=(*reglesP).at(index).getProbabilite();
        for (unsigned int j = index+1; j < (*motsP).size(); ++j) {
          if ((*motsP).at(j) == (*etageF).at(i)->getName()[0]) {
          index = j;
          break;
        }
      }
    }
    if (ctr !=10){
        for (unsigned int j = 0; j < (*reglesP).at(index).getString().size(); ++j) {  
            tmpTab[0] = (*reglesP).at(index).getString().at(j);
        //    cout<< " le truc bizarre devient :"<< (*reglesP).at(index).getString().at(j)<< "venant de "<<(*reglesP).at(index).getString()<<endl;
            tmpTab[1] = '\0';
            a<<(*reglesP).at(index).getString().at(j);
            node *enfant = new node(40, (*reglesP).at(index).getString().at(j)=='a'? 40 : 60, !((*reglesP).at(index).getString().at(j) == 'a'), tmpTab, (*etageF).at(i));
            etageSuivant.push_back(enfant);
        }  
      }
      cout << "   ";
    }
    r=rand()%(10)+1;
    r=r/10;
  }
    cout << endl;
    (*etageF).clear();
    for (int i = 0; i < etageSuivant.size(); ++i) {
      (*etageF).push_back(etageSuivant.at(i));
    }
      cout<< " a = "<< a.str()<<endl;
      PreparationArbre(a.str(), angle);
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

void PreparationArbre(string a, double angle){//a represente une ligne de caracteres
    vector<node*> etageR;//etages dans la lecture du mot
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
  node* racineR = new node(NULL, 50, 400, 90, tmp);
//  cout<<"inclinaison racineR : "<<racineR->getInclinaison()<<endl;
  etageR.push_back(racineR);
  node* pere=racineR;
  node *enfant ;
  double inclinaison=0;
  //cout<<"etape4 franchie"<<endl;
    while ((a[m])!='\0'){
  //    cout<<"avec m="<<m<<endl;
        if (((a[m] >64)&&(a[m] <91))||((a[m] >96)&&(a[m] <123)))
        {
          //cout<< " cas1 :a["<<m<<"]="<<a[m] <<" en int "<<(int)a[m]<<endl;
          char tmpTab[2];
          tmpTab[0] = a[m];
          tmpTab[1] = '\0';
      
          enfant = new node(10, inclinaison,true, tmpTab,pere );
    //      cout<<" inclinaison enfant "<<m<<" : "<<enfant->getInclinaison()<<"avec pere d'une inclinaison de "<<pere->getInclinaison()<<" et a[m]="<<a[m]<<endl;
          pere=enfant;
        }
        else {
          if (a[m]=='['){
          //    cout<<"1er test inclinaison ="<<inclinaison<<endl;
              m= arbrePere(m, a, pere, angle,inclinaison);
            }
          if(a[m]=='+'){inclinaison-= angle;
          //  cout<<"l'inclinaison devient :"<<inclinaison<<endl;
           }
          if(a[m]=='-'){inclinaison+= angle;
          //  cout<<"l'inclinaison devient :"<<inclinaison<<endl;
          }
        }        
        m++;
  }
  //cout<<"main :x= "<<racineR->getX()<<" et y= "<< racineR->getY() <<endl;
  affichageGraphique(racineR);
}


/**********************
*arbre pere permet de creer l'arbre a partie d'un mot
*chaque noeud de l'arbre a des caracteristiques spécifiqués héritées du mot
*
***********/
int arbrePere(int m, string a, node* pere,double angle,double inclinaison){//dans les cas des []
//  cout<<"bienvenue dans arbre pere avec pere d'une inclinaison de "<<pere->getInclinaison()<<" et inclinaison ="<<inclinaison<<endl;
  m++;
  while ((a[m])!='\0'){
//    cout<<"avec m="<<m<<endl;

      if (a[m]==']'){ 
//        cout<<"arret de arbrePere avec m="<<m<<endl;
        return (m);}
      if (a[m]=='['){
//        cout<<"dans ce cas inclinaison ="<<inclinaison<<endl;
       m= arbrePere(m, a, pere, angle, inclinaison);
//       cout<<"retour de arbrePere avec m= "<<m<<endl;
     }
      if(a[m]=='+'){ inclinaison -=angle;
//        cout<<"apres un +, l'inclinaison devient"<<inclinaison<<endl;
      }
      if(a[m]=='-'){ inclinaison +=angle;
//        cout<<"apres un -, l'inclinaison devient"<<inclinaison<<endl;
      }
      if (((a[m] >64)&&(a[m] <91))||((a[m] >96)&&(a[m] <123)))
        {
              char tmpTab[2];
              tmpTab[0] = a[m];
              tmpTab[1] = '\0';
              node *enfant = new node(10, inclinaison,true, tmpTab,pere );                 
//              cout<<" inclinaison enfant "<<m<<" : "<<enfant->getInclinaison()<<"avec pere d'une inclinaison de "<<pere->getInclinaison()<<" et a[m]="<<a[m]<<endl;
              pere=enfant;
        }
        m++;
    }
//    cout<<"cas final"<<endl;
    return m;// ne sert jamais

}
