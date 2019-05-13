# DarwinLogs

[![CircleCI](https://circleci.com/gh/franpog859/darwinLogs.svg?style=shield)](https://circleci.com/gh/franpog859/darwinLogs)

DarwinLogs is a simple population evolution simulator. A given start population goes through a number of generations. After all changes it returns statistics of all generations. This is a second version of [Project Darwin](https://github.com/franpog859/darwin).

User provides environment and population in JSON files. After all program returns plots with statistics data, output environment and population in JSON files which can be used as input data and all statistics in CSV file for further analysis.

## Main assumptions

- Input and output data is provided in JSON format. It will make web layer implementation easier and allow continuing population execution
- All program behavior issues are logged to standard output. It will make easier process of finding problems with correctly working program
- Output file is provided in the CSV format. It will make iterative processes of creating output graphs easier and allow easy fetching data in other programs

## Used outsource libraries

- [json](https://github.com/nlohmann/json) - JSON format manipulation
- [csvfile](https://gist.github.com/rudolfovich/f250900f1a833e715260a66c87369d15) - CSV format manipulation
- [argh](https://github.com/adishavit/argh) - flags parsing
- [progress-cpp](https://github.com/prakhar1989/progress-cpp) - progress bar showing
- [gnuplot](http://www.gnuplot.info/) - plotter
- [gnuplot-iostream](https://github.com/dstahlke/gnuplot-iostream) - Gnuplot facade for plotting graphs
- [libboost-all-dev](https://packages.debian.org/pl/sid/libboost-all-dev) - package used to connecto to plotter
- [valgrind](http://valgrind.org/) - checking memory leaks

To install Gnuplot, Boost and Valgrind run:

```sh
sudo apt-get update
sudo apt-get install -y gnuplot
sudo apt-get install -y libboost-all-dev
sudo apt-get install -y valgrind
```

Valgrind is not required for DarwinLogs usage. It is used in the development process to check memory leaks. Other libraries are imported locally so you do not need to bother.

## Usage

```sh
cmake .
make
./darwinLogs
```

Program prints help if run with incorrect flags. You can also print it using `-h` flag. Input files format is coherent with `data/pop.json` and `data/env.json` files used for manual testing. First of them provides input population and the second input environment.

## Development

To clone the repository run:

```sh
git clone https://github.com/franpog859/darwinLogs.git
```

If you are Ubuntu (or other Linux distro) user you can run `test.sh` script which builds, compiles and runs the program with memory leaks check.

## Plots examples

**TODO**