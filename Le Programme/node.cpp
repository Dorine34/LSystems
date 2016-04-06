#include "node.h"

node::node()
{
  setX(0);
  setY(0);
  setZ(0);
  setInclinaisonXY(0);
  setInclinaisonZ(0);
  setPere(NULL);
  setgravite(false);
  this->enfants = new std::vector<node*>();
  this->name = NULL;
  this->angleXY = 0;
  this->angleZ = 0;
}

node::node(node* pere, double x, double y, double z,
          double inclinaisonXY, double  inclinaisonZ,
          char* name, double poids, bool gravite)
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
  setPoids(poids);
  setgravite(gravite);
  this->enfants = new std::vector<node*>();
}

node::node(double poids, double distance, double angleXY, double angleZ,
          bool gravite, char* name, node* pere)
{
  if(pere != NULL)
  {
    int h=1;
    this->pere = pere;
    this->angleXY = angleXY;
    this->angleZ = angleZ;
    this->gravite=gravite;
    this->poids=poids;

    pere->ajoutEnfant(this);
    int direction = pow(-1, h);

    double passageEn3D = cos(PI * this->angleZ * direction / 180);
    setX(this->pere->getX() + passageEn3D * distance * cos(PI * this->angleXY * direction / 180));
    setY(this->pere->getY() + passageEn3D * distance * sin(PI * this->angleXY * direction / 180));
    setZ(this->pere->getZ() + distance * sin(PI * this->angleZ * direction / 180));

    setInclinaisonXY(this->pere->getInclinaisonXY() + this->angleXY * direction);
    setInclinaisonZ(this->pere->getInclinaisonZ() + this->angleZ * direction);
    this->enfants = new std::vector<node*>();
    this->name = NULL;
    this->setName(name);
  }
  else
  {
    std::cout << "Constructor failed, this->pere = " << this->pere << std::endl;
  }
}

node::~node()
{
  if(this->name != NULL)
  {
    delete this->name;
  }
  for(unsigned int i = 0; i < this->getEnfants()->size(); ++i)
  {
    delete this->enfants->at(i);
  }
  if(this->enfants != NULL)
  {
    delete this->enfants;
  }
}
void node::contour(int fils)
{
  double D_X = (getPere()->getX() + getEnfant(fils)->getX()) / 2;
  double D_Y = (getPere()->getY() + getEnfant(fils)->getY()) / 2;
  double D_Z = (getPere()->getZ() + getEnfant(fils)->getZ()) / 2;

  /**
    * CALCUL DES COORDONNEES DE D-B
    */
  double medMinRoot_X = D_X - getX();
  double medMinRoot_Y = D_Y - getY();
  double medMinRoot_Z = D_Z - getZ();

  if (medMinRoot_X == 0 && medMinRoot_Y == 0 && medMinRoot_Z == 0)
  {
      DD_X = getX() + getPere()-> DD_X - getPere()->getX();
      DD_Y = getY() + getPere()-> DD_Y - getPere()->getY();
      DD_Z = getZ() + getPere()-> DD_Z - getPere()->getZ();

    o_DD_X = getX() + getPere()->o_DD_X - getPere()->getX();
    o_DD_Y = getY() + getPere()->o_DD_Y - getPere()->getY();
    o_DD_Z = getZ() + getPere()->o_DD_Z - getPere()->getZ();

      EE_X = getX() + getPere()->  EE_X - getPere()->getX();
      EE_Y = getY() + getPere()->  EE_Y - getPere()->getY();
      EE_Z = getZ() + getPere()->  EE_Z - getPere()->getZ();

    o_EE_X = getX() + getPere()->o_EE_X - getPere()->getX();
    o_EE_Y = getY() + getPere()->o_EE_Y - getPere()->getY();
    o_EE_Z = getZ() + getPere()->o_EE_Z - getPere()->getZ();
  }
  else
  {
    /**
      * CALCUL DE LA NORME DE D-B
      */
    double norm_medMinRoot = sqrt(pow(D_X - getX(), 2) +
                                  pow(D_Y - getY(), 2) +
                                  pow(D_Z - getZ(), 2));

    /**
      * CALCUL DE DD
      */
    DD_X = getX() + (medMinRoot_X/norm_medMinRoot) * getPoids();
    DD_Y = getY() + (medMinRoot_Y/norm_medMinRoot) * getPoids();
    DD_Z = getZ() + (medMinRoot_Z/norm_medMinRoot) * getPoids();

    /**
      * CALCUL DE L'OPPOSE DE DD
      */
    o_DD_X = getX() - (medMinRoot_X/norm_medMinRoot) * getPoids();
    o_DD_Y = getY() - (medMinRoot_Y/norm_medMinRoot) * getPoids();
    o_DD_Z = getZ() - (medMinRoot_Z/norm_medMinRoot) * getPoids();

    /**
      * CALCUL DU PRODUIT VECTORIEL : A-B ^ C-B
      * Resultat : COORDONEES DE E
      */

    /*E_X : YZ - ZY*/
    double pv_X = ((getPere()->getY()       - getY())   /*A_Y - B_Y*/
                * (getPere()->getZ()        - getZ()))  /*A_Z - B_Z*/
                - ((getEnfant(fils)->getZ() - getZ())   /*C_Z - B_Z*/
                * (getEnfant(fils)->getY()  - getY())); /*C_Y - B_Y*/
    /*E_Y : ZX - XZ*/
    double pv_Y = ((getPere()->getZ()       - getZ())   /*A_Z - B_Z*/
                * (getPere()->getX()        - getX()))  /*A_X - B_X*/
                - ((getEnfant(fils)->getX() - getX())   /*C_X - B_X*/
                * (getEnfant(fils)->getZ()  - getZ())); /*C_Z - B_Z*/

    /*E_Z : XY - YX*/
    double pv_Z = ((getPere()->getX()       - getX())   /*A_X - B_X*/
                * (getPere()->getY()        - getY()))  /*A_Y - B_Y*/
                - ((getEnfant(fils)->getY() - getY())   /*C_Y - B_Y*/
                * (getEnfant(fils)->getX()  - getX())); /*C_X - B_X*/

    /**
      * CALCUL DES COORDONNEES DE E-B
      */
    double eMinRoot_X = pv_X - getX();
    double eMinRoot_Y = pv_Y - getY();
    double eMinRoot_Z = pv_Z - getZ();

    /**
      * CALCUL DE LA NORME DE E-B
      */
    double norm_eMinRoot = sqrt(pow(pv_X - getX(), 2) +
                                  pow(pv_Y - getY(), 2) +
                                  pow(pv_Z - getZ(), 2));

    /**
      * CALCUL DE EE
      */
    EE_X = getX() + (eMinRoot_X/norm_eMinRoot) * getPoids();
    EE_Y = getY() + (eMinRoot_Y/norm_eMinRoot) * getPoids();
    EE_Z = getZ() + (eMinRoot_Z/norm_eMinRoot) * getPoids();

    /**
      * CALCUL DE L'OPPOSE DE EE
      */
    o_EE_X = getX() - (eMinRoot_X/norm_eMinRoot) * getPoids();
    o_EE_Y = getY() - (eMinRoot_Y/norm_eMinRoot) * getPoids();
    o_EE_Z = getZ() - (eMinRoot_Z/norm_eMinRoot) * getPoids();
  }
}

