#ifndef MGRAPHE_H_INCLUDED
#define MGRAPHE_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>
//#include "Arrete.h"
#include "Sommet.h"
#include "svgfile.h"

class Mgraphe
{
public :
     Mgraphe(std::string fichier1,std::string fichier2);
     void afficher() const;
     void afficherGraph() const;
     bool connexe(std::vector<bool> vect_bin);
     friend void increment(std::vector<bool> &vec_bin);
     friend void afficherSolution(std::vector<bool> vect_bin);
      void departcpt(std::vector<bool>&vec_bin);
      void arrivecpt(std::vector<bool>&vec_bin);
     void trouverSolution();
     void afficherGraphique();
     void kruskal(std::string fichier, std::string fichier2);
     std::map<std::string , Arrete*> getMapArret();
     bool trouverSommet(Arrete*A1,std::map<std::string, int> &vect_somm);

private :
    std::map<std::string , Sommet*> m_sommet;
    std::map<std::string , Arrete*> m_arrete;
    double m_ptot1,m_ptot2;
    std::string m_couleure;
    std::map<std::string , std::vector<bool> > m_chemin;
    std::vector<std::pair<double, double>> m_tousLesPoids;
};

#endif // MGRAPHE_H_INCLUDED
