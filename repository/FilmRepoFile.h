//
// Created by user on 4/24/2024.
//

#ifndef POO_LAB_6_7_FILMREPOFILE_H
#define POO_LAB_6_7_FILMREPOFILE_H

#include <fstream>
#include <algorithm>
#include <sstream>
#include "FilmRepositoryAbstract.h"
#include "../exceptions/FilmRepositoryException.h"

using std::vector;
using std::ifstream;
using std::ofstream;

class FilmRepoFile : public FilmRepositoryAbstract {

private:
    vector<Film> filmsConst;

    string filename = "films.txt";

    [[nodiscard]] bool existsFilm(const Film &film) noexcept {
        filmsConst = findAllFilms();
        auto iterator = std::find(filmsConst.begin(), filmsConst.end(), film);
        if (iterator == filmsConst.end()) {
            return false;
        }
        return true;
    }

public:
    FilmRepoFile() {
        ofstream file(filename);
        file<<"";
        file.close();
    }

    /**
     * Saves film in database
     * Throws exception if film already exist
     * @param film film to be save
     */
    void saveFilm(const Film &film) override {
        if (!existsFilm(film)) {
            ofstream file;
            file.open(filename, std::ios::out | std::ios::app);
            file << film.getTitle() << "," << film.getGenre() << "," << film.getYearOfRelease() << "," << film.getPrincipalActor() << "\n";
            file.close();
        } else {
            throw FilmRepositoryException("Film already exists!");
        }
    }

    /**
     * Retrieves all films from database
     * @return list of films stored
     */
    [[nodiscard]] const vector<Film> &findAllFilms() noexcept override {
        ifstream file(filename);
        filmsConst.clear();
        string line;
        while (std::getline(file, line, '\n')) {
            std::stringstream ss(line);

            string title;
            string genre;
            string yearStr;
            string principalActor;

            std::getline(ss, title, ',');
            std::getline(ss, genre, ',');
            std::getline(ss, yearStr, ',');
            std::getline(ss, principalActor, ',');

            int year = std::stoi(yearStr);

            Film film(title, genre, year, principalActor);
            filmsConst.push_back(film);
        }
        file.close();
        return filmsConst;
    }

    /**
     * Retrieves first film from database with a certain title
     * Throws exception if film is not found
     * @param title title of the film to be retrieved
     * @return film with the given title
     */
    [[nodiscard]] Film getFilmByTitle(const string &title) const override {
        ifstream file(filename);
        string line;
        while (std::getline(file, line, '\n')) {
            std::stringstream ss(line);

            string titleFile;
            string genre;
            string yearStr;
            string principalActor;

            std::getline(ss, titleFile, ',');
            std::getline(ss, genre, ',');
            std::getline(ss, yearStr, ',');
            std::getline(ss, principalActor, ',');

            int year = std::stoi(yearStr);

            if (titleFile == title) {
                Film film(titleFile, genre, year, principalActor);
                file.close();
                return film;
            }
        }
        file.close();
        throw FilmRepositoryException("Film this title does not exist!");
    }

    /**
     * Updates a film from database
     * Throws exception if old film is not found
     * @param oldFilm film to be updated
     * @param newFilm new film that will take the place of the old film
     */
    void updateFilm(const Film &oldFilm, const Film &newFilm) override {
        ifstream file(filename);
        string line;
        while (std::getline(file, line, '\n')) {
            std::stringstream ss(line);

            string titleFile;
            string genre;
            string yearStr;
            string principalActor;

            std::getline(ss, titleFile, ',');
            std::getline(ss, genre, ',');
            std::getline(ss, yearStr, ',');
            std::getline(ss, principalActor, ',');

            int year = std::stoi(yearStr);
            Film film(titleFile, genre, year, principalActor);

            if (film == oldFilm) {
                file.close();
                deleteFilm(oldFilm);
                saveFilm(newFilm);
                return;
            }
        }
        file.close();
        throw FilmRepositoryException("Film does not exist!");
    }

    /**
     * Deletes film from database
     * Throws exception if film is not found
     * @param film film to be deleted from list
     */
    void deleteFilm(const Film &film) override {
        ifstream file(filename);
        ofstream temp("temp.txt");
        string line;
        bool sw = false;
        while (std::getline(file, line, '\n')) {
            std::stringstream ss(line);

            string titleFile;
            string genre;
            string yearStr;
            string principalActor;

            std::getline(ss, titleFile, ',');
            std::getline(ss, genre, ',');
            std::getline(ss, yearStr, ',');
            std::getline(ss, principalActor, ',');

            int year = std::stoi(yearStr);
            Film filmFile(titleFile, genre, year, principalActor);

            if (filmFile == film) {
                sw = true;
                continue;
            }
            temp << titleFile << "," << genre << "," << year << "," << principalActor << "\n";
        }
        file.close();
        temp.close();
        if (!sw) {
            throw FilmRepositoryException("Film does not exist!");
        }
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }

};

#endif //POO_LAB_6_7_FILMREPOFILE_H
