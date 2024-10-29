//
// Created by user on 4/17/2024.
//

#ifndef POO_LAB_6_7_FILMSERVICEEXCEPTION_H
#define POO_LAB_6_7_FILMSERVICEEXCEPTION_H

#include <exception>

class FilmServiceException : public std::exception {

private:
    const char* message;

public:
    explicit FilmServiceException(const char* message) : message(message) {}

    string getErrorMessage() {
        string s(message);
        return s;
    }
};

#endif //POO_LAB_6_7_FILMSERVICEEXCEPTION_H
