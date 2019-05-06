#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include <iostream>

class Arrete
{
public :
    Arrete(std::string id_init);
    Arrete();
    void ajouterpoid(double p1_init,double p2_init);
    void afficher() const;
    double getPoids_1();
    double getPoids_2();

private :
    std::string m_id;
    double m_p1, m_p2;
};


#endif // ARRETE_H_INCLUDED
