#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>
#include <map>
#include "Arrete.h"

class Sommet
{
public :
    Sommet(double x_init,double y_init,std::string id_init, int cc_init);
    Sommet();
    void ajouterVoisin(Sommet*S1,Arrete*A1);
    void afficher() const;
    void afficherData() const;
    double getX();
    double getY();
    std::string getID();
    std::map<Sommet*,Arrete*> getNeighbour();
    bool trouverArrete(Arrete*A1);
   int getCC();
    void setCC(int Ca);
    bool verifier_connex();

private :
    std::string m_id;
    int m_cc;
    double m_x,m_y;
    std::map<Sommet*,Arrete*> m_voisin;

};

#endif // SOMMET_H_INCLUDED
