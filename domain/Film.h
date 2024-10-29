//
// Created by user on 4/2/2024.
//

#ifndef POO_LAB_6_7_FILM_H
#define POO_LAB_6_7_FILM_H

#include <string>

using std::string;

class Film {

private:
    string title;
    string genre;
    int yearOfRelease{};
    string principalActor;

public:
    Film() = default;

    Film(string title, string genre, int yearOfRelease, string principalActor);

    Film(const Film &ot);

    [[nodiscard]] const string &getTitle() const;

    void setTitle(const string &title);

    [[nodiscard]] const string &getGenre() const;

    void setGenre(const string &genre);

    [[nodiscard]] int getYearOfRelease() const;

    void setYearOfRelease(int yearOfRelease);

    [[nodiscard]] const string &getPrincipalActor() const;

    void setPrincipalActor(const string &principalActor);

    bool operator==(const Film& film) const noexcept;

    Film & operator=(const Film& film);

    ~Film() = default;
};


#endif //POO_LAB_6_7_FILM_H
