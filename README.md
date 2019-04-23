# DarwinLogs

[![CircleCI](https://circleci.com/gh/franpog859/darwinLogs.svg?style=shield)](https://circleci.com/gh/franpog859/darwinLogs)

**WIP** - DarwinLogs is a simple population evolution simulator. A given start population goes through a number of generations. After all changes it returns statistics of all generations. This is a second version of [Project Darwin](https://github.com/franpog859/darwin).

User provides environment and population in JSON files. After all program returns information also in JSON file. It is important for further web layer implementation.

## Main assumptions

- Input and output data is provided in JSON format. It will make web layer implementation easier
- All program behavior issues are logged to standard output. It will make easier process of finding problems with correctly working program
- Output file is provided in the array format. It will make iterative processes of creating output graphs easier

## Used outsource libraries

- [argh](https://github.com/adishavit/argh) - flags parsing
- [progress-cpp](https://github.com/prakhar1989/progress-cpp) - progress bar showing
- [json](https://github.com/nlohmann/json) - JSON format manipulation
- [CRT](https://docs.microsoft.com/pl-pl/visualstudio/debugger/finding-memory-leaks-using-the-crt-library) - memory leaks detecting (only for Windows development)

First three libraries are included locally so there will be no problems with dependencies. `CRT` library is used only for developing purposes with Windows system. If you do not develop it on Windows or create production binary just comment marked lines in `src/main.cpp` file.

## Usage

Make sure you have marked lines in `src/main.cpp` file commented. To build the program run:

```sh
cmake .
make
```

Program prints help if run with incorrect flags. You can also print it using `-h` flag. Input files format is coherent with `data/pop.json` and `data/env.json` files used for manual testing. First of them provides input population and the second input environment.

## Further implementation

- [ ] Add `const` word in all functions which do not change its objects and for all arguments that are pointers and should not be changed in the function
- [ ] Add move and copy `=` operators and move and copy constructor for all classes
- [ ] Fix minor issues marked in code with `// TODO:` comments
- [ ] Add unit and acceptance tests
- [ ] Extend output data with average person statistics in all ages and environment in the epoch
- [ ] Connect input files and add output file with output population and environment for further evolution continuation
- [ ] Optimize drawing algorithm for creating couples
- [ ] Make children statistics depend on their parents ability to survive
- [ ] Make number of children depend on the adaptation to the environment of the couple
- [ ] Save output files regularly to prevent unchecked memory growth
- [ ] Extend output data with number of children births, number of orphans, number of dead children, heterosexual couples, homosexual couples, dead elders, dead adults, number of ultra elders, number of people, average man statistics, average woman statistics
- [ ] Extend world with random events such as drastic climate change, god birth, pandemic, Noah Ark
- [ ] Create simple REST service which gets input data and respond with output data
- [ ] Create simple WEB UI using service API, creating input data and showing response with graphs
- [ ] Containerize service and deploy it in test environment
