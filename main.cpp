#include <iostream>
#include "MGraphe.h"
#include "svgfile.h"

int main()
{
    Svgfile svgout;
    std::string fichier = "files/manhattan.txt";
    std::string fichier1 = "files/manhattan_weights_0.txt";
    Mgraphe g{fichier, fichier1};

    //g.afficher();
    g.trouverSolution();
    //g.afficherGraph(svgout);

    return 0;
}
