#include "afficheps.h"

void afficheVector(node *racine, std::ofstream* output)
{
  if(racine->getEnfants()->size() > 0)
  {
    for(int k = 0; k < racine->getEnfants()->size(); ++k)
    {
      afficheVector(racine->getEnfants()->at(k), output);
    }
  }
  *output << racine->getX() << " " << racine->getY() << " 3 0 360 arc" << std::endl;
  *output << "0 setgray" << std::endl;
  *output << "fill" << std::endl;
  *output << "stroke"<< std::endl;
  *output << std::endl;
}

void afficheEdge(node *racine, std::ofstream* output)
{
  if(racine->getEnfants()->size() > 0)
  {
    for(int k = 0; k < racine->getEnfants()->size(); ++k)
      afficheEdge(racine->getEnfants()->at(k), output);
  }
  for(int i = 0; i < racine->getEnfants()->size(); ++i)
  {
    *output << racine->getX() << " " << racine->getY() << " moveto" << std::endl;
    *output << racine->getEnfants()->at(i)->getX() << " " << racine->getEnfants()->at(i)->getY() << " lineto" << std::endl;
    *output << "stroke" << std::endl;
    *output << std::endl;
  }
}

void affichageGraphique(node* root)
{
  std::cout << "Debut ecriture du .ps" << std::endl;
  std::ofstream output;
  output.open("arbre.ps",std::ios::out);
  output << "%!PS-Adobe-3.0" << std::endl;
  output << "%%BoundingBox: 0 0 612 792" << std::endl;
  output << std::endl;
  node* node = root;
  afficheVector(node, &output);
  output << std::endl;
  afficheEdge(node, &output);
  output << "showpage";
  output << std::endl;
  output.close();
  std::cout << "Fin ecriture du .ps" << std::endl;
}
