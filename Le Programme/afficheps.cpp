#include "afficheps.h"

void afficheVector(node *racine, std::ofstream* output)
 {
//   // std::cout<<"affichage graphique :"<<std::endl;
//   if(racine->getEnfants()->size() > 0)
//   {
//     for(int k = 0; k < racine->getEnfants()->size(); ++k)
//     {
//       afficheVector(racine->getEnfants()->at(k), output);
//     }
//   }
//   *output << racine->getX() << " " << racine->getY() << " 3 0 360 arc" << std::endl;
//   // std::cout<<"boucle :x= " << racine->getX()<<" et y= " << racine->getY() << std::endl;
//   *output << "0 setgray" << std::endl;
//   *output << "fill" << std::endl;
//   *output << "stroke"<< std::endl;
//   *output << std::endl;
}

double xmi,xma,ymi,yma,coeff,decaX,decaY,centreX,centreY;//xmi plus petit x et xma plus grand (x1:gauche | x2:droite)

void cherche_lgla(node *racine){ //lgla : longueur largeur
  if(racine->getX() < xmi)
    xmi = racine->getX();
  else if(racine->getX() > xma)
      xma = racine->getX();
  if(racine->getY() < ymi)
    ymi = racine->getY();
   else if(racine->getY() > yma)
     yma = racine->getY();
  if(racine->getEnfants()->size() > 0)
    for(int k = 0; k < racine->getEnfants()->size(); ++k)
      cherche_lgla(racine->getEnfants()->at(k));
}

void coef(node* racine, std::ofstream* output){
  xmi = racine->getX(); xma = racine->getX(); ymi = racine->getY(); yma = racine->getY(); coeff = 1.0;//(Ré)Intialisation des variables globales pour la recherche.
  cherche_lgla(racine);
  double xtot = xma - xmi, ytot = yma - ymi;
  if(xtot / XMAX > ytot / YMAX)
  {
    coeff = xtot/XMAX;
  }
  else
  {
    coeff = ytot/YMAX;
  }

  centreX = xmi + xtot/2;
  centreY = ymi + ytot/2;
  decaX = XMAX/2 - (centreX)/coeff;
  decaY = YMAX/2 - (centreY)/coeff;

    // std::cout << "Y : " << (ytot/2)/coeff + decaY << " =? " << YMAX/2 << std::endl;
    // std::cout << "X : " << (xtot/2)/coeff + decaX << " =? " << XMAX/2 << std::endl;

    double Ycentered = (ytot/2)/coeff + decaY;
    double Xcentered = (xtot/2)/coeff + decaX;
/*
    *output << lround(YMAX/2) - 5 << " "
            << lround(XMAX/2) << " moveto" << std::endl;
    *output << lround(YMAX/2) + 5 << " "
            << lround(XMAX/2) << " lineto" << std::endl;
    *output << "stroke" << std::endl;
    *output << std::endl;

    *output << lround(YMAX/2) << " "
            << lround(XMAX/2) - 5 << " moveto" << std::endl;
    *output << lround(YMAX/2) << " "
            << lround(XMAX/2) + 5 << " lineto" << std::endl;
    *output << "stroke" << std::endl;
    *output << std::endl;
*/
  afficheEdge(racine, output);
}

/*
void coef(node *racine, std::ofstream* output){ //Les y(s) ne sont pas encore utilisé
  double y_min = 0.0, center = YMAX/2; //largeur = 612
  xma = XMAX; ymi = y_min; yma = YMAX; coeff = 1.0;//(Ré)Intialisation des variables globales pour la recherche.
  cherche_lgla(racine,coeff);
  if(xma > XMAX){   //creer un coeff qui rend égale à la valeur max sur l'axe X
    coeff = xma/XMAX;
    }
  if((racine->getY()/coeff) <= center){ //décalage pour centrer la racine mais 306-400=-706?!(WHAT?!) et 178.258+127.742=306 ce qui est exacte
    deca = center - (racine->getY()/coeff);
    std::cout << " MOINS " << std::endl;
  }
  else{
    std::cout << " PLUS " << std::endl;
    deca = - center - (racine->getY()/coeff);
  }
//deca = racine->getY() + (racine->getY()/coeff);//décalage subit à la racine
  std::cout << "Coefficient : " <<  coeff <<  std::endl
            << "Centre : " << center << std::endl
            << "decalage : " << deca << std::endl
            << "Coordonée Racine : Normal : " << racine->getY()
            << " Avec coeff :" << racine->getY()/coeff << " total :"  << (racine->getY()/coeff)+deca << std::endl;
  //std::cout << deca << " | " <<  ymi/coeff << " Y :" <<  racine->getY()/coeff+deca << " X :" << racine->getX()   << std::endl;
  //------------


  afficheEdge(racine, output);
}
*/
void afficheEdge(node *racine, std::ofstream* output)
{
  if(racine->getEnfants()->size() > 0)
  {
    for(unsigned int k = 0; k < racine->getEnfants()->size(); ++k)
      afficheEdge(racine->getEnfants()->at(k), output);
  }
  for(unsigned int i = 0; i < racine->getEnfants()->size(); ++i)
  {
    //std::cout<< " y="<<racine->getY()<<std::endl;
    //std::cout<< " x="<<racine->getX()<<std::endl;
    *output << lround((racine->getY()/coeff)+decaY) << " "
            << lround((racine->getX()/coeff)+decaX) << " moveto" << std::endl;
    *output << lround((racine->getEnfant(i)->getY()/coeff)+decaY) << " "
            << lround((racine->getEnfant(i)->getX()/coeff)+decaX) << " lineto" << std::endl;
    *output << "stroke" << std::endl;
    *output << std::endl;
  }
}

void affichageGraphique(node* root)
{
  std::cout<<"entree dans affiche vector 2"<<std::endl;
  std::cout << "Debut ecriture du .ps" << std::endl;
  std::cout << "Nb enfants racine : " << root->getEnfants()->size() << std::endl;
  std::ofstream output;
  output.open("arbre.ps",std::ios::out);
  output << "%!PS-Adobe-3.0" << std::endl;
  output << "%%BoundingBox: 0 0 " << YMAX << " " << XMAX << std::endl;
  output << std::endl;
  std::cout<<"root :x= "<<root->getX()<<" et y= "<< root->getY() <<std::endl;
  node* node = root;
  afficheVector(node, &output);
  output << std::endl;
  coef(node, &output);
  output << "showpage";
  output << std::endl;
  output.close();
  std::cout << "Fin ecriture du .ps" << std::endl;
}
