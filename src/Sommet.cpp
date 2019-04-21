#include "../Sommet.h"

Sommet::Sommet(double x_init,double y_init,std::string id_init)
:m_id{id_init}, m_x{x_init} , m_y{y_init}
{

}

Sommet::Sommet()
: m_id{0}, m_x{0} , m_y{0}
{

}


void Sommet::ajouterVoisin(Sommet*S1,Arrete*A1)
{
     m_voisin.insert({S1,A1});
}

void Sommet::afficherData() const
{
    std::cout<<"    "<<m_id<<" : "<< " x= " << m_x<< " y= " << m_y<<std::endl;
}

void Sommet::afficher() const
{
    std::cout<< "   voisins : " << std::endl;
    for(const auto &it : m_voisin)
    {
         std::cout << "      sommet :  ";
        it.first->afficherData();
        it.second->afficher();
    }
}

double Sommet::getX()
{
    return m_x;
}

double Sommet::getY()
{
    return m_y;
}

std::string Sommet::getID()
{
    return m_id;
}

std::map<Sommet*,Arrete*> Sommet::getNeighbour()
{
    return m_voisin;
}

bool Sommet::trouverArrete(Arrete*A1)
{
    for(const auto&it : m_voisin)
    {
        if(it.second == A1)
        {
            return true ;
        }
    }
    return false ;
}

