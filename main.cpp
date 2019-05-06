#include <iostream>
#include "MGraphe.h"

int main()
{
    bool booleen;
    while(true)
    {
        std::string nom;
        size_t choix = 0;

        std::cout << "Veuillez saisir une ville : ";
        std::cin >> nom;

        std::string fichier = "files/" + nom + ".txt";
        std::string fichier1 = "files/" + nom + "_weights_0.txt";

        Mgraphe g{fichier, fichier1};

        do
        {
            std::cout << "Voulez vous afficher toutes les solutions (1) ou des solutions plus optimales (2) ? : ";
            std::cin >> choix;
            if(choix != 1 && choix != 2)
            {
                std::cout << "ERROR" << std::endl;
            }
        }
        while(choix != 1 && choix != 2);

        if(choix == 1)
        {
            g.trouvertouteSoluce();
        }
        else
        {
            g.trouverSolucemin();
        }
        g.kruskal(fichier, fichier1, 1);
        g.kruskal(fichier, fichier1, 2);
        g.dijktra();
        g.afficherGraphique();
        system("start graphique.svg");

        do
        {
            std::string indice;
            std::cout<<"Entrez l'indice du graphe a afficher dans \"graphe.svg\" (ex: \"bf2\", pour le 2e graphe bruteforce ou \"k1\" et \"k2\" pour les kruskal du poids 1 ou 2) : ";
            std::cin>>indice;
            booleen = g.afficherGraph(indice);
        }
        while(!booleen);
        system("start graphe.svg");
        system("cls");
    }

    return 0;
}
