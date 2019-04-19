#include "../MGraphe.h"
#include <fstream>
#include <iomanip>
#include <algorithm>

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

std::map<std::string , Arrete*> Mgraphe::getMapArret()
{
    return m_arrete;
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

void afficherSolution(std::vector<bool> vect_bin)
{
    for(size_t i = 0  ; i < vect_bin.size() ; i++)
    {
        std::cout<<vect_bin[i]<<" ";
    }
    std::cout<<" "<<std::endl;
}

void Mgraphe::afficherGraph() const
{
    std::string indice;
    /*for(auto const&it : m_chemin)
    {
        std::cout<<it.first<<std::endl;
    }*/
    std::cout<<"entrer l'indice du graphe a afficher"<<std::endl;
    std::cin>>indice;

    afficherSolution(m_chemin.find(indice)->second);

    std::vector<bool> vec_bin = m_chemin.find(indice)->second;

    Svgfile svgout("graphe.svg");



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

void Mgraphe::afficherGraphique()
{
    double poids_1, poids_2;
    Arrete *arete_actuel;
    Svgfile graphique("graphique.svg");

    for(auto& graphe : m_chemin)
    {
        poids_1 = 0;
        poids_2 = 0;
        for(size_t j = 0 ; j < m_arrete.size() ; j++)
        {
            if(graphe.second[m_arrete.size() - 1 - j] == true)
            {
                arete_actuel = m_arrete.find(std::to_string(j))->second;
                poids_1 += arete_actuel->getPoids_1();
                poids_2 += arete_actuel->getPoids_2();
            }
        }

        //graphique.addDisk(50+10*poids_1, 500-10*poids_2, 2.0, "red");

        graphique.addDisk(50+400.0*poids_1/m_ptot1, 500-400.0*poids_2/m_ptot2, 2.0, "red");
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
            if (compteur >= nb_sommet)
                return false;
        }
    }

    if(compteur < nb_sommet - 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Mgraphe::connexe(std::vector<bool> vect_bin)
{
    bool select;
    //std::vector<std::string> vect_somm;
    int s = 0;
    std::string s1, s2;
    std::map<std::string, int> vect_somm;


    for(size_t i = 0 ; i < m_arrete.size() ; i++)
    {
        if(vect_bin[vect_bin.size() - 1 - i] == 1)
        {
            Arrete*A1 = m_arrete.find( std::to_string(i) ) -> second ;

            for(const auto&it : m_sommet)
            {
                select = it.second->trouverArrete(A1);
                if(select == true )
                {
                    s++;
                    if(s == 1)
                    {
                       // vect_somm.push_back(it.second->getID());
                       vect_somm.insert({it.second->getID(), 0});
                    }
                    if(s == 2)
                    {
                        //vect_somm.push_back(it.second->getID());
                        vect_somm.insert({it.second->getID(), 1});
                    }
                }
            }
            s=0;
        }
    }
    if (vect_somm.size() == m_sommet.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}


void increment(std::vector<bool> &vec_bin)
{
    int i = vec_bin.size() -1 ;

    do
    {

        if(vec_bin[i] == 0)
        {
            vec_bin[i] = 1;
            i = 1000;

        }

        else if( vec_bin[i] == 1 )
        {
            vec_bin[i] = 0;
            i--;
            if(i < 0)
            {
                i = 1000;
            }
        }


    }
    while(i < 1000);


}

void Mgraphe::departcpt(std::vector<bool>&vec_bin)
{
    int i = vec_bin.size() -1 ;
    int nb = 0;
    while(nb != m_sommet.size() -1)
    {
        vec_bin[i] = 1;
        i--;
        nb++;
    }
}

void Mgraphe::arrivecpt(std::vector<bool>&vec_bin)
{
    int i = 0;
    int nb = 0;
    while(nb != m_sommet.size() -1)
    {
        vec_bin[i] = 1;
        i++;
        nb++;
    }
}

/*void Mgraphe::trouverSolution()
{
    std::vector<bool> vect_bin;
    vect_bin.resize(m_arrete.size() );

    std::vector<bool> vect_bina;
    vect_bina.resize(m_arrete.size() );

    std::string name;
    (*this).departcpt(vect_bin);
    (*this).arrivecpt(vect_bina);
    //afficherSolution(vect_bin);
    //afficherSolution(vect_bina);

    int i= 0;

    do
    {
        i++;
        increment(vect_bin) ;
        if( (*this).ordre(vect_bin) == true )
        {
            //afficherSolution(vect_bin);
            if( (*this).connexe(vect_bin) == true )
            {
                //afficherSolution(vect_bin);
                name = "bf" + std::to_string(i);
                m_chemin.insert({name,vect_bin});
            }

        }
    }
    while(vect_bin != vect_bina);
}*/

void Mgraphe::trouverSolution()
{
    std::vector<bool> vect_bin;
    vect_bin.resize(m_arrete.size() );
    std::string name;

    for(long i = 0 ; i < std::pow( 2 , m_arrete.size() ) ; i++)
    {
        increment(vect_bin) ;
        if( (*this).ordre(vect_bin) == true )
        {
            //afficherSolution(vect_bin);
            if( (*this).connexe(vect_bin) == true )
            {
                //afficherSolution(vect_bin);
                name = "bf" + std::to_string(i);
                m_chemin.insert({name,vect_bin});
            }

        }
    }
}

<<<<<<< benoitmtz
/*void Mgraphe::TrouverPareto()
{

}*/
=======
void Mgraphe::kruskal(std::string fichier, std::string fichier2)
{
    int test;
    test = 1;

    Mgraphe main{fichier, fichier2};

    std::map<std::string , Arrete*> map_arrete;
    std::vector<Arrete*> vect_arretes;

   map_arrete = main.getMapArret();

   for (const auto &a : map_arrete)
   {
       vect_arretes.push_back(a.second);
   }

   if (test == 1)
   {


   }
   std::sort(vect_arretes.begin(), vect_arretes.end(), [](Arrete* s1, Arrete* s2)
    {
        return s1->getPoids(1) > s2->getPoids(1);
    });

}
>>>>>>> debut kruskal
