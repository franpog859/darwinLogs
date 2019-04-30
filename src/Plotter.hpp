#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <vector>
#include "Info.hpp"
#include "Parameters.hpp"

class Plotter {
public:
    static void saveGraphs(std::vector<Info> *info, Parameters *parameters);

};

#endif
