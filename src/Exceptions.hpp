#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

// TODO: Add every needed exception here
class HelpException : public std::exception {
public:
    virtual const char * what() noexcept {
        return "Printing help triggered!";
    }
};

class InvalidEpochsParameterException : public HelpException {
public:
    const char * what() noexcept {
        return "You should provide valid epochs number!";
    }
};

class InvalidEnvironmentParameterException : public HelpException {
public:
    const char * what() noexcept {
        return "You should provide valid input file name for the environment!";
    }
};

class InvalidPopulationParameterException : public HelpException {
public:
    const char * what() noexcept {
        return "You should provide valid input file name for the population!";
    }
};

class ReadException : public std::exception {
public:
    virtual const char * what() noexcept {
        return "Error occured  while reading the file!";
    }
};

class ReadEnvironmentException : public ReadException {
public:
    const char * what() noexcept {
        return "You should provide valid input file for the environment!";
    }
};

#endif