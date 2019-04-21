#include "../MGraphe.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "../svgfile.h"

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
        m_sommet.insert({id, new Sommet{x,y,id, i}});
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

std::map<std::string, Arrete*> Mgraphe::getMapArret()
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
    std::pair<double,double> coords, checkPoint = {0,0}, temponPareto, temponDraw;
    Arrete *arete_actuel;
    size_t gabX = 50, gabY = 50, tailleGraphiqueY = 700, tailleGraphiqueX = 1400;
    m_tousLesPoids.clear();
    std::string text;
    Svgfile graphique("graphique.svg", 2000, 1000);

    graphique.addLine(gabX, gabY, gabX, tailleGraphiqueY+gabY, "black");
    graphique.addLine(gabX, tailleGraphiqueY+gabY, tailleGraphiqueX+gabX, tailleGraphiqueY+gabY, "black");
    graphique.addTriangle(gabX-5, gabY, gabX+5, gabY, gabX, gabY-10, "black");
    graphique.addTriangle(tailleGraphiqueX+gabX, tailleGraphiqueY+gabY+5, tailleGraphiqueX+gabX, tailleGraphiqueY+gabY-5, tailleGraphiqueX+gabX+10, tailleGraphiqueY+gabY, "black");
    graphique.addText(gabX-47, gabY, "cout 1", "grey");
    graphique.addText(tailleGraphiqueX+gabX-20, tailleGraphiqueY+gabY+20, "cout 2", "grey");

    for(auto& graphe : m_chemin)
    {
        coords = {0,0};
        for(size_t j = 0 ; j < m_arrete.size() ; j++)
        {
            if(graphe.second[m_arrete.size()-1-j] == true)
            {
                ///On compte le poids total de chacunes des possibilités

                arete_actuel = m_arrete.find(std::to_string(j))->second;
                coords.first += arete_actuel->getPoids_1();
                coords.second += arete_actuel->getPoids_2();
            }
        }

        if(coords.first+coords.second < checkPoint.first+checkPoint.second || checkPoint.first+checkPoint.second == 0)
        {
            ///On cherche le premier point de référence pour la frontière de Pareto

            checkPoint = coords;
        }

        ///On rempli notre tableau de point et on dessine tous les points

        m_tousLesPoids.push_back(coords);
        graphique.addDisk(gabX+tailleGraphiqueX*coords.first/m_ptot1, tailleGraphiqueY+gabY-tailleGraphiqueY*coords.second/m_ptot2, 2.0, "red");
    }

    ///On dessine le premier point de référence pour la frontière de Pareto

    graphique.addDisk(gabX+tailleGraphiqueX*checkPoint.first/m_ptot1, tailleGraphiqueY+gabY-tailleGraphiqueY*checkPoint.second/m_ptot2, 3.0, "green");
    text = std::to_string((int)checkPoint.first) + " ; " + std::to_string((int)checkPoint.second);
    graphique.addText(gabX+tailleGraphiqueX*checkPoint.first/m_ptot1+5, tailleGraphiqueY+gabY-tailleGraphiqueY*checkPoint.second/m_ptot2+5, text, "grey");

    std::sort(m_tousLesPoids.begin(), m_tousLesPoids.end(), [](std::pair<double,double> coords_1, std::pair<double,double> coords_2)
    {
        return coords_1.first < coords_2.first;
    });
    temponPareto = checkPoint;
    for(size_t i = 0 ; i < m_tousLesPoids.size()-1 ; i++)
    {
        if(m_tousLesPoids[i].first > checkPoint.first)
        {
            if(m_tousLesPoids[i].second < temponPareto.second)
            {
                ///On dessine les points de Pareto de droite

                temponPareto = m_tousLesPoids[i];
                graphique.addDisk(gabX+tailleGraphiqueX*m_tousLesPoids[i].first/m_ptot1, tailleGraphiqueY+gabY-tailleGraphiqueY*m_tousLesPoids[i].second/m_ptot2, 3.0, "green");
            }
        }
    }

    std::sort(m_tousLesPoids.begin(), m_tousLesPoids.end(), [](std::pair<double,double> coords_1, std::pair<double,double> coords_2)
    {
        return coords_1.second < coords_2.second;
    });
    temponPareto = checkPoint;
    for(size_t i = 0 ; i < m_tousLesPoids.size()-1 ; i++)
    {
        if(m_tousLesPoids[i].second > checkPoint.second)
        {
            if(m_tousLesPoids[i].first < temponPareto.first)
            {
                ///On dessine les points de Pareto de gauche

                temponPareto = m_tousLesPoids[i];
                graphique.addDisk(gabX+tailleGraphiqueX*m_tousLesPoids[i].first/m_ptot1, tailleGraphiqueY+gabY-tailleGraphiqueY*m_tousLesPoids[i].second/m_ptot2, 3.0, "green");
            }
        }
    }
}

