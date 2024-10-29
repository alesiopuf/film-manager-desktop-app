//
// Created by user on 4/2/2024.
//

#ifndef POO_LAB_6_7_FILMSERVICE_H
#define POO_LAB_6_7_FILMSERVICE_H


#include "../repository/FilmRepositoryAbstract.h"
#include "../validator/FilmValidator.h"
#include "../service/undo.h"

#include <memory>

class FilmService {

private:
    FilmRepositoryAbstract& repository;

    std::vector<std::unique_ptr<ActiuneUndo>> undoActions;

public:
    explicit FilmService(FilmRepositoryAbstract &repository);

    /**
     * Creates a new film
     * Throws exception if film is not valid or if it already exists
     * @param film film to be created
     */
    void addFilm(const Film &film);

    /**
     * Retrieves all films
     * Does not throw
     * @return list of films
     */
    [[nodiscard]] const vector<Film>& getAllFilms() const noexcept;

    /**
     * Gets first film which has specific title
     * @param title title searched for
     * @return film
     */
    [[nodiscard]] Film getFilmByTitle(const string& title) const;

    /**
     * Updates film
     * Throws exception if old film does not exist, or new film is invalid
     * @param oldFilm film to be updates
     * @param newFilm new film that will be added
     */
    void updateFilm(const Film& oldFilm, const Film& newFilm);

    /**
     * Deletes an existing film
     * Throws exception in film does not exist
     * @param film film to be added
     */
    void deleteFilm(const Film& film);

    /**
     * Filters films by title
     * @param title title to be filtered by
     * @return new list of films filtered
     */
    vector<Film> filterFilmsByTitle(const string& title) noexcept;

    /**
     * Filters films by year
     * @param year year to be filtered by
     * @return new list of films filtered
     */
    vector<Film> filterFilmsByYear(int year) noexcept;

    /**
     * Sorts films by title
     * @return new sorted list of films
     */
    vector<Film> sortFilmsByTitle();

    /**
     * Sorts films by actor
     * @return new sorted list of films
     */
    vector<Film> sortFilmsByActor();

    /**
     * Sorts films by year and genre
     * @return new sorted list of films
     */
    vector<Film> sortFilmsByYearAndGenre();

    void undoOperation();
};


#endif //POO_LAB_6_7_FILMSERVICE_H
