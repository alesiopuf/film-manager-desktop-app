//
// Created by user on 4/17/2024.
//

#ifndef POO_LAB_6_7_FILMCONTAINERSERVICEEXCEPTION_H
#define POO_LAB_6_7_FILMCONTAINERSERVICEEXCEPTION_H

#include <exception>

class FilmContainerServiceException : public std::exception {

private:
    const char* message;

public:
    explicit FilmContainerServiceException(const char* message) : message(message) {}
};

#endif //POO_LAB_6_7_FILMCONTAINERSERVICEEXCEPTION_H
