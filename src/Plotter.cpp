#include "Plotter.hpp"
#include "../lib/gnuplot-iostream.h"

void Plotter::saveGraphs(std::vector<Info> *info, Parameters *parameters) {
    Gnuplot gp;
    gp << "set terminal png\n";

    gp << "set output 'corelation-dexterity.png'\n";
    std::vector<std::pair<int, int>> xy_avarage_dexterity;
    for(int i = 0; i < info->size(); i++) {
        xy_avarage_dexterity.push_back(std::make_pair(i, info->at(i).averageStatistics.dexterity));
    }

    std::vector<std::pair<int, int>> xy_minimal_survival_dexterity;
    for(int i = 0; i < info->size(); i++) {
        xy_minimal_survival_dexterity.push_back(std::make_pair(i, info->at(i).minimalSurvivalStatistics.dexterity));
    }

    gp << "plot '-' with lines title 'avarage dexterity', ";
	gp << "'-' with lines title 'minimal survival dexterity'\n";
	gp.send1d(xy_avarage_dexterity);
	gp.send1d(xy_minimal_survival_dexterity);
}