//
// Created by user on 4/2/2024.
//

#include "Film.h"

#include <utility>
#include <iostream>
#include <QDebug>

using std::cout;

Film::Film(string title, string genre, int yearOfRelease, string principalActor) :
    title(std::move(title)), genre(std::move(genre)), yearOfRelease(yearOfRelease), principalActor(std::move(principalActor)) {}

const string &Film::getTitle() const {
    return title;
}

void Film::setTitle(const string &t) {
    Film::title = t;
}

const string &Film::getGenre() const {
    return genre;
}

void Film::setGenre(const string &g) {
    Film::genre = g;
}

int Film::getYearOfRelease() const {
    return yearOfRelease;
}

void Film::setYearOfRelease(int y) {
    Film::yearOfRelease = y;
}

const string &Film::getPrincipalActor() const {
    return principalActor;
}

void Film::setPrincipalActor(const string &p) {
    Film::principalActor = p;
}

bool Film::operator==(const Film &film) const noexcept {
    return title == film.title && genre == film.genre && yearOfRelease == film.yearOfRelease &&
        principalActor == film.principalActor;
}

Film::Film(const Film &ot) : title(ot.getTitle()), genre(ot.getGenre()),
yearOfRelease(ot.getYearOfRelease()), principalActor(ot.getPrincipalActor()) {
    qDebug()<< "Copy constructor called";
}

Film& Film::operator=(const Film &film) = default;
