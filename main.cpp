#include <iostream>
#include "MGraphe.h"
#include "svgfile.h"

int main()
{
    std::string fichier = "files/cubetown.txt";
    std::string fichier1 = "files/cubetown_weights_0.txt";
    Mgraphe g{fichier, fichier1};
    std::vector<bool> test;


    //g.afficher();
    g.trouverSolution();
    test = g.kruskal(fichier, fichier1);
    for(size_t i = 0  ; i < test.size() ; i++)
    {
        std::cout<<test[i]<<" ";
    }
    std::cout<<" "<<std::endl;
    g.afficherGraph();

    g.afficherGraphique();

    //system("start graphique.svg");
    //system("start graphe.svg");

    return 0;
}
