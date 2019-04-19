#include <iostream>
#include "MGraphe.h"
#include "svgfile.h"

int main()
{
    std::string fichier = "files/manhattan.txt";
    std::string fichier1 = "files/manhattan_weights_0.txt";
    Mgraphe g{fichier, fichier1};

    //g.afficher();
    g.trouverSolution();
    g.afficherGraph();

    g.afficherGraphique();

    system("start graphique.svg");
    //system("start graphe.svg");

    return 0;
}
