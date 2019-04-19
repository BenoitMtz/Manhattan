#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <math.h>
#include <vector>

constexpr char defcol[] = "black";

class Svgfile
{
    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;
        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;

    public:
        void reset_i();
        Svgfile(std::string _filename = "output.svg", int _width=2000, int _height=2000);
        ~Svgfile();
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);
        void addAnimatedDisk(double x ,double y ,double r ,std::string color =defcol,std::string nom="null",bool tourne=1);
        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");
};

std::string makeRGB(int r, int g, int b);

std::string fillBallColor(std::string col);

#endif // SVGFILE_H_INCLUDED



