﻿#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <set>

constexpr char defcol[] = "black";

class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=1000, int _height=800);
        ~Svgfile();
        void addEllipseAnimate(double x, double y , double r ,std::string color, std::string color1, int grad);
        void addPolygon(int x1, int y1, int x2, int y2 ,int x3, int y3, int x4, int y4,std::string color);
        void addDisk(double x, double y, double r, std::string color=defcol);
        void addDiskC(double x, double y, double r,std::string color,std::string color1,int grad);
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);
        void addEllipse(double cx, double cy, double rx,double ry,double angle,double transx,double transy,std::string color);
        void addEllipseC(double c_x,double c_y,double r_x,double r_y,double angle,double transx,double transy,std::string color,int grad);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");
        void addfond();

        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

        static bool s_verbose;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED
