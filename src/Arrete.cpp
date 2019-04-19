#include "../Arrete.h"

Arrete::Arrete(std::string id_init)
:m_id{id_init}
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

