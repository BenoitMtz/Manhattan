#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include <iostream>

class Arrete
{
public :
    Arrete(std::string id_init);
    Arrete(std::string id_init, std::string, std::string);
    Arrete();
    void ajouterpoid(double p1_init,double p2_init);
    void afficher() const;
    double getPoids_1();
    double getPoids_2();
    double getPoids(int test);
    std::string getS1();
    std::string getS2();
    std::string getID();
    void setCC(int etat);
    bool getCC();


private :
    std::string m_id;
    double m_p1, m_p2;
    int m_cc;
    std::string m_s1, m_s2;
};



#endif // ARRETE_H_INCLUDED
