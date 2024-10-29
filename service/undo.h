//
// Created by user on 4/22/2024.
//

#ifndef POO_LAB_6_7_UNDO_H
#define POO_LAB_6_7_UNDO_H


#include "../domain/Film.h"
#include "../repository/FilmRepository.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    //destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
    virtual ~ActiuneUndo()= default;
};

class UndoAdauga : public ActiuneUndo {
    Film filmAdaugat;
    FilmRepositoryAbstract& rep;
public:
    UndoAdauga(FilmRepositoryAbstract& rep,const  Film& p) :filmAdaugat{ p }, rep{ rep } {}

    void doUndo() override {
        rep.deleteFilm(filmAdaugat);
    }
};

class UndoSterge : public ActiuneUndo {
    Film filmSters;
    FilmRepositoryAbstract& rep;
public:
    UndoSterge(FilmRepositoryAbstract& rep, const  Film& p) :filmSters{ p }, rep{ rep } {}
    void doUndo() override {
        rep.saveFilm(filmSters);
    }
};

class UndoModifica : public ActiuneUndo {
    Film filmVechi;
    Film filmNou;
    FilmRepositoryAbstract& rep;
public:
    UndoModifica(FilmRepositoryAbstract& rep, const Film& fv, const Film& fn) : filmVechi{fv}, filmNou{fn}, rep{rep} {}
    void doUndo() override {
        rep.updateFilm(filmNou, filmVechi);
    }
};


#endif //POO_LAB_6_7_UNDO_H
