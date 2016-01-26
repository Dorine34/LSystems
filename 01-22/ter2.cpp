

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>  
#include <fstream>//pour le graphe

using namespace std;

/***************
Objectifs : arbre dynamique donc tab dynamique -> actuellement arbre de taille k avec a rempli
structure de données pour chaque feuille de l'arbre
******************/
void reecriture(char**tab, int k);

int main (int argc, char* argv[]){
  cout<< "Bonjour Camarades!"<<endl;
  char * tab[100];
  char str [80];
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

  char s[100];
  int a=1;

  cout<<"appuyez sur une touche pour continuer et quit pour quitter"<<endl;
  cin>>s;

  while (strcmp (s,"quit")!=0){
    reecriture (tab,a);
    a++;
    cout<<endl<<"Resultat :"<<endl<<endl;
    for (int i=0; i<a;i++){
    cout<< "rang "<<i<<" : "<<tab[i]<<endl; 
    }
  cout<<"appuyez sur une touche pour continuer et quit pour quitter"<<endl;
  cin>>s;
  }
  for (int i=0; i<a;i++){free (tab[i]);}
  return 0;
}

void reecriture (char**tab, int k)
{
  char buff[1024];
  cout<<"boucle "<<k<<endl;
  FILE * pFile;
  int c, a, i=0;
  string str = tab[k-1];   
  char bufferTest[1024];
  strcpy (bufferTest,"");

  while (str[i]!= '\0'){
    a=str[i];
    i++;
    pFile=fopen ("myfile.txt","r");
    if (pFile==NULL) perror ("impossible d'ouvrir le fichier !");
    else
      {
        do {
          c = fgetc (pFile);
          if (c==a){
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
  tab [k]= (char*)malloc(strlen(bufferTest)+1);
  strcpy(tab[k], bufferTest);
  cout<<"rang"<<k<<" = "<<tab[k]<<endl;
  strcpy (bufferTest,"");
}