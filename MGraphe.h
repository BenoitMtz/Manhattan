#ifndef MGRAPHE_H_INCLUDED
#define MGRAPHE_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>
#include "Arrete.h"
#include "Sommet.h"
#include "svgfile.h"

class Mgraphe
{
public :
     Mgraphe(std::string fichier1,std::string fichier2);
     void afficher() const;
     void afficherGraph(Svgfile& svgout) const;
     bool ordre(std::vector<bool> vect_binaire);
     bool connexe(std::vector<bool> vect_bin);

private :
    std::map<std::string , Sommet*> m_sommet;
    std::map<std::string , Arrete*> m_arrete;
    double m_ptot1,m_ptot2;
    std::string m_couleure;
    std::map<std::string , std::vector<bool> > m_chemin;
};

#endif // MGRAPHE_H_INCLUDED
