#include "../Arrete.h"

Arrete::Arrete(std::string id_init)
:m_id{id_init}
{

}

Arrete::Arrete(std::string id_init, std::string S1, std::string S2)
:m_id{id_init}, m_s1{S1}, m_s2{S2}
{

}


Arrete::Arrete()
:m_id{0} , m_p1{0} , m_p2{0}
{

}

void Arrete::ajouterpoid(double p1_init,double p2_init)
{
    m_p1 = p1_init;
    m_p2 = p2_init;
}

void Arrete::afficher() const
{
     std::cout << "      Arret : " << m_id << std::endl;
    std::cout << "          cout 1 : " << m_p1 << std::endl;
    std::cout << "          cout 2 : " << m_p2 << std::endl;
}

double Arrete::getPoids_1()
{
    return m_p1;
}

double Arrete::getPoids_2()
{
    return m_p2;
}

double Arrete::getPoids(int test)
{
    if (test == 1)
    {
        return m_p1;
    }else if ( test == 2 ) {
        return m_p2;
    }

    return 1;
}

std::string Arrete::getID()
{
    return m_id;
}

std::string Arrete::getS1()
{
    return m_s1;
}

std::string Arrete::getS2()
{
    return m_s2;
}

int Arrete::getCC()
{
    return m_cc;
}

void Arrete::setCC(int etat)
{
    m_cc = etat;
}


