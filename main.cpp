#include <iostream>
#include "MGraphe.h"
#include "svgfile.h"

int main()
{
    std::string fichier = "files/broadway.txt";
    std::string fichier1 = "files/broadway_weights_0.txt";
    Mgraphe g{fichier, fichier1};

    //g.afficher();
    g.trouverSolution();
    //g.afficherGraph();

    //g.dijktra();

    g.afficherGraphique();

    system("start graphique.svg");
    //system("start graphe.svg");

    return 0;
}
