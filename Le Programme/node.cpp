

#include "node.h"

node::node()
{
  setX(0);
  setY(0);
  setZ(0);
  setInclinaisonXY(0);
  setInclinaisonZ(0);
  setPere(NULL);
  this->enfants = new std::vector<node*>();
  this->name = NULL;
  this->angleXY = 0;
  this->angleZ = 0;
}

node::node(node* pere, double x, double y, double z, double inclinaisonXY,double  inclinaisonZ, char* name, double poids)
{
  std::cout<<"entree dans node ()"<<std::endl;
  this->angleXY = 0;
  this->angleZ = 0;
  if(pere != NULL)
  {
    pere->ajoutEnfant(this);
  }
  else
  {
    this->pere = NULL;
  }
  this->name = NULL;
  this->setName(name);
  setX(x);
  setY(y);
  setZ(z);
  setInclinaisonXY(inclinaisonXY);
  setInclinaisonZ(inclinaisonZ);
  setDV(false);
  setPoids(poids);
  this->enfants = new std::vector<node*>();
}

node::node(double distance, double angleXY, double angleZ, bool horaire, char* name, node* pere){
  
  if(pere != NULL)
  {
    int h;
    if(horaire)
    {
      h = 0;
    }
    else
    {
      h = 1;
    }
    this->pere = pere;
    this->angleXY = angleXY;
    this->angleZ = angleZ;
    //this->angle -= 0.5 * (this->getPere()->angle);
    pere->ajoutEnfant(this);
    int direction = pow(-1, h);

    double passageEn3D = cos(PI * this->angleZ * direction / 180);
    setX(this->pere->getX() + passageEn3D*distance*cos(PI * this->angleXY * direction / 180));

    setY(this->pere->getY() + passageEn3D*distance*sin(PI * this->angleXY * direction / 180));

    setZ(this->pere->getZ()+ distance *sin(PI * this->angleZ * direction / 180));
    
    //setPoids(this->pere->getPoids()/2);//poids du pere = poids du fils/2
    setInclinaisonXY(this->pere->getInclinaisonXY() + this->angleXY * direction);
    setInclinaisonZ(this->pere->getInclinaisonZ() + this->angleZ * direction);
    //std::cout<<"x="<<(this->x )<<" car passage en 3d="<<cos(PI * this->angleZ * direction / 180)<< "cos(0)="<<cos(0)<< " et cos(1)="<<cos(1)<<std::endl;
    //std::cout<<"y=" <<(this->y )<<std::endl;
    setDV(false);
    this->enfants = new std::vector<node*>();
    this->name = NULL;
    this->setName(name);
    //std::cout<<"name="<<(this->name)<<" poids="<<(this->poids)<<std::endl;
    //std::cout<<"nb de freres="<<this->pere->getEnfants()->size()<<std::endl;
    int nbVraisEnfants=0;
    double nouveauPoids=this->pere->getPoids();
    //std::cout<<"Bonjour, je suis : "<<this->getName()<<" Mon pere est"<<this->pere->getName()[0]<<"et pese :"<<nouveauPoids<<std::endl; 
     for (int i = 0; i < this->pere->getEnfants()->size(); ++i)
    {
      //std::cout<<"Mon frere  "<<this->pere->getEnfant(i)->getName()[0];
      // this->pere->getEnfant(i)->resetDV();
      //std::cout<<"mes freres sont :";
      if(((this->pere->getEnfant(i)->getName()[0] > 64) && (this->pere->getEnfant(i)->getName()[0] < 91))
        || ((this->pere->getEnfant(i)->getName()[0] > 96) && (this->pere->getEnfant(i)->getName()[0] < 123)))
      {
        //std::cout<<this->pere->getEnfant(i)->getName()<<"  ";  
        nbVraisEnfants++;
      }
      //std::cout<<std::endl<<" J'en ai donc :"<<nbVraisEnfants<<std::endl;
    }

     for (int i = 0; i < this->pere->getEnfants()->size(); ++i)
    {

      if(((this->pere->getEnfant(i)->getName()[0] > 64) && (this->pere->getEnfant(i)->getName()[0] < 91))
        || ((this->pere->getEnfant(i)->getName()[0] > 96) && (this->pere->getEnfant(i)->getName()[0] < 123)))
      {

        this->setPoids(nouveauPoids/nbVraisEnfants); 
        //std::cout<<this->pere->getEnfant(i)->getName()[0]<<" -> "<<this->pere->getEnfant(i)->getPoids()<<" ";
      }
      //std::cout<<"name="<<(this->name)<<"pere ="<< this->pere->getName()<<" poids="<<(this->poids)<<std::endl;
    }
    

//    std::cout<<"on a donc dans node(.....) : angle = "<<angle<<" et inclinaison = "<<inclinaison<<std::endl;
  }
  else
  {
    std::cout << "Constructor failed, this->pere = " << this->pere<<std::endl;
  }
}

node::~node()
{
  if(this->name != NULL)
  {
    delete this->name;
  }
  delete this->enfants;
}

void node::ajoutEnfant(node* enfant)
{
  this->enfants->push_back(enfant);
  enfant->setPere(this);
}

void node::resetDV(){
  if(this->getEnfants()->size() > 0)
  {
    for (int i = 0; i < this->getEnfants()->size(); ++i)
    {
      this->getEnfant(i)->resetDV();
    }
  }
  this->setDV(false);
}

bool node::getDV()
{
  return this->dv;
}

void node::setDV(bool dv)
{
  this->dv = dv;
}

char* node::getName()
{
  return this->name;
}

void node::setName(char* name)
{
  if(this->name != NULL && strlen(this->name) > 0)
  {
    delete this->name;
  }
  if (strlen(name) > 0)
  {
    this->name = new char[(strlen(name) + 1) * sizeof(char)];
    strcpy(this->name, name);
  }
  else
  {
    this->name = NULL;
  }
}

double node::getX()
{
  return this->x;
}

void node::setX(double x)
{
  this->x = x;
}

double node::getY(){
  return this->y;
}

void node::setY(double y)
{
  this->y = y;
}

double node::getZ(){
  return this->z;
}

void node::setZ(double z)
{
  this->z = z;
}


double node::getInclinaisonXY()
{
  return this->inclinaisonXY;
}

void node::setInclinaisonXY(double inclinaison)
{
  this->inclinaisonXY = inclinaison;
}

double node::getInclinaisonZ()
{
  return this->inclinaisonZ;
}

void node::setInclinaisonZ(double inclinaison)
{
  this->inclinaisonZ = inclinaison;
}


node* node::getPere()
{
  return this->pere;
}

void node::setPere(node* pere)
{
  this->pere = pere;
}

std::vector<node*>* node::getEnfants()
{
  return this->enfants;
}

node* node::getEnfant(int index)
{
  if(0 <= index && index < this->enfants->size())
  {
    return this->enfants->at(index);
  }
  else
  {
    return NULL;
  }
}

void node::setEnfants(std::vector<node*> *enfants)
{
  this->enfants = enfants;
  for(int i = 0; i < this->enfants->size(); ++i)
  {
    this->enfants->at(i)->setPere(this);
  }
}


double node::getPoids(){
  return this->poids;
}

void node::setPoids(double poids)
{
  this->poids = poids;
}
