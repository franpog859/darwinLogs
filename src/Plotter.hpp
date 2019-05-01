#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <vector>
#include <string>
#include "Info.hpp"
#include "Parameters.hpp"

class Plotter {
public:
    static void saveGraphs(std::vector<Info> *info, Parameters *parameters);

private:
    static void saveAverageDexterityAndMinimumSurvivalDexterity(std::vector<Info> *info, const std::string *outputPath);
    static void saveSexNumberDifferenceAndCouplesSexuality(std::vector<Info> *info, const std::string *outputPath);
    static void savePeopleNumber(std::vector<Info> *info, const std::string *outputPath);
    static void saveEldersBoom(std::vector<Info> *info, const std::string *outputPath);

};

#endif
