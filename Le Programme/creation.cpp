#include "creation.h"


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
          
            etageSuivant.push_back((*etageF)[k]);
            k++;
          }
          node* enfant;
          //cout<<"pere possible :"<<(*etageF)[k]->getName();
          node*test=(*etageF)[k];
          while (k<(*contextes)[i].getReglesNouvelles().length()+base)
          {
          
            tmpTab[0] = a[k] ;
            tmpTab[1] = '\0';
            if ((test->getgravite())|| (*contextes)[i].getGravite())
            {
              enfant = new node((*etageF)[0]->getPoids(), hauteur, 180, (*etageF)[0]->getInclinaisonZ(), true,tmpTab ,test);  

            }
            else
            {
              enfant = new node((*etageF)[0]->getPoids(), hauteur, (*etageF)[0]->getInclinaisonXY(), (*etageF)[0]->getInclinaisonZ(), (*contextes)[i].getGravite(),tmpTab ,test);  
              //cout<<"pour "<<enfant->getName()<< " contexte = "<<(*contextes)[i].getGravite(); 
              //cout<<"test gravite du pere"<<enfant->getPere()->getName() <<" = "<<enfant->getPere()->getgravite()<<endl;
            }
            //cout<<endl<<"Coucou on est ici avec"<< tmpTab<< " et "<<(*contextes)[i].getGravite()<<endl; 
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