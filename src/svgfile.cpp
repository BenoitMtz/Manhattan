#include "svgfile.h"
#include "interfaceSB.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\"  xmlns:xlink=\"http://www.w3.org/1999/xlink\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    std::cout << "Opening SVG output file : "
              << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\" viewBox=\"0 0 2000 2000\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the gradients into the SVG file
    m_ostrm << svgBallGradients;

    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);
    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}
std::string attrib(std::string name, std::string commande )
{
    std::ostringstream oss;
    oss << name << "=\"" << commande << "\" ";
    return oss.str();
}
std::string attrib(std::string name, double x ,double y,double tourne )
{
    int rayon= (x-1000);
    if (tourne==1)
        rayon =0;
    std::ostringstream oss;
    oss << name << "=\"" << "M"<< " " << x <<" " << y <<" "<<"a"<< " "<< rayon <<" "<< rayon << " 0 0 0 " << -(2*rayon )<<" "<< "0 "<<" "<<"a" <<rayon <<" " <<rayon <<" 0 0 0 " <<(2*rayon)<<" "<< "0 Z" <<"\"" ;
    return oss.str();
}
std::string attrib(std::string name,std::string champs, std::string nom ,std::string champs2 )
{
    std::ostringstream oss;
    oss << name << "=\""<<champs <<champs2<<nom<<"\" " ;
    return oss.str();
}
std::string attrib(std::string name, std::string nom,std::string champs )
{
    std::ostringstream oss;
    oss << name << "=\""<<champs<<nom<<"\" " ;
    return oss.str();
}
std::string attrib(std::string name,std::string champs, double x ,double y, std::string champs2)
{
    std::ostringstream oss;
    oss << name << "=\""<<champs<<-x<<","<<-y<<champs2<<"\"" ;
    return oss.str();
}

void Svgfile::addAnimatedDisk(double x, double y, double r, std::string color,std::string nom, bool tourne)
{
    m_ostrm << "<circle "
            <<attrib("id",nom)
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", fillBallColor(color) )
            <<attrib("transform","scale(-1,1)translate(",x,y,")")
            << "/>\n"
            <<"<path "
            <<attrib("id",nom,"motionPath")
            <<attrib("fill","none")
            <<attrib("stroke","black")
            <<attrib("d",x,y,tourne)
            << "/>\n"
            <<"<animateMotion "
            <<attrib("xlink:href",nom,"#")
            <<attrib("dur",(2*3.14*(x-1000))/pow(GM/(x-1000), 0.5)*33)
            <<attrib("begin","0s")
            <<attrib("fill","freeze")
            <<attrib("repeatCount","indefinite")
            <<attrib("rotate","auto")
            << ">\n"
            <<attrib("<mpath xlink:href","#",nom,"motionPath")
            << "/>\n"
            <<"</animateMotion >\n";
            addText(x,y,nom);
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << "/>\n";
}

void Svgfile::addCross(double x, double y, double span, std::string color)
{
    addLine(x-span, y-span, x+span, y+span, color);
    addLine(x-span, y+span, x+span, y-span, color);
}

void Svgfile::addText(double x, double y, std::string text, std::string color)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        addLine(0, y, m_width, y, color);
        addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        addText(x+5, 15, x, color);
        x+=span;
    }
}

std::string makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}

std::string fillBallColor(std::string col)
{
    if ( col.size()>4 && col.substr(col.size()-4) == "ball" )
        col =   "url(#" + col + ")";

    return col;
}

/// Effets "Boule en relief"
/// Horrible bricolage : ces données devraient soit être dans un fichier auxiliaire
/// ( c'était l'approche initiale qui marchait bien sur Firefox mais pas sur les autres )
/// soit générées dynamiquement en fonction des besoins (couleurs paramétrables...)
/// On fera mieux l'an prochain !
extern const std::string svgBallGradients =
"  \n\n<defs>\n"
"    <radialGradient id=\"redball\" cx=\"30%\" cy=\"30%\" r=\"100%\" fx=\"30%\" fy=\"30%\">\n"
"      <stop offset=\"0%\" style=\"stop-color:rgb(255,250,250)\" />\n"
"      <stop offset=\"3%\" style=\"stop-color:rgb(255,250,250)\" />\n"
"      <stop offset=\"7%\" style=\"stop-color:rgb(255,160,160)\" />\n"
"      <stop offset=\"70%\" style=\"stop-color:rgb(255,0,0)\" />\n"
"      <stop offset=\"100%\" style=\"stop-color:rgb(255,0,0)\" />\n"
"    </radialGradient>\n"
"    <radialGradient id=\"greenball\" cx=\"30%\" cy=\"30%\" r=\"100%\" fx=\"30%\" fy=\"30%\">\n"
"      <stop offset=\"0%\" style=\"stop-color:rgb(250,255,250)\" />\n"
"      <stop offset=\"3%\" style=\"stop-color:rgb(250,255,250)\" />\n"
"      <stop offset=\"7%\" style=\"stop-color:rgb(160,255,160)\" />\n"
"      <stop offset=\"70%\" style=\"stop-color:rgb(0,255,0)\" />\n"
"      <stop offset=\"100%\" style=\"stop-color:rgb(0,255,0)\" />\n"
"    </radialGradient>\n"
"    <radialGradient id=\"blueball\" cx=\"30%\" cy=\"30%\" r=\"100%\" fx=\"30%\" fy=\"30%\">\n"
"      <stop offset=\"0%\" style=\"stop-color:rgb(250,250,255)\" />\n"
"      <stop offset=\"3%\" style=\"stop-color:rgb(250,250,255)\" />\n"
"      <stop offset=\"7%\" style=\"stop-color:rgb(160,160,255)\" />\n"
"      <stop offset=\"70%\" style=\"stop-color:rgb(0,0,255)\" />\n"
"      <stop offset=\"100%\" style=\"stop-color:rgb(0,255,0)\" />\n"
"    </radialGradient>\n"
"    <radialGradient id=\"yellowball\" cx=\"30%\" cy=\"30%\" r=\"100%\" fx=\"30%\" fy=\"30%\">\n"
"      <stop offset=\"0%\" style=\"stop-color:rgb(255,255,250)\" />\n"
"      <stop offset=\"3%\" style=\"stop-color:rgb(255,255,250)\" />\n"
"      <stop offset=\"7%\" style=\"stop-color:rgb(255,255,160)\" />\n"
"      <stop offset=\"70%\" style=\"stop-color:rgb(255,255,0)\" />\n"
"      <stop offset=\"100%\" style=\"stop-color:rgb(255,255,0)\" />\n"
"    </radialGradient>\n"
"    <radialGradient id=\"greyball\" cx=\"30%\" cy=\"30%\" r=\"100%\" fx=\"30%\" fy=\"30%\">\n"
"      <stop offset=\"0%\" style=\"stop-color:rgb(250,250,250)\" />\n"
"      <stop offset=\"3%\" style=\"stop-color:rgb(250,250,250)\" />\n"
"      <stop offset=\"7%\" style=\"stop-color:rgb(160,160,160)\" />\n"
"      <stop offset=\"70%\" style=\"stop-color:rgb(100,100,100)\" />\n"
"      <stop offset=\"100%\" style=\"stop-color:rgb(100,100,100)\" />\n"
"    </radialGradient>\n"
"  </defs>\n";
