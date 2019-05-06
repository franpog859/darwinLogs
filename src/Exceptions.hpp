#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

// TODO: Add every needed exception here
class HelpException : public std::exception {
public:
    const char * what() noexcept {
        return "Printing help triggered!";
    }
};

#endif