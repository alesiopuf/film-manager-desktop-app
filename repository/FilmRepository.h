//
// Created by user on 4/2/2024.
//

#ifndef POO_LAB_6_7_FILMREPOSITORY_H
#define POO_LAB_6_7_FILMREPOSITORY_H

#include "FilmRepositoryAbstract.h"

using std::vector;

class FilmRepository : public FilmRepositoryAbstract {

private:
    vector<Film> database;

    [[nodiscard]] bool existsFilm(const Film& film) const noexcept;

public:
    FilmRepository() = default;

    /**
     * Saves film in database
     * Throws exception if film already exist
     * @param film film to be save
     */
    void saveFilm(const Film& film) override;

    /**
     * Retrieves all films from database
     * @return list of films stored
     */
    [[nodiscard]] const vector<Film>& findAllFilms() noexcept override;

    /**
     * Retrieves first film from database with a certain title
     * Throws exception if film is not found
     * @param title title of the film to be retrieved
     * @return film with the given title
     */
    [[nodiscard]] Film getFilmByTitle(const string &title) const override;

    /**
     * Updates a film from database
     * Throws exception if old film is not found
     * @param oldFilm film to be updated
     * @param newFilm new film that will take the place of the old film
     */
    void updateFilm(const Film& oldFilm, const Film& newFilm) override;

    /**
     * Deletes film from database
     * Throws exception if film is not found
     * @param film film to be deleted from list
     */
    void deleteFilm(const Film& film) override;
};


#endif //POO_LAB_6_7_FILMREPOSITORY_H
