#include "Plotter.hpp"
#include "Exceptions.hpp"
#include "../lib/gnuplot-iostream.h"

void Plotter::saveGraphs(std::vector<Info> *info, Parameters *parameters) {
    try {
        std::string outputPath = parameters->outputFilesPath;
		std::cout << "Saving graphs to " << outputPath << " directory" << std::endl;

        saveAverageDexterityAndMinimumSurvivalDexterity(info, &outputPath);
        saveSexNumberDifferenceAndCouplesSexuality(info, &outputPath);
        savePeopleNumber(info, &outputPath);
        saveEldersBoom(info, &outputPath);
		std::cout << "Graphs saved successfully!" << std::endl;
    }
    catch (std::exception &e) {
		std::cerr << "Error occured: " << e.what() << std::endl;
        throw SaveGraphsException();
    }

}

void Plotter::saveAverageDexterityAndMinimumSurvivalDexterity(std::vector<Info> *info, const std::string *outputPath) {
    Gnuplot gp;
    gp << "set terminal png\n";
    gp << "set output '" + *outputPath + "correlation-dexterity.png'\n"; //TODO: Create file name before gp << "set output..."

    std::vector<std::pair<int, int>> xy_average_dexterity;
    for(int i = 0; i < info->size(); i++) {
        xy_average_dexterity.push_back(std::make_pair(i, info->at(i).averageStatistics.dexterity));
    }

    std::vector<std::pair<int, int>> xy_minimal_survival_dexterity;
    for(int i = 0; i < info->size(); i++) {
        xy_minimal_survival_dexterity.push_back(std::make_pair(i, info->at(i).minimalSurvivalStatistics.dexterity));
    }

    gp << "set title 'Correlation of attributes'\n";
    gp << "set xlabel 'Epoch number'\n";
    gp << "set ylabel 'Attribute value'\n";
    gp << "set grid\n";
    gp << "plot '-' with lines title 'average dexterity', ";
	gp << "'-' with lines title 'minimal dexterity to survive'\n";
	gp.send1d(xy_average_dexterity);
	gp.send1d(xy_minimal_survival_dexterity);
}

void Plotter::saveSexNumberDifferenceAndCouplesSexuality(std::vector<Info> *info, const std::string *outputPath) {
    Gnuplot gp;
    gp << "set terminal png\n";
    gp << "set output '" + *outputPath + "correlation-sex-and-couples.png'\n";

    std::vector<std::pair<int, int>> xy_sex_and_couples_difference;
    for(int i = 1; i < info->size(); i++) {
        int sex_number_difference = info->at(i).maleAdultNumber - info->at(i).femaleAdultNumber; 
        sex_number_difference = (sex_number_difference >= 0) ? sex_number_difference : sex_number_difference * -1;

        int couple_sexuality_difference = info->at(i).homoCouplesNumber - info->at(i).straightCouplesNumber;

        xy_sex_and_couples_difference.push_back(std::make_pair(couple_sexuality_difference, sex_number_difference));
    }

    gp << "set title 'Sex difference'\n";
    gp << "set xlabel 'How many more homosexual couples there are'\n";
    gp << "set ylabel 'Difference in number of adults of a given sex'\n";
    gp << "plot '-' with points title 'correlation of sex difference and pairing'\n";
	gp.send1d(xy_sex_and_couples_difference);
}

void Plotter::savePeopleNumber(std::vector<Info> *info, const std::string *outputPath) {
    Gnuplot gp;
    gp << "set terminal png\n";
    gp << "set output '" + *outputPath + "people-number.png'\n";

    std::vector<std::pair<int, int>> xy_people_number;
    for(int i = 1; i < info->size(); i++) {
        int people_number = info->at(i).maleNumber + info->at(i).femaleNumber;
        xy_people_number.push_back(std::make_pair(i, people_number));
    }

    gp << "set title 'People number'\n";
    gp << "set xlabel 'Epoch number'\n";
    gp << "set ylabel 'People number'\n";
    gp << "set grid\n";
    gp << "plot '-' with lines title 'people number'\n";
	gp.send1d(xy_people_number); 
}

void Plotter::saveEldersBoom(std::vector<Info> *info, const std::string *outputPath) {
    Gnuplot gp;
    gp << "set terminal png\n";
    gp << "set output '" + *outputPath + "correlation-elders-dexterity.png'\n";

    std::vector<std::pair<int, int>> xy_average_dexterity;
    for(int i = 0; i < info->size(); i++) {
        xy_average_dexterity.push_back(std::make_pair(i, info->at(i).minimalSurvivalStatistics.dexterity));
    }
    std::vector<std::pair<int, int>> xy_average_intelligence;
    for(int i = 0; i < info->size(); i++) {
        xy_average_intelligence.push_back(std::make_pair(i, info->at(i).minimalSurvivalStatistics.intelligence));
    }
    std::vector<std::pair<int, int>> xy_average_strength;
    for(int i = 0; i < info->size(); i++) {
        xy_average_strength.push_back(std::make_pair(i, info->at(i).minimalSurvivalStatistics.strength));
    }

    std::vector<std::pair<int, double>> xy_elders;
    for(int i = 0; i < info->size(); i++) {
        double relative_elders = (double)(info->at(i).eldersNumber) / (double)(info->at(i).maleNumber + info->at(i).femaleNumber);
        double relative_elders_percent = relative_elders * 100;
        xy_elders.push_back(std::make_pair(i, relative_elders_percent));
    }

    gp << "set title 'Elders share in the population'\n";
    gp << "set xlabel 'Epoch number'\n";
    gp << "set y2tics nomirror\n";
    gp << "set y2label 'Attributes value'\n";
    gp << "set ytics nomirror\n";
    gp << "set ylabel 'Elders share in the population'\n";
    gp << "set termoption enhanced\n";
    gp << "set format y '%.0f%%'\n";
    gp << "set grid\n";
    gp << "plot '-' with lines title 'minimal dexterity to survive' axis x1y2, ";
	gp << "'-' with lines title 'minimal intelligence to survive' axis x1y2, ";
	gp << "'-' with lines title 'minimal strength to survive' axis x1y2, ";
	gp << "'-' with lines title 'elders number'\n";
	gp.send1d(xy_average_dexterity);
	gp.send1d(xy_average_intelligence);
	gp.send1d(xy_average_strength);
	gp.send1d(xy_elders);

}

/* TODO:
* różnica ilości śmierci i poprzedniej do różnicy minimalnej cechy do przeżycia
* różnica ilości narodzin i poprzedniej do różnicy minimalnej cechy do reprodukcji
*/