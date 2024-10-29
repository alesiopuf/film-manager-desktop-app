//
// Created by user on 4/24/2024.
//

#ifndef POO_LAB_6_7_FILMREPOLAB_H
#define POO_LAB_6_7_FILMREPOLAB_H

#include "FilmRepositoryAbstract.h"
#include "../exceptions/FilmRepositoryException.h"

#include <map>
#include <algorithm>
#include <random>

using std::vector;
using std::map;

class FilmRepoLab: public FilmRepositoryAbstract {

private:
    double probability = 0.5;

    map<int,Film> database;

    vector<Film> filmsConst;

    [[nodiscard]] bool existsFilm(const Film& film) const noexcept {
        auto iterator = std::find_if(database.begin(), database.end(), [&film](const std::pair<int, Film>& p) -> bool {
            return p.second == film;
        });
        if (iterator == database.end()) {
            return false;
        }
        return true;
    }

    static double generateRandom() {
        std::mt19937 mt{std::random_device{}()};
        std::uniform_real_distribution<> dist{0, 1};
        return dist(mt);
    }

public:
    explicit FilmRepoLab(double p) : probability(p) {}

    /**
     * Saves film in database
     * Throws exception if film already exist
     * @param film film to be save
     */
    void saveFilm(const Film& film) override {
        if (generateRandom() < probability)
            throw FilmRepositoryException("Unexpected error");
        if (existsFilm(film))
            throw FilmRepositoryException("Film already exists!");
        database.insert({database.size()+1, film});
    }

    /**
     * Retrieves all films from database
     * @return list of films stored
     */
    [[nodiscard]] const vector<Film>& findAllFilms() noexcept override {
        if (!filmsConst.empty())
            filmsConst.clear();
        for (const auto & it : database) {
            filmsConst.push_back(it.second);
        }
        return filmsConst;
    }

    /**
     * Retrieves first film from database with a certain title
     * Throws exception if film is not found
     * @param title title of the film to be retrieved
     * @return film with the given title
     */
    [[nodiscard]] Film getFilmByTitle(const string &title) const override {
        if (generateRandom() < probability)
            throw FilmRepositoryException("Unexpected error");
        for (const auto & it : database) {
            if (it.second.getTitle() == title)
                return it.second;
        }
        throw FilmRepositoryException("Film this title does not exist!");
    }

    /**
     * Updates a film from database
     * Throws exception if old film is not found
     * @param oldFilm film to be updated
     * @param newFilm new film that will take the place of the old film
     */
    void updateFilm(const Film& oldFilm, const Film& newFilm) override {
        if (generateRandom() < probability)
            throw FilmRepositoryException("Unexpected error");
        for (auto &it : database) {
            if (it.second == oldFilm) {
                it.second = newFilm;
                return;
            }
        }
        throw FilmRepositoryException("Film does not exist!");
    }

    /**
     * Deletes film from database
     * Throws exception if film is not found
     * @param film film to be deleted from list
     */
    void deleteFilm(const Film& film) override {
        if (generateRandom() < probability)
            throw FilmRepositoryException("Unexpected error");
        for (auto it = database.begin(); it != database.end(); ++it) {
            if (it->second == film) {
                database.erase(it);
                return;
            }
        }
        throw FilmRepositoryException("Film does not exist!");
    }
};

#endif //POO_LAB_6_7_FILMREPOLAB_H
