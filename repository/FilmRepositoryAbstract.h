//
// Created by user on 4/24/2024.
//

#ifndef POO_LAB_6_7_FILMREPOSITORYABSTRACT_H
#define POO_LAB_6_7_FILMREPOSITORYABSTRACT_H

#include "../domain/Film.h"
#include <vector>

using std::vector;

class FilmRepositoryAbstract {

public:

    virtual ~FilmRepositoryAbstract() = default;

    /**
     * Saves film in database
     * Throws exception if film already exist
     * @param film film to be save
     */
    virtual void saveFilm(const Film& film) = 0;

    /**
     * Retrieves all films from database
     * @return list of films stored
     */
    [[nodiscard]] virtual const vector<Film>& findAllFilms() noexcept = 0;

    /**
     * Retrieves first film from database with a certain title
     * Throws exception if film is not found
     * @param title title of the film to be retrieved
     * @return film with the given title
     */
    [[nodiscard]] virtual Film getFilmByTitle(const string &title) const = 0;

    /**
     * Updates a film from database
     * Throws exception if old film is not found
     * @param oldFilm film to be updated
     * @param newFilm new film that will take the place of the old film
     */
    virtual void updateFilm(const Film& oldFilm, const Film& newFilm) = 0;

    /**
     * Deletes film from database
     * Throws exception if film is not found
     * @param film film to be deleted from list
     */
    virtual void deleteFilm(const Film& film) = 0;
};

#endif //POO_LAB_6_7_FILMREPOSITORYABSTRACT_H
