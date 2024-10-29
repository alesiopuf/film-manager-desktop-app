//
// Created by user on 4/2/2024.
//

#include <stdexcept>
#include <algorithm>
#include "FilmRepository.h"
#include "../exceptions/FilmRepositoryException.h"

void FilmRepository::saveFilm(const Film &film) {
    if (!existsFilm(film)) {
        database.push_back(film);
    } else {
        throw FilmRepositoryException("Film already exists!");
    }
}

const vector<Film>& FilmRepository::findAllFilms() noexcept {
    return database;
}

void FilmRepository::updateFilm(const Film &oldFilm, const Film &newFilm) {
    for (auto &film : database) {
        if (film == oldFilm) {
            film = newFilm;
            return;
        }
    }
    throw FilmRepositoryException("Film does not exist!");
}

void FilmRepository::deleteFilm(const Film &film) {
    for (auto it = database.begin(); it != database.end(); ++it) {
        if (*it == film) {
            database.erase(it);
            return;
        }
    }
    throw FilmRepositoryException("Film does not exist!");
}

bool FilmRepository::existsFilm(const Film &film) const noexcept {
    auto iterator = std::find_if(database.begin(), database.end(), [&film](const Film &f) -> bool {
        return f == film;
    });
    if (iterator == database.end()) {
        return false;
    }
    return true;
}

Film FilmRepository::getFilmByTitle(const string &title) const {
    auto iterator = std::find_if(database.begin(), database.end(), [&title](const Film &f) -> bool {
        return f.getTitle() == title;
    });
    if (iterator != database.end()) {
        return database[iterator - database.begin()];
    }
    throw FilmRepositoryException("Film does not exist!");
}