void Mgraphe::dijktra()
{
    size_t gabX = 50, gabY = 50, tailleGraphiqueY = 700, tailleGraphiqueX = 1400;
    Svgfile graphique("graphique_dijktra.svg", 2000, 1000);

    for(auto& graphe : m_chemin)
    {
        std::map<std::string,Arrete*> map_arrete_dijktra;
        std::map<std::string,std::pair<double,double>> map_poids_dijktra;
        std::map<std::string,std::pair<double,double>> map_poids_dijktra_finale;
        std::pair<std::string,std::pair<double,double>> paire_minimum = {"0", {0,0}};

        for(size_t j = 0 ; j < m_arrete.size() ; j++)
        {
            if(graphe.second[m_arrete.size()-1-j] == true)
            {
                ///On compte le poids total de chacunes des possibilités
                //coords.first += arrete_actuel->getPoids_1();
                //coords.second += arrete_actuel->getPoids_2();
                map_arrete_dijktra.insert(*m_arrete.find(std::to_string(j)));
            }
        }

        while(map_poids_dijktra_finale.size() <= m_sommet.size())
        {
            std::string sommet_id = paire_minimum.first;
            for(auto& paire_arrete : map_arrete_dijktra)
            {
                if(paire_arrete.second->getS1() == sommet_id)
                {
                    //map_poids_dijktra.insert(sommet_id, {paire_arrete.second->getPoids_1() + paire_minimum.second.first, paire_arrete.second->getPoids_2() + paire_minimum.second.second});

                }
            }

            auto min_it = std::min_element(map_poids_dijktra.begin(), map_poids_dijktra.end(),[](const std::pair<std::string, std::pair<double,double>>& p1, const std::pair<std::string, std::pair<double,double>>& p2)
            {
                return p1.second.second < p2.second.second;
            });

            paire_minimum = *min_it;
            map_poids_dijktra_finale.insert(paire_minimum);
        }
        unsigned int poidsTotalGraphe_1 = 0, poidsTotalGraphe_2 = 0;
        for(auto& finale : map_poids_dijktra_finale)
        {
            poidsTotalGraphe_1 += (unsigned int)finale.second.first;
            poidsTotalGraphe_2 += (unsigned int)finale.second.second;
        }
        graphique.addDisk(gabX+tailleGraphiqueX*poidsTotalGraphe_1/1000, tailleGraphiqueY+gabY-tailleGraphiqueY*poidsTotalGraphe_2/1000, 2.0, "red");
    }
}


bool Mgraphe::trouverSommet(Arrete*A1,std::map<std::string, int> &vect_somm)
{
    bool select;
    int s =0;

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
                       return true;
                    }
                }
            }
                return true;
}

bool Mgraphe::connexe1(int i,int etat)
{
      m_arrete.find( std::to_string(i) ) -> second ->setCC(etat);
      return (*this).Verifier_connex();
}

bool Mgraphe::Verifier_connex()
{
    bool selec = false;
    int s = 0;
    for(const auto&it : m_sommet)
            {
                selec = it.second->verifier_connex();
                if(selec == true)
                {
                    return true;
                }
            }
            //std::cout<<"true/false "<<a<<std::endl;
            return false;
}




bool Mgraphe::increment(std::vector<bool> &vec_bin)
{
    int i = vec_bin.size() -1 ;
    int refe=0;
    int taille;
    int prec1,prec2;
    bool a = false;

    do
    {
        if( (vec_bin[i] == 0)&&(vec_bin[i+1] == 1) )
        {
            vec_bin[i] = 1;
            a = (*this).connexe1(vec_bin.size() -1 - i,1);

            vec_bin[i+1] = 0;
             a = (*this).connexe1(vec_bin.size() -1 - (i+1),0);
            if(refe == 1)
            {
                taille = vec_bin.size() -1 -(i+1);
                taille =taille/2;

                for(int j=0 ; j < taille ; j++)
                {
                    prec1 = vec_bin[i+2+j];
                    prec2 = vec_bin[ vec_bin.size() -1 -j];

                    vec_bin[i+2+j] = prec2;
                    a = (*this).connexe1(vec_bin.size() -1 - (i+2+j),prec2);

                    vec_bin[ vec_bin.size() -1 -j] = prec1;
                    a = (*this).connexe1(vec_bin.size() -1 - (vec_bin.size() -1 - j),prec1);
                }
                i= 1000;
            }

            i = 1000;

        }
        else if( (vec_bin[i] == 0)&&(i == vec_bin.size() -1) )
        {
            refe = 1;
            i--;
        }
        else
        {
            i--;
        }
    }
    while(i < 1000);

return a;
}