node& node::operator=(const node &n)
{
  std::cout<<"bienvenue dans copie node !"<<std::endl;
  if(this == &n)
  {
    return *this;
  }
  this->x = n.x;
  this->y = n.y;
  this->z = n.z;
  this->inclinaisonXY = n.inclinaisonXY;
  this->inclinaisonZ = n.inclinaisonZ;
  this->poids = n.poids;
  this->angleXY = n.angleXY;
  this->angleZ = n.angleZ;
  this->gravite = n.gravite;

  if(name != NULL)
  {
    delete name;
  }
  name = n.name;

  if(pere != NULL)
  {
    delete pere;
  }
  pere = n.pere;

  for(unsigned int i = 0; i < n.enfants->size(); ++i)
  {
    delete enfants->at(i);
  }
  enfants->clear();
  for(unsigned int i = 0; i < n.enfants->size(); ++i)
  {
    enfants->push_back(n.enfants->at(i));
  }
  std::cout<<"node a "<<enfants->size()<< " enfants"<<std::endl;
  return *this;
}

bool node::getgravite()
{
  return gravite;
}

void node::setgravite(bool g)
{
  gravite=g;
}


void node::ajoutEnfant(node* enfant)
{
  this->enfants->push_back(enfant);
  enfant->setPere(this);
}

void node::voirEnfant()
{
  for (unsigned int i=0; i<enfants->size(); i++)
  {
    std::cout << (*enfants)[i]->getName() << " ";
  }
  std::cout<<std::endl;
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
double node::getAngleXY()
{
  return this->angleXY;
}
void node::setAngleXY(double a)
{
  this->angleXY=a;
}

double node::getAngleZ()
{
  return this->angleZ;
}

void node::setAngleZ(double a)
{
  this->angleZ=a;
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

node* node::getEnfant(int index)
{
  if(0 <= index && (unsigned)index < this->enfants->size())
  {
    return this->enfants->at(index);
  }
  else
  {
    return NULL;
  }
}

std::vector<node*>* node::getEnfants()
{
  return this->enfants;
}

void node::setEnfants(std::vector<node*> *enfants)
{
  this->enfants = enfants;
  for(unsigned int i = 0; i < this->enfants->size(); ++i)
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
