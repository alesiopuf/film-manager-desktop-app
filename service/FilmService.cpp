//
// Created by user on 4/2/2024.
//
#include <algorithm>
#include <stdexcept>

#include "FilmService.h"
#include "../exceptions/FilmServiceException.h"

using std::sort;

FilmService::FilmService(FilmRepositoryAbstract &repository) : repository(repository) {}

void FilmService::addFilm(const Film &film) {
    FilmValidator::validateFilm(film);
    FilmService::repository.saveFilm(film);
    undoActions.push_back(std::make_unique<UndoAdauga>(repository, film));
}

const vector<Film>& FilmService::getAllFilms() const noexcept {
    return FilmService::repository.findAllFilms();
}

Film FilmService::getFilmByTitle(const string &title) const {
    return FilmService::repository.getFilmByTitle(title);
}

void FilmService::updateFilm(const Film &oldFilm, const Film &newFilm) {
    FilmValidator::validateFilm(newFilm);
    FilmService::repository.updateFilm(oldFilm, newFilm);
    undoActions.push_back(std::make_unique<UndoModifica>(repository, oldFilm, newFilm));
}

void FilmService::deleteFilm(const Film &film) {
    FilmService::repository.deleteFilm(film);
    undoActions.push_back(std::make_unique<UndoSterge>(repository, film));
}

vector<Film> FilmService::filterFilmsByTitle(const string& title) noexcept {
    vector<Film> films = FilmService::repository.findAllFilms();
    vector<Film> filteredFilms;
    std::copy_if(films.begin(), films.end(), std::back_inserter(filteredFilms), [&title](const Film& film) {
        return film.getTitle() == title;
    });
    return filteredFilms;
}

vector<Film> FilmService::filterFilmsByYear(int year) noexcept {
    vector<Film> films = FilmService::repository.findAllFilms();
    vector<Film> filteredFilms;
    std::copy_if(films.begin(), films.end(), std::back_inserter(filteredFilms), [&year](const Film& film) {
        return film.getYearOfRelease() == year;
    });
    return filteredFilms;
}

vector<Film> FilmService::sortFilmsByTitle() {
    auto sortedFilms = FilmService::repository.findAllFilms();
    sort(sortedFilms.begin(), sortedFilms.end(), [](const Film& a, const Film& b) {
        return a.getTitle() < b.getTitle();
    });
    if (sortedFilms.empty())
        throw FilmServiceException("No films to sort!");
    return sortedFilms;
}

vector<Film> FilmService::sortFilmsByActor() {
    auto sortedFilms = FilmService::repository.findAllFilms();
    sort(sortedFilms.begin(), sortedFilms.end(), [](const Film& a, const Film& b) {
        return a.getPrincipalActor() < b.getPrincipalActor();
    });
    if (sortedFilms.empty())
        throw FilmServiceException("No films to sort!");
    return sortedFilms;
}

vector<Film> FilmService::sortFilmsByYearAndGenre() {
    auto sortedFilms = FilmService::repository.findAllFilms();
    sort(sortedFilms.begin(), sortedFilms.end(), [](const Film& a, const Film& b) {
        return a.getYearOfRelease() < b.getYearOfRelease() || (a.getYearOfRelease() == b.getYearOfRelease() && a.getGenre() < b.getGenre());
    });
    if (sortedFilms.empty())
        throw FilmServiceException("No films to sort!");
    return sortedFilms;
}

void FilmService::undoOperation() {
    if (undoActions.empty()) {
        throw FilmServiceException{"Nu mai exista operatii"};
    }
    undoActions.back()->doUndo();
    undoActions.pop_back();
}
