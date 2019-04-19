#include "MGraphe.h"
#include <fstream>
#include <iomanip>

Mgraphe::Mgraphe(std::string fichier1,std::string fichier2)
{
    std::ifstream ifs{fichier1};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier1);

    std::ifstream ifs2{fichier2};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier2);

    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    std::string id;
    double x, y;

    for (int i = 0; i < ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet : lecture id");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet : lecture x");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet : lecture y");
        m_sommet.insert({id, new Sommet{x,y,id}});
    }

    int taille;
    ifs >> taille;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_arret;
    Arrete* arr;
    std::string id_voisin;

    for (int i = 0; i < taille; ++i)
    {
        ifs>> id_arret;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet : lecture id");
        arr = new Arrete{id_arret};
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet : lecture x");
        ifs>>id_voisin;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn�es sommet : lecture y");

        m_arrete.insert({id_arret,arr});
        /// la on peut remplir notre vecteur de bool
        m_sommet.find(id)->second->ajouterVoisin(m_sommet.find(id_voisin)->second, arr);
        m_sommet.find(id_voisin)->second->ajouterVoisin(m_sommet.find(id)->second, arr);

    }

    ifs2 >> ordre;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture ordre des arretes");

    int dim;
    ifs2 >> dim;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture dim des arretes");
    if (dim != 2)
        throw std::runtime_error("dimention arrete non valide");

    double p1, p2;
    double ptot1 =0;
    double ptot2 =0;

    for (int i = 0; i < ordre; ++i)
    {
        ifs2 >> id_arret;
        if(ifs2.fail())
            throw std::runtime_error("Probleme lecture donn�es arrete : lecture id");
        ifs2 >> p1;
        if(ifs2.fail())
            throw std::runtime_error("Probleme lecture donn�es arrete : lecture poids 1");
        ifs2 >> p2;
        if(ifs2.fail())
            throw std::runtime_error("Probleme lecture donn�es arrete : lecture 2");

        m_arrete.find(id_arret)->second->ajouterpoid(p1,p2);
        ptot1 = ptot1 + p1;
        ptot2 = ptot2 + p2;
    }
    m_ptot1 = ptot1;
    m_ptot2 = ptot2;
    m_couleure = "red";
}

void Mgraphe::afficher() const
{
    std::cout << " Graphe : " << std::endl;
    std::cout << " ordre : " << m_sommet.size() << std::endl;
    for(const auto&it : m_sommet)
    {
        std::cout << "sommet :  ";
        it.second->afficherData();
        it.second->afficher();
        std::cout << std::endl;
    }
    std::cout << "Le cout total est (" << m_ptot1 << ";" << m_ptot2 << ")" << std::endl << std::endl;
}

void Mgraphe::afficherGraph(Svgfile& svgout) const
{

    std::cout<<m_arrete.size();
    std::vector<bool> vec_bin = {1,1,1,1,1,1,1,0,0,1,0,0};

    bool select;
    int s = 0;
    double xd,yd,xa,ya;

    for(const auto&it : m_sommet)
    {
        svgout.addDisk(it.second->getX(),it.second->getY(),5,"black");
    }

    for(size_t i = 0 ; i < m_arrete.size() ; i++)
    {
        if(vec_bin[vec_bin.size() - 1 - i] == 1)
        {
            Arrete*A1 = m_arrete.find( std::to_string(i) ) -> second ;
            for(const auto&it : m_sommet)
            {
                select = it.second->trouverArrete(A1);
                if(select == true )
                {
                    s++;
                    Sommet*S1 = it.second ;
                    if(s == 1)
                    {
                    xd = it.second->getX();
                    yd = it.second->getY();
                    }
                    if(s == 2)
                    {
                    xa = it.second->getX();
                    ya = it.second->getY();
                    }
                }
            }
            s=0;
            svgout.addLine(xd,yd,xa,ya,"black");
        }
    }
}


bool Mgraphe::ordre(std::vector<bool> vect_binaire)
{
    int nb_sommet = m_sommet.size();
    int compteur = 0;

    for(const auto& binary : vect_binaire)
    {
        if (binary == 1)
        {
            compteur++;
            if (compteur >= nb_sommet) return false;
        }
    }

    if(compteur < nb_sommet - 1){
        return false;
    }else{
        return true;
    }
}

bool Mgraphe::connexe(std::vector<bool> vect_bin)
{
    int nb_sommet = m_sommet.size();
    int compteur = 0;

    for(const auto& binary : vect_bin)
    {
        if (binary == 1)
        {
            compteur++;
            if (compteur >= nb_sommet) return false;
        }
    }

    if(compteur < nb_sommet - 1){
        return false;
    }else{
        return true;
    }
}
