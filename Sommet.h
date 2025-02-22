#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>
#include <map>
#include "Arrete.h"

class Sommet
{
public :
    Sommet(double x_init,double y_init,std::string id_init);
    Sommet();
    void ajouterVoisin(Sommet*S1,Arrete*A1);
    void afficher() const;
    void afficherData() const;
    double getX();
    double getY();
    std::string getID();
    bool trouverArrete(Arrete*A1);

private :
    std::string m_id;
    double m_x,m_y;
    std::map<Sommet*,Arrete*> m_voisin;
};

#endif // SOMMET_H_INCLUDED
