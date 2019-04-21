#ifndef MGRAPHE_H_INCLUDED
#define MGRAPHE_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>
#include "Arrete.h"
#include "Sommet.h"

class Mgraphe
{
public :
     Mgraphe(std::string fichier1,std::string fichier2);
     void afficher() const;
     void afficherGraph() const;
     bool connexe(std::vector<bool> vect_bin);
    bool increment(std::vector<bool> &vec_bin);
     friend void afficherSolution(std::vector<bool> vect_bin);
    void departcpt(std::vector<bool>&vec_bin);
    void arrivecpt(std::vector<bool>&vec_bin);
     void trouverSolution(std::string fichier1,std::string fichier2);
     void afficherGraphique();
     std::vector<bool> kruskal(std::string fichier, std::string fichier2);
     std::map<std::string , Arrete*> getMapArret();
     void dijktra();
     Sommet* getSommet(std::string id);
     void changerTousCC(int Cd, int Ca);
     bool trouverSommet(Arrete*A1,std::map<std::string, int> &vect_somm);
     bool selec_Arete(Arrete*A1,std::vector<std::string>&S1);
     bool connexe1(int i,std::map<std::string,int>&S1);

private :
    std::map<std::string , Sommet*> m_sommet;
    std::map<std::string , Arrete*> m_arrete;
    double m_ptot1,m_ptot2;
    std::string m_couleure;
    std::map<std::string , std::vector<bool> > m_chemin;
    std::vector<std::pair<double, double>> m_tousLesPoids;
};

#endif // MGRAPHE_H_INCLUDED
