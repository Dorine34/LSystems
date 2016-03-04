#include "rules.h"

Rules::Rules()
{
  std::cout << "Bienvenue dans la creation d'arbre" << std::endl;
  choice();
}

Rules::~Rules(){}

int Rules::getXY()
{
  return angXY;
}

void Rules::setXY(int ang)
{
  angXY = ang % 360;
}

int Rules::getZ()
{
  return angZ;
}

void Rules::setZ(int ang)
{
  angZ = ang % 360;
}

int Rules::getLargeur()
{
  return largeur;
}

void Rules::setLargeur(int l)
{
  largeur = l;
}

int Rules::getLongueur()
{
  return longueur;
}

void Rules::setLongueur(int l)
{
  longueur = l;
}

std::string Rules::getAxiom()
{
  return axiom;
}

void Rules::setAxiom(std::string str)
{
  axiom = str;
}

std::string Rules::getRule(int index)
{
  return rules.at(index);
}

std::vector<std::string> Rules::getRules()
{
  return rules;
}

void Rules::setRules(std::vector<std::string> ru)
{
  for (unsigned int i = 0; i < ru.size(); ++i)
  {
    rules.push_back(ru.at(i));
  }
}

void Rules::addRule(std::string str)
{
  rules.push_back(str);
}

void Rules::choice()
{
  int inp = 0, inpPar;
  std::string strTmp;

  std::cout << "Choisissez ce que vous voulez faire :"  << std::endl
            << "\t" << STOP << " - Sauvegarder"         << std::endl
            << "\t" << KILL << " - Abandonner"          << std::endl
            << "\t" << SETD << " - Modifier Dimension"  << std::endl
            << "\t" << XY   << " - Modifier Angle XY"   << std::endl
            << "\t" << Z    << " - Modifier Angle Z"    << std::endl
            << "\t" << LARG << " - Modifier Largeur"    << std::endl
            << "\t" << LONG << " - Modifier Longueur"   << std::endl
            << "\t" << AXIO << " - Modifier Axiome"     << std::endl
            << "\t" << ADD  << " - Ajouter une regle"   << std::endl
            << "\t" << PRIN << " - Afficher tout"       << std::endl;
  std::cin >> inp;
  system("clear");
  switch(inp)
  {
    case STOP :
    {
      if(rules.size() > 0
      && axiom.size() > 0
      && angXY > 0
      && angZ >= 0
      && largeur > 0
      && longueur > 0)
      {
        write();
        return;
      }
      break;
    }
    case KILL :
    {
      return;
    }
    case SETD :
    {
      std::cout << "Choissez le type d'arbre desire :" << std::endl
                << "> (0) 2D" << std::endl
                << "> (1) 3D" << std::endl;  
      do
      {
        std::cin >> inpPar;
      }while(inpPar != 0 && inpPar != 1);
      if(!inpPar)
      {
        setZ(0);
      }
      break;
    }
    case XY :
    {
      std::cout << "Saisissez l'angle XY : " << std::endl;
      std::cin >> inpPar;
      setXY(inpPar);
      break;
    }
    case Z :
    {
      std::cout << "Saisissez l'angle Z : " << std::endl;
      std::cin >> inpPar;
      setZ(inpPar);
      break;
    }
    case LARG :
    {
      std::cout << "Saisissez la largeur : " << std::endl;
      std::cin >> inpPar;
      setLargeur(inpPar);
      break;
    }
    case LONG :
    {
      std::cout << "Saisissez la longueur : " << std::endl;
      std::cin >> inpPar;
      setLongueur(inpPar);
      break;
    }
    case AXIO :
    {
      std::cout << "Saisissez l'axiome : " << std::endl;
      std::cin >> strTmp;
      setAxiom(strTmp);
      break;
    }
    case ADD :
    {
      std::cout << "Format : F=F+F-F/F\\F"           << std::endl
                << "+ pour angleXY+"                 << std::endl
                << "- pour angleXY-"                 << std::endl
                << "/ pour angleZ +"                 << std::endl
                << "\\ pour angleZ -"                << std::endl
                << "[] pour faire des sous branches" << std::endl
                << "Saisissez l'axiome : " << std::endl;
      std::cin >> strTmp;
      addRule(strTmp);
      break;
    }
    case PRIN :
    {
      printVar();
      break;
    }
    default :
    {

    }
  }
  choice();
}

void Rules::write()
{
  std::fstream outfile("codeGenere", std::fstream::out);
  outfile << "angleXY=" << angXY << "." << std::endl
          << "angleZ="  << angZ << "." << std::endl
          << "largeur=" << largeur << "." << std::endl
          << "longueur=" << longueur << "." << std::endl
          << axiom << "." << std::endl;
  for (unsigned int i = 0; i < rules.size(); ++i)
  {
    outfile << rules.at(i) << "." << std::endl;
  }
  // system("ter1 codeGenere");
}

void Rules::printVar()
{
  std::cout << "Angle XY\t: " << angXY    << std::endl
            << "Angle Z\t\t: "<< angZ     << std::endl
            << "Largeur\t\t: "<< largeur  << std::endl
            << "Longueur\t: " << longueur << std::endl
            << "Axiome\t\t: ";
  if(axiom.size() <= 0)
  {
    std::cout << "EMPTY"<< std::endl;
  }
  else
  {
    std::cout << axiom  << std::endl;
  }
  std::cout << "Regles" << std::endl;
  for (unsigned int i = 0; i < rules.size(); ++i)
  {
    std::cout << "\tRegle "<< i <<" : " << rules.at(i) << std::endl;
  }
  if (rules.size() <= 0)
  {
    std::cout << "\tNONE" << std::endl;
  }
}
