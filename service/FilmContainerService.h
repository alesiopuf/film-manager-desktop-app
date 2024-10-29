//
// Created by user on 4/17/2024.
//

#ifndef POO_LAB_6_7_FILMCONTAINERSERVICE_H
#define POO_LAB_6_7_FILMCONTAINERSERVICE_H


#include "../repository/FilmRepositoryAbstract.h"
#include "ui/observer.h"

class FilmContainerService : public Observable {

private:
    vector<Film> cos;
    FilmRepositoryAbstract& source;

public:
    explicit FilmContainerService(FilmRepositoryAbstract &source);

    /**
     * Retrieves the number of films in the container
     * @return length of the container
     */
    [[nodiscard]] int getNumberOfFilms() const noexcept;

    /**
     * Searches for a film in the source repository and adds it to the container after a certain title
     * Throws exception if title is not found
     * @param title title of the film after which the new film will be added
     */
    void addFilmAfterTitle(const string& title);

    /**
     * Empties the container
     */
    void emptyContainer();

    /**
     * Generates a number of films and adds them to the container
     * @param numberOfFilms number of films to be generated
     */
    void generateFilms(int numberOfFilms);

    /**
     * Exports all films from the container to a file
     * @param filename name of the file to which the films will be exported
     */
    void exportFilms(const string& filename);

    /**
     * Retrieves all films
     * Does not throw
     * @return list of films
     */
    [[nodiscard]] const vector<Film>& getAllFilms() const noexcept;
};


#endif //POO_LAB_6_7_FILMCONTAINERSERVICE_H
