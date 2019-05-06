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

class ReadPopulationException : public ReadException {
public:
    const char * what() noexcept {
        return "You should provide valid input file for the population!";
    }
};

class EmptyFileException : public ReadException {
public:
    const char * what() noexcept {
        return "Input file is empty!";
    }
};

class NotArrayException : public ReadException {
public:
    const char * what() noexcept {
        return "Input file does not contain an array!";
    }
};

class SaveException : public std::exception {
public:
    virtual const char * what() noexcept {
        return "Error occured while saving the file!";
    }
};

class SaveLogsException : public SaveException {
public:
    const char * what() noexcept {
        return "Failed to save logs!";
    }
};

class SaveEnvironmentException : public SaveException {
public:
    const char * what() noexcept {
        return "Failed to save environment!";
    }
};

class SavePopulationException : public SaveException {
public:
    const char * what() noexcept {
        return "Failed to save population!";
    }
};

class SaveGraphsException : public SaveException {
public:
    const char * what() noexcept {
        return "Failed to save graphs!";
    }
};

class EmptyInfoException : public std::exception {
public:
    const char * what() noexcept {
        return "Info is empty, nothing to print!";
    }
};

#endif