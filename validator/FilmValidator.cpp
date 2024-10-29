//
// Created by user on 4/3/2024.
//

#include <stdexcept>
#include <vector>
#include "FilmValidator.h"
#include "../exceptions/FilmValidatorException.h"

using std::vector;

void FilmValidator::validateFilm(const Film &film) {
    vector<string> msgs;
    if (film.getTitle().empty()) {
        msgs.emplace_back("Title cannot be empty!");
    }
    if (film.getGenre().empty()) {
        msgs.emplace_back("Genre cannot be empty!");
    }
    if (film.getYearOfRelease() < 1900 || film.getYearOfRelease() > 2024) {
        msgs.emplace_back("Year of release is invalid!");
    }
    if (film.getPrincipalActor().empty()) {
        msgs.emplace_back("Principal actor cannot be empty!");
    }
    if (film.getTitle().size() > 100) {
        msgs.emplace_back("Title is too long!");
    }
    if (film.getGenre().size() > 100) {
        msgs.emplace_back("Genre is too long!");
    }
    if (film.getPrincipalActor().size() > 100) {
        msgs.emplace_back("Principal actor is too long!");
    }
    if (!msgs.empty()) {
        string msg;
        for (const auto &m : msgs) {
            msg += m + '\n';
        }
        throw FilmValidatorException(msg.c_str());
    }
}
