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
    std::string getS1() const;
    std::string getS2() const;
    std::string getID() const;
    int getCC();
    void setCC(int etat);


private :
    std::string m_id;
    double m_p1, m_p2;
    int m_cc;
    std::string m_s1, m_s2;
};



#endif // ARRETE_H_INCLUDED
