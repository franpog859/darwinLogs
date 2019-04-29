#include "PopulationRepository.hpp"
#include "PopulationService.hpp"
#include "World.hpp"
#include "Parameters.hpp"
#include "Random.hpp"
#include "IoService.hpp"
#include "LogService.hpp"

#include <map>
#include <vector>
#include <cmath>

#include "../lib/gnuplot-iostream.h"

//#define _CRTDBG_MAP_ALLOC // Comment this if you are not debugging it on Windows.
//#include <stdlib.h> // Comment this if you are not debugging it on Windows.
//#include <crtdbg.h> // Comment this if you are not debugging it on Windows.

int main(int argc, char *argv[]) {
//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); // Comment this if you are not debugging it on Windows.

	Parameters params = IoService::parseArgs(argc, argv);
	if (!params.isHelp) {
		Random::initialize();

		Environment environment = IoService::readEnvironment(&params);
		PopulationRepository populationRepo = IoService::readPopulation(&params);
		PopulationService populationSvc(&populationRepo);

		World world(&environment, &params, &populationSvc);
		world.start();

		IoService::saveEnvironment(&environment, &params);
		IoService::savePopulation(&populationRepo, &params);
		std::vector<Info> logs = LogService::getLogs();
		IoService::saveLogs(&logs, &params); //TODO: This should save logs to CSV file.
		//IoService::generateGraphs(LogService::getLogs(), &params);
	}


	{
		Gnuplot gp;

		std::vector<std::pair<double, double> > xy_pts_A;
		for(double x=-2; x<2; x+=0.01) {
			double y = x*x*x;
			xy_pts_A.push_back(std::make_pair(x, y));
		}

		std::vector<std::pair<double, double> > xy_pts_B;
		for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
			double theta = alpha*2.0*3.14159;
			xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
		}

		gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
		// Data will be sent via a temporary file.  These are erased when you call
		// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
		// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
		// and won't be deleted (this is useful when creating a script).
		gp << "plot" << gp.file1d(xy_pts_A, "fileA.dat") << "with lines title 'cubic',"
			<< gp.file1d(xy_pts_B) << "with points title 'circle'" << std::endl;
	}
	return 0;
}