void Mgraphe::departcpt(std::vector<bool>&vec_bin)
{
    int i = vec_bin.size() -1 ;
    int nb = 0;

    while(nb != m_sommet.size() -1)
    {
        vec_bin[i] = 1;
        (*this).connexe1(vec_bin.size() -1 -i ,1);
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

void Mgraphe::trouverSolution()
{
    std::vector<bool> vect_bin;
    bool a = false;
    std::vector<bool> vect_bina;
    vect_bina.resize(m_arrete.size() );

    for(size_t i = 0 ; i < m_arrete.size() ; ++i)
    {
        vect_bin.push_back(0);
        (*this).connexe1(i,0);
    }

    std::string name;
    (*this).departcpt(vect_bin);
    (*this).arrivecpt(vect_bina);
    //afficherSolution(vect_bin);
    //afficherSolution(vect_bina);

    int i= 0;

    do
    {

        a = (*this).increment(vect_bin) ;
            if( a == false )
            {
                i++;
                //afficherSolution(vect_bin);
                name = "bf" + std::to_string(i);
                m_chemin.insert({name,vect_bin});
            }

        //}
    }
    while(vect_bin != vect_bina);
}

std::vector<bool> Mgraphe::kruskal(std::string fichier, std::string fichier2)
{
    int test;

    do {
        std::cout << "Quel kruskal vous souhaitez faire tourner ? "<< std::endl;
        std::cin >> test;

    }while ( test < 1 || test > 2);

    Mgraphe main{fichier, fichier2};

    Arrete* arret;
    bool select;
    int s = 0;
    int cc1, cc2;

    std::map<std::string, Arrete*> map_arrete;
    std::vector<Arrete*> vect_arretes;
    std::string somm1, somm2;
    std::string name;

    Sommet* Soomet1, *Soomet2;

    std::vector<bool> vect_bin;
    vect_bin.resize(m_arrete.size() );

    map_arrete = main.getMapArret();

    for (const auto &a : m_arrete)
    {
        vect_arretes.push_back(a.second);
    }

    if (test == 1)
    {
        std::sort(vect_arretes.begin(), vect_arretes.end(), [](Arrete* s1, Arrete* s2)
        {
            return s1->getPoids(1) > s2->getPoids(1);
        });
        name = "k1";
    }
    else if(test == 2)
    {
        std::sort(vect_arretes.begin(), vect_arretes.end(), [](Arrete* s1, Arrete* s2)
        {
            return s1->getPoids(2) > s2->getPoids(2);
        });
        name = "k2";
    }

    while (vect_arretes.size() != 0)
    {

        arret = vect_arretes[vect_arretes.size()-1];

        for (const auto&it : m_sommet)
        {
            select = it.second->trouverArrete(arret);
            if(select == true )
            {
                s++;
                if(s == 1)
                {
                    somm1 = it.second->getID();
                    Soomet1 = main.getSommet(somm1);
                    cc1 = Soomet1->getCC();
                }
                if(s == 2)
                {
                    somm2 = it.second->getID();
                    Soomet2 = main.getSommet(somm2);
                    cc2 = Soomet2->getCC();
                }
            }
        }
        s = 0;
        if (cc1 != cc2 )
        {
            int id_arret = 0;
            id_arret = atoi((arret->getID()).c_str());
            vect_bin[m_arrete.size() - 1 - id_arret] = 1;
            main.changerTousCC(cc1, cc2);

        }
        vect_arretes.pop_back();
    }
    m_chemin.insert({name,vect_bin});
    return vect_bin;
}

void Mgraphe::changerTousCC(int Cd, int Ca)
{
    for ( auto &s : m_sommet)
    {
        if(s.second->getCC() == Ca)
        {
            s.second->setCC(Cd);
        }
    }
}

Sommet* Mgraphe::getSommet(std::string id)
{
    return m_sommet.find(id)->second;
}



