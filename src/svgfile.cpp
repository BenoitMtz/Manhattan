#include "../svgfile.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

bool Svgfile::s_verbose = true;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    if (s_verbose)
        std::cout << "Opening SVG output file : "
                  << m_filename << std::endl;

    if (s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    if (s_verbose)
        std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";

    if(m_filename == "graphique.svg")
    {
        addGrid(10, 0, "lightgrey");
        addLine(50, 50, 50, 500, "black");
        addLine(50, 500, 500, 500, "black");
        addTriangle(50-5, 50,
                    50+5, 50,
                    50, 50-10,
                     "black");
        addTriangle(500, 500+5,
                    500, 500-5,
                    500+10, 500,
                     "black");
    }
}

Svgfile::~Svgfile()
{
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
void Svgfile::addEllipseAnimate(double x, double y , double r ,std::string color, std::string color1,int grad)
{
    double coeff = r/50;
    m_ostrm <<"<linearGradient id=\"grad"<<grad<<"\" x1=\"0%\" y1=\"0%\" x2=\"100%\" y2=\"0%\"><stop offset=\"0%\" style=\"stop-color:"
    <<color<<";stop-opacity:1\" />\n<stop offset=\"100%\" style=\"stop-color:"
    <<color1<<";stop-opacity:1\" />\n</linearGradient>\n<g transform=\" matrix("
    <<coeff<<", -0.5, 0.25, 0.433,"<<x<<","
    <<y<<")\">\n<path d=\"M 0,70 A 65,70 0 0,0 65,0 5,5 0 0,1 75,0 75,70 0 0,1 0,70Z\" fill=\"#FFF\">\n<animateTransform attributeName=\"transform\" type=\"rotate\" from=\"360 0 0\" to=\"0 0 0\" dur=\"2s\" repeatCount=\"indefinite\" />\n</path>\n</g>\n<path d=\"M 50,0 A 50,50 0 0,0 -50,0Z\" transform=\"matrix("
    <<coeff-0.1<<", -0.5, 0.5, "<<coeff-0.1<<", "<<x<<","<<y<<")\" fill=\"url(#grad"<<grad<<")\" />";
}
void Svgfile::addPolygon(int x1, int y1, int x2, int y2 ,int x3, int y3, int x4, int y4,std::string color)
{
    std::string color1 = "black";
   /* m_ostrm <<"<linearGradient id=\"grad"<<grad<<"\" x1=\"0%\" y1=\"0%\" x2=\"100%\" y2=\"0%\"><stop offset=\"0%\" style=\"stop-color:"<<color<<";stop-opacity:1\" />\n<stop offset=\"100%\" style=\"stop-color:"<<color1<<";stop-opacity:1\" />\n</linearGradient>\n<polygon points=\" "
    <<x1<<","<<y1<<","<<x2<<","<<y2<<","<<x3<<","<<y3<<","<<x4<<","<<y4<<"\" style=\"fill:url(#grad"<<grad<<");stroke:none\" />";*/
    m_ostrm <<"<polygon points=\" "
    <<x1<<","<<y1<<","<<x2<<","<<y2<<","<<x3<<","<<y3<<","<<x4<<","<<y4<<"\" style=\"fill:"<<color<<";stroke:black\" />";
}


void Svgfile::addDisk(double x, double y, double r, std::string color)
{
     /*m_ostrm  <<"<defs>\n"
    <<"<radialGradient id="<<"grad1" <<"cx="<<"50%" <<"cy="<<"50%" <<"r="<<"50%"<<"fx="<<"50%" <<"fy="<<"50%"<<">\n"
    <<"<stop offset="<<"0%" <<"style="<<"stop-color:rgb(255,255,255);stop-opacity:0" <<"/>\n"
    <<"<stop offset="<<"100%" <<"style="<<"stop-color:rgb(0,0,255);stop-opacity:1" <<"/>\n"
    <<"</radialGradient>\n"
    <<"</defs>\n"
    <<"<ellipse cx="<<"200" <<"cy="<<"70" <<"rx="<<"85" <<"ry="<<"55" <<"fill="<<"url(#grad1)"<<" />\n";*/

    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";

}

void Svgfile::addDiskC(double x, double y, double r,std::string color,std::string color1,int grad)
{
    m_ostrm <<"<linearGradient id=\"grad"<<grad<<"\" x1=\"0%\" y1=\"0%\" x2=\"100%\" y2=\"0%\"><stop offset=\"0%\" style=\"stop-color:"<<color<<";stop-opacity:1\" />\n<stop offset=\"100%\" style=\"stop-color:"<<color1<<";stop-opacity:1\" />\n</linearGradient>\n<circle cx=\" "
    <<x<<"\" cy=\" "<<y<<"\" r=\" "<<r<<"\" fill=\"url(#grad"<<grad<<")\" />\n";

}

void Svgfile::addEllipse(double cx, double cy, double rx,double ry,double angle,double transx,double transy,std::string color)
{

   /* m_ostrm <<"<ellipse "
           << attrib("cx", cx)
            << attrib("cy", cy)
            << attrib("rx", rx)
            <<attrib("ry",  ry)
            << attrib("fill", color )
            <<attrib("transform", "rotate(-30,400,200)")
            << "/>\n";*/
if(color=="rgb(255,0,0)")
m_ostrm<<"<linearGradient id=\"lave\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n<stop offset=\"0\" stop-color=\"#FF0000\">\n</stop>\n<stop offset=\"0.25\" stop-color=\"#FFFF00\">\n<animate attributeName=\"offset\" dur=\"5s\" values=\"0;1\" repeatCount=\"indefinite\" />\n</stop>\n<stop offset=\"1\" stop-color=\"#FF0000\"/> \n</linearGradient>\n<ellipse cx=\" "<<cx<<"\" cy=\" "<<cy<<"\"  rx=\" "<<rx<<"\"  ry=\" "<<ry<<"\" stroke=\"black\" stroke-width=\"1\" fill=\"url(#lave)\" transform=\"rotate("<<angle<<" "<<transx<<" "<<transy<<")\" />";
else
   m_ostrm << "<ellipse cx=\" "<<cx<<"\" cy=\" "<<cy<<"\" rx=\" "<<rx<<"\" ry=\" "<<ry<<"\" style=\"fill:"<<color<<"\" transform=\"rotate("<<angle<<" "<<transx<<" "<<transy<<")\" />\n";



}

void Svgfile::addEllipseC(double c_x,double c_y,double r_x,double r_y,double angle,double transx,double transy,std::string color,int grad)
{

    //m_ostrm <<"<radialGradient id=\"grad1\" cx=\"50%\" cy=\"30%\" r=\"45%\" fx=\"50%\" fy=\"50%\"><stop offset=\"0%\" style=\"stop-color:rgb(255,255,255);stop-opacity:0\" /><stop offset=\"100%\" style=\"stop-color:rgb(150,150,150);stop-opacity:1\" /></radialGradient></defs>"
    /*m_ostrm  <<"<ellipse"
           << attrib("cx", c_x)
            << attrib("cy", c_y)
            << attrib("rx", r_x)
            <<attrib("ry",  r_y)
            << attrib("fill",  "none")
            <<attrib("stroke", "black")
            << "/>\n";*/

m_ostrm <<"<radialGradient id=\"grad"<<grad<<"\" cx=\"20%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"30%\">\n<stop offset=\"0%\" style=\"stop-color:rgb(255,255,255);stop-opacity:0\" />\n<stop offset=\"100%\" style=\"stop-color:"<<color<<";stop-opacity:1\" />\n</radialGradient>\n<ellipse cx=\" "<<c_x<<"\" cy=\" "<<c_y<<"\"  rx=\" "<<r_x<<"\"  ry=\" "<<r_y<<"\" stroke=\"black\" stroke-width=\"1\" fill=\"url(#grad"<<grad<<")\" transform=\"rotate("<<angle<<" "<<transx<<" "<<transy<<")\" />";
//m_ostrm <<"<radialGradient id=\"grad"<<grad<<"\" cx=\"50%\" cy=\"30%\" r=\"45%\" fx=\"50%\" fy=\"50%\">\n<stop offset=\"0%\" style=\"stop-color:rgb(255,255,255);stop-opacity:0\" />\n<stop offset=\"100%\" style=\"stop-color:rgb(150,150,150);stop-opacity:1\" />\n</radialGradient>\n<ellipse cx=\" "<<c_x<<"\" cy=\" "<<c_y<<"\"  rx=\" "<<r_x<<"\"  ry=\" "<<r_y<<"\" fill=\"url(#grad"<<grad<<")\" />";
//\n<ellipse cx=\" "<<c_x<<"\" cy=\" "<<c_y-20<<"\"  rx=\" "<<0.8*r_x<<"\"  ry=\" "<<0.75*r_y<<"\" style=\"fill:black;stroke:none;stroke-width:2\" />\n<ellipse cx=\" "<<c_x<<"\" cy=\" "<<c_y-15<<"\"  rx=\" "<<0.75*r_x<<"\"  ry=\" "<<0.625*r_y<<"\" fill=\"grey\" />";
}

void Svgfile::addCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
    m_ostrm << "<linearGradient id=\"lave\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n<stop offset=\"0\" stop-color=\"#FF0000\">\n</stop>\n<stop offset=\"0.25\" stop-color=\"#FFFF00\">\n<animate attributeName=\"offset\" dur=\"5s\" values=\"0;1\" repeatCount=\"indefinite\" />\n</stop>\n<stop offset=\"1\" stop-color=\"#FF0000\"/> \n</linearGradient>\n<polygon points=\"485,500 440,525 500,555\" style=\"fill:url(#lave);stroke:none;stroke-width:1\" />\n<polygon points=\"485,500 450,525 500,550\" style=\"fill:dimgrey;stroke:none;stroke-width:3\" />\n<polyline points=\"499,551 430,575 530,620\" style=\"fill:rgba(255,255,255,.01);stroke:url(#lave);stroke-width:5\" />\n<polyline points=\"533,623 400,666 570,730\" style=\"fill:rgba(255,255,255,.01);stroke:url(#lave);stroke-width:11\" />\n<polyline points=\"575,732 350,820 630,930\" style=\"fill:rgba(255,255,255,.01);stroke:url(#lave);stroke-width:15\" />\n<polyline points=\"637,933 300,1100 580,1500\" style=\"fill:grey;stroke:url(#lave);stroke-width:24\" />\n";
}

/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />
void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}


void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
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
        if (numbering)
            addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        if (numbering)
            addText(x+5, 15, x, color);
        x+=span;
    }
}

void Svgfile::addfond()
{
     m_ostrm << "<rect "
            << attrib("x", 0)
            << attrib("y", 0)
            << attrib("width", 1000)
            << attrib("height", 900)
            << attrib("style", "fill::black")
            <<"/>\n";

}

std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}
