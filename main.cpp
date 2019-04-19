#include <iostream>
#include "MGraphe.h"
#include "svgfile.h"

int main()
{
    Svgfile svgout;
    std::string fichier = "files/cubetown.txt";
    std::string fichier1 = "files/cubetown_weights_0.txt";
    Mgraphe g{fichier, fichier1};

    g.afficher();

    g.afficherGraph();

    std::cout << "Projet Manhattan" << std::endl;
    return 0;
}
