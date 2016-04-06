#include "export.h"

void Export::promptXYZ(t_double x, t_double y, t_double z)
{
  std::cout << "X = "
            << x
            << "\tY = "
            << y
            << "\tZ = "
            << z
            << std::endl;
}

/**
  * ########################
  */

Export::Export(node* root, bool trunk)
{
  last = 0;

  std::ostringstream tmpPath;
  tmpPath << "arbre.obj";
  out.open(tmpPath.str().c_str(), std::ios::out);

  exportObj(root, trunk, 0);

  std::cout << "Fin ecriture du .obj a " << tmpPath.str().c_str() << std::endl;
}

Export::Export(std::vector<node*> arbre, bool trunk)
{
  last = 0;
  std::ostringstream tmpPath;
  tmpPath << "arbre.obj";
  out.open(tmpPath.str().c_str(), std::ios::out);

  for (unsigned int i = 0; i < arbre.size(); ++i)
  {
    exportObj(arbre.at(i), trunk, i);
  }

  std::cout << "Fin ecriture du .obj a " << tmpPath.str().c_str() << std::endl;
}

Export::~Export()
{
  out.close();
}

void Export::exportObj(node* root, bool trunk, int nb)
{
  out << "o terTREE." << nb << std::endl;
  if (trunk)
  {
    recurExportTrunk(root);
  }
  else
  {
    recurExportSimple(root);
  }
}

std::string Export::exportVertices(t_double x, t_double y, t_double z)
{
  std::ostringstream oss;
  oss << "v "
      << y
      << " "
      << x
      << " "
      << z
      << std::endl;
  ++last;
  return oss.str();
}

std::string Export::exportRoot(node* root)
{
  std::ostringstream oss;
  oss << exportVertices(root->getX(), root->getY() + root->getPoids(), root->getZ());
  oss << exportVertices(root->getX(), root->getY(), root->getZ() + root->getPoids());
  oss << exportVertices(root->getX(), root->getY() - root->getPoids(), root->getZ());
  oss << exportVertices(root->getX(), root->getY(), root->getZ() - root->getPoids());
  ++last;

  // std::cout << "Root :" << std::endl;
  // std::cout << "_____" << std::endl;
  return oss.str();
}

std::string Export::exportEdge(node* pere, node* actual, node* fils, int nb)
{
  std::ostringstream oss;
  actual->contour(nb);

  oss << exportVertices(actual->  DD_X, actual->  DD_Y, actual->  DD_Z);
  oss << exportVertices(actual->  EE_X, actual->  EE_Y, actual->  EE_Z);
  oss << exportVertices(actual->o_DD_X, actual->o_DD_Y, actual->o_DD_Z);
  oss << exportVertices(actual->o_EE_X, actual->o_EE_Y, actual->o_EE_Z);

  // std::cout << "_____" << std::endl;
  return oss.str();
}

/**
  * EXEMPLE :
  * f 2//1 1//5 5//2
  * f 3//2 2//5 5//3
  * f 4//3 3//5 5//4
  * f 1//4 4//5 5//1
  */

std::string Export::exportApex(int pere)
{
  std::ostringstream oss;

  int firstPere = pere - 3;

  for (int i = 0; i < 4; ++i)
  {
    oss << "f "
        << firstPere + ((1 + i) % 4)
        << "//"
        << i + firstPere
        << " "
        << i + firstPere
        << "//"
        << last - 1
        << " "
        << last - 1
        << "//"
        << firstPere + ((1 + i) % 4)
        << std::endl;
  }
  return oss.str();
}

/**
  * EXEMPLE :
  * f 2//1 1//5 5//6 6//2
  * f 3//2 2//6 6//7 7//3
  * f 4//3 3//7 7//8 8//4
  * f 1//4 4//8 8//5 5//1
  */

std::string Export::exportTrunk(int pere)
{
  std::ostringstream oss;
  int firstTop = last - 4;
  int firstPere = pere - 3;
  for (int i = 0; i < 4; ++i)
  {
    oss << "f "
        << firstPere + ((1 + i) % 4)
        << "//"
        << i + firstPere
        << " "
        << i + firstPere
        << "//"
        << i + firstTop
        << " "
        << i + firstTop
        << "//"
        << firstTop + ((1 + i) % 4)
        << " "
        << firstTop + ((1 + i) % 4)
        << "//"
        << firstPere + ((1 + i) % 4)
        << std::endl;
  }
  return oss.str();
}

int Export::recurExportSimple(node* root)
{
  int pere = last;
  if(root->getPere() == NULL)
  {
    out << exportVertices(root->getX(), root->getY(), root->getZ());
    // promptXYZ(root->getX(), root->getY(), root->getZ());
    ++pere;
  }
  if(!(root->getEnfants()->size() > 0))
  {
    return last;
  }
  for(unsigned int i = 0; i < root->getEnfants()->size(); ++i)
  {
    out << exportVertices(root->getEnfant(i)->getX(), root->getEnfant(i)->getY(), root->getEnfant(i)->getZ());
    // promptXYZ(root->getEnfant(i)->getX(), root->getEnfant(i)->getY(), root->getEnfant(i)->getZ());
    out << "l "
        << pere
        << " "
        << last
        << std::endl;
    last = this->recurExportSimple(root->getEnfant(i));
  }
  return last;
}

int Export::recurExportTrunk(node* root)
{
  int pere = last - 1;
  /**
    * Bloc racine
    */
  if(root->getPere() == NULL)
  {
    out << exportRoot(root);
  }
  /**
    * Bloc apex
    */
  if (root->getEnfants()->size() == 0)
  {
    out << "#ME" << std::endl;
    out << exportVertices(root->getX(), root->getY(), root->getZ());
    // promptXYZ(root->getX(), root->getY(), root->getZ());
    out << exportApex(pere);
  }
  /**
    * Bloc branche
    */
  for (unsigned int i = 0; i < root->getEnfants()->size(); ++i)
  {
    if (!(root->getPere() == NULL))
    {
      out << exportEdge(root->getPere(), root, root->getEnfant(i), i);
      out << exportTrunk(pere);
    }
    last = recurExportTrunk(root->getEnfant(i));
  }

  return last;
}
