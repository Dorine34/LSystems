#include "export.h"

int recurExport(node* root, std::ofstream* output, int last)
{
  int pere = last;
  if(root->getPere() == NULL)
  {
    *output << "v "
            << root->getY()
            << " "
            << root->getX()
            << " "
            << root->getZ()
            << std::endl;
  }
  if(!(root->getEnfants()->size() > 0))
  {
    return last;
  }
  for(unsigned int i = 0; i < root->getEnfants()->size(); ++i)
  {
    *output << "v "
            << root->getEnfant(i)->getY()
            << " "
            << root->getEnfant(i)->getX()
            << " "
            << root->getEnfant(i)->getZ()
            << std::endl;
    *output << "l "
            << pere << " "
            << ++last
            << std::endl;
    last = recurExport(root->getEnfant(i), output, last);
  }
  return last;
}
/*
void exportObj(node* root, std::string filename)
{
  std::ofstream output;
  std::ostringstream tmpPath;
  tmpPath << filename << ".obj";
  output.open(tmpPath.str().c_str(),std::ios::out);
  output << "o terTREE" << std::endl;
  recurExport(root, &output, 1);
  output.close();
  std::cout << "Fin ecriture du .obj a " << tmpPath.str().c_str() << std::endl;
}
*/

void exportObj(node* root)
{
  std::ofstream output;
  std::ostringstream tmpPath;
  tmpPath << "arbre.obj";
  output.open(tmpPath.str().c_str(),std::ios::out);
  output << "o terTREE" << std::endl;
  recurExport(root, &output, 1);
  output.close();
  std::cout << "Fin ecriture du .obj a " << tmpPath.str().c_str() << std::endl;
}
