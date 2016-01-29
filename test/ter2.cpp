

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>  
#include <fstream>//pour le graphe
#include "node.h"
using namespace std;



/***************
Objectifs : arbre dynamique donc tab dynamique -> actuellement arbre de taille k avec a rempli
structure de données pour chaque feuille de l'arbre
******************/
void reecriture(char**tab, int k);
int calculInclinaison(int a);
double CalculDegreAbs(double base, int inclinaison);
double CalculDegreOrd(double base, int inclinaison);



int main (int argc, char* argv[]){


  cout<< "Bonjour Camarades!"<<endl;
  char * tab[100];
  char str [80];
  node* tree [100];
  int t=0;

  tree[t] = new node(1000, 0, (long)90, ".", NULL);
  cout<<"nom="<<tree[t]->getName()<< ", abs ="<<tree[t]->getX()<< ", ord="<<tree[t]->getY()<< "inli="<<tree[t]->getInclinaison()<< endl;
  t++;


  FILE * pFile;
  pFile=fopen ("myfile.txt","r");
 
  if (pFile==NULL) perror ("impossible d'ouvrir le fichier !");
  else
    {
      fgets (str,2, pFile)!=NULL; 
    } 
  
  fclose (pFile);
 
  tab [0]= (char*)malloc(strlen(str)+1);
  strcpy(tab[0],str);

/**************creation tronc******************/
  if ( strcmp("a",str)==0){
    double incli =calculInclinaison(90-10);
    double absi= CalculDegreAbs(1000, incli);
    double ordo= CalculDegreOrd(0, incli);
    tree[t] = new node(absi, ordo, (long)incli, str, tree[t-1]);
    tree[t-1]->ajoutEnfant (tree[t]);

    for(int j = 0; j < tree[t-1]->getSizeEnfant(); ++j)
    cout<< "enfants = "<<tree[t-1]->getEnfant(j)->getName()<<endl;


    cout<<"nom="<<tree[t]->getName()<< ", abs ="<<tree[t]->getX()<< ", ord="<<tree[t]->getY()<< "inli="<<tree[t]->getInclinaison()<< ", pere :"<< tree[t]->getPere()->getName()<< endl;
    }   
/***************fin du tronc***********************/
  char s[100];
  int a=1;

  cout<<"appuyez sur une touche pour continuer et quit pour quitter"<<endl;
  cin>>s;

  while (strcmp (s,"quit")!=0){
    //reecriture (tab,a);

/************REECRITURE***************/

    char buff[1024];
    cout<<"boucle "<<a<<endl;
    FILE * pFile;
    int c, b, i=0;
    string str = tab[a-1];   
    char bufferTest[1024];
    strcpy (bufferTest,"");

    while (str[i]!= '\0'){
      b=str[i];
      i++;
      pFile=fopen ("myfile.txt","r");
      if (pFile==NULL) perror ("impossible d'ouvrir le fichier !");
      else
      {
        do {
          c = fgetc (pFile);
          if (c==b){
            c = fgetc (pFile);
            if (c == '>'){
              c = fgetc (pFile);
              while (c!='.'){
                int f=sprintf(buff,"%c", (char)c);
                strcat(bufferTest,buff);
                //cout<< "buff="<<buff<<"et buffTest ="<<bufferTest<<endl;
                c = fgetc (pFile);
              }
            }
          }
        } while (c != EOF);
        fclose (pFile);
      }
    }
    tab [a]= (char*)malloc(strlen(bufferTest)+1);
    strcpy(tab[a], bufferTest);
    cout<<"rang"<<a<<" = "<<tab[a]<<endl;
    strcpy (bufferTest,"");

/********FIN REECRITURE************/

    a++;
    cout<<endl<<"Resultat :"<<endl<<endl;
    for (int i=0; i<a;i++){
    cout<< "rang "<<i<<" : "<<tab[i]<<endl; 
    }
  cout<<"appuyez sur une touche pour continuer et quit pour quitter"<<endl;
  cin>>s;
  }

  //for (int i=0; i<a;i++){free (tab[i]);}
  return 0;
}



int calculInclinaison(int a){//permet d'avoir l'inclinaison d'une branche
  if (a>=360){return (a-360);}
  if (a<0){return (360+a);}
  else return a;
} 

double CalculDegreAbs(double base, int inclinaison){//permet d'avoir l'abscisse selon l'inclinaison
  double g= PI * inclinaison / 180;//calcul en radian
  //cout<<"inclinaison="<<inclinaison <<" et cos(g)="<<cos(g)<<endl;
  return base+10*cos(g); 
}

double CalculDegreOrd(double base, int inclinaison){//permet d'avoir l'ordonnee selon l'inclinaison
  double g= PI * inclinaison / 180;//calcul en radian
  return base+10*sin(g); 
}
