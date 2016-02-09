#include "node.h"

node::node()
{
  setX(0);
  setY(0);
  setInclinaison(0);
  setPere(NULL);
  this->enfants = new std::vector<node*>();
  this->name = NULL;
  this->angle = 0;
}

node::node(node* pere, double x, double y, double inclinaison, char* name)
{
  std::cout<<"entree dans node ()"<<std::endl;
  this->angle = 0;
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
  setInclinaison(inclinaison);
  setDV(false);
  this->enfants = new std::vector<node*>();
}

node::node(double distance, double angle, bool horaire, char* name, node* pere){
  
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
    this->angle = angle;
    //this->angle -= 0.5 * (this->getPere()->angle);
    pere->ajoutEnfant(this);
    int direction = pow(-1, h);
    setX(this->pere->getX() + distance * cos(PI * this->angle * direction / 180));
    setY(this->pere->getY() + distance * sin(PI * this->angle * direction / 180));
    setInclinaison(this->pere->getInclinaison() + this->angle * direction);
    setDV(false);
    this->enfants = new std::vector<node*>();
    this->name = NULL;
    this->setName(name);
//    std::cout<<"on a donc dans node(.....) : angle = "<<angle<<" et inclinaison = "<<inclinaison<<std::endl;
  }
  else
  {
    std::cout << "Constructor failed, this->pere = " << this->pere<<std::endl;
  }
}

node::~node()
{
 /* if(this->name != NULL)
  {
    delete this->name;
  }
  delete this->enfants;
*/}

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

double node::getInclinaison()
{
  return this->inclinaison;
}

void node::setInclinaison(double inclinaison)
{
  this->inclinaison = inclinaison;
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
  if(index < this->enfants->size())
  {
    return this->enfants->at(index);
  }
  else return NULL;
}

void node::setEnfants(std::vector<node*> *enfants)
{
  this->enfants = enfants;
  for(int i = 0; i < this->enfants->size(); ++i)
    this->enfants->at(i)->setPere(this);
}
