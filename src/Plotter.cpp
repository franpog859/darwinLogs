#include "Plotter.hpp"
#include "../lib/gnuplot-iostream.h"

void Plotter::saveGraphs(std::vector<Info> *info, Parameters *parameters) {
    Gnuplot gp;

    gp << "set terminal png\n";
    gp << "set output 'my_graph_1.png'\n";

    std::vector<std::pair<double, double> > xy_pts_A;
    for(double x=-2; x<2; x+=0.01) {
        double y = x*x*x;
        xy_pts_A.push_back(std::make_pair(x, y));
    }

    gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
    gp << "plot" << gp.file1d(xy_pts_A) << "with lines title 'cubic'" << std::endl;
}