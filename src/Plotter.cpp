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

    gp << "plot '-' with lines title 'average dexterity', ";
	gp << "'-' with lines title 'minimal survival dexterity'\n";
	gp.send1d(xy_average_dexterity);
	gp.send1d(xy_minimal_survival_dexterity);
}

void Plotter::saveSexNumberDifferenceAndCouplesSexuality(std::vector<Info> *info, const std::string *outputPath) {
    Gnuplot gp;
    gp << "set terminal png\n";
    gp << "set output '" + *outputPath + "correlation-sex-and-couples.png'\n";

    std::vector<std::pair<int, int>> xy_sex_and_couples_difference;
    for(int i = 1; i < info->size(); i++) {
        int sex_number_difference = info->at(i).maleNumber - info->at(i).femaleNumber;
        sex_number_difference = (sex_number_difference >= 0) ? sex_number_difference : sex_number_difference * -1;

        int couple_sexuality_difference = info->at(i-1).homoCouplesNumber - info->at(i-1).straightCouplesNumber;

        xy_sex_and_couples_difference.push_back(std::make_pair(couple_sexuality_difference, sex_number_difference));
    }

    gp << "set title 'Sex difference'\n";
    gp << "set xlabel 'homosexual couples - heterosexual couples'\n";
    gp << "set ylabel '|male number - female number|'\n";
    gp << "plot '-' with points title 'sex difference'\n";
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
    gp << "set xlabel 'epoch'\n";
    gp << "set ylabel 'people number'\n";
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
        xy_elders.push_back(std::make_pair(i, relative_elders));
    }

    gp << "set y2tics nomirror\n";
    gp << "set ytics nomirror\n";
    gp << "plot '-' with lines title 'average dexterity' axis x1y2, ";
	gp << "'-' with lines title 'average intelligence' axis x1y2, ";
	gp << "'-' with lines title 'average strength' axis x1y2, ";
	gp << "'-' with lines title 'elders number'\n";
	gp.send1d(xy_average_dexterity);
	gp.send1d(xy_average_intelligence);
	gp.send1d(xy_average_strength);
	gp.send1d(xy_elders);

}
/* TODO:
* różnica ilości śmierci i poprzedniej do różnicy minimalnej cechy do przeżycia
* różnica ilości narodzin i poprzedniej do różnicy minimalnej cechy do reprodukcji
* ilość starców i minimalna cecha do przeżycia (dla bardzo małej cechy ilość starców bardzo szybko rośnie)
*/