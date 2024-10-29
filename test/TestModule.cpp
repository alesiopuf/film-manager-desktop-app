//
// Created by user on 4/3/2024.
//

#include <cassert>
#include <filesystem>
#include "TestModule.h"
#include "../service/FilmService.h"
#include "../service/FilmContainerService.h"
#include "../repository/FilmRepoLab.h"
#include "../repository/FilmRepoFile.h"

void TestModule::testFilmService() {
    FilmRepository repository;
    FilmService service(repository);

    try {
        service.sortFilmsByTitle();
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        service.sortFilmsByActor();
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        service.sortFilmsByYearAndGenre();
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        service.undoOperation();
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    Film film1("title1", "genre1", 2001, "actor1");
    Film film2("title2", "genre2", 2002, "actor2");
    Film film3("title3", "genre3", 2003, "actor3");

    service.addFilm(film1);
    service.undoOperation();
    service.addFilm(film1);
    service.addFilm(film2);
    service.addFilm(film3);

    vector<Film> films = service.getAllFilms();
    assert(films.size() == 3);

    service.deleteFilm(film2);
    service.undoOperation();
    service.deleteFilm(film2);
    films = service.getAllFilms();
    assert(films.size() == 2);

    Film newFilm("title1", "genre1", 2001, "actor1");
    service.updateFilm(film1, newFilm);
    service.undoOperation();
    service.updateFilm(film1, newFilm);
    films = service.getAllFilms();
    assert(films.size() == 2);
    assert(films[0] == newFilm);
    assert(films[1] == film3);

    Film film = service.getFilmByTitle("title1");
    assert(film == newFilm);

    Film film4("title4", "genre4", 2004, "actor4");
    Film film5("title5", "genre5", 2005, "actor5");
    Film film6("title6", "genre6", 2001, "actor6");

    service.addFilm(film4);
    service.addFilm(film5);
    service.addFilm(film6);

    films = service.getAllFilms();
    assert(films.size() == 5);

    films = service.filterFilmsByTitle("title1");
    assert(films.size() == 1);
    films = service.filterFilmsByYear(2001);
    assert(films.size() == 2);

    films = service.sortFilmsByTitle();
    assert(films[0] == film1);
    films = service.sortFilmsByActor();
    assert(films[0] == film1);
    films = service.sortFilmsByYearAndGenre();
    assert(films[0] == film1);
}

void TestModule::testFilmRepository() {
    //init
    std::unique_ptr<FilmRepositoryAbstract> repository = std::make_unique<FilmRepository>();
    std::unique_ptr<FilmRepositoryAbstract> repolab = std::make_unique<FilmRepoLab>(1);
    std::unique_ptr<FilmRepositoryAbstract> repolab0 = std::make_unique<FilmRepoLab>(0);
    std::unique_ptr<FilmRepositoryAbstract> repofile = std::make_unique<FilmRepoFile>();

    //save
    Film film1("title1", "genre1", 2001, "actor1");
    Film film2("title2", "genre2", 2002, "actor2");
    Film film3("title3", "genre3", 2003, "actor3");

    repository->saveFilm(film1);
    repository->saveFilm(film2);
    repository->saveFilm(film3);
    repofile->saveFilm(film1);
    repofile->saveFilm(film2);
    repofile->saveFilm(film3);
    repolab0->saveFilm(film1);
    repolab0->saveFilm(film2);
    repolab0->saveFilm(film3);
    try {
        repolab->saveFilm(film1);
        repolab->saveFilm(film2);
        repolab->saveFilm(film3);
        assert(true);
    } catch (const std::exception& e) {
        assert(true);
    }

    //save exceptions
    try {
        repository->saveFilm(film3);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repolab->saveFilm(film3);
        assert(true);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repolab0->saveFilm(film3);
        assert(true);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repofile->saveFilm(film3);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    //find
    vector<Film> films = repository->findAllFilms();
    assert(films.size() == 3);
    films = repolab->findAllFilms();
    assert(films.size() <= 3);
    films = repolab0->findAllFilms();
    assert(films.size() == 3);
    films = repofile->findAllFilms();
    assert(films.size() == 3);

    //update
    Film newFilm("title1", "genre1", 2010, "actor1");
    repository->updateFilm(film1, newFilm);
    films = repository->findAllFilms();
    assert(films.size() == 3);
    assert(films[0] == newFilm);
    assert(films[1] == film2);
    assert(films[2] == film3);
    repofile->updateFilm(film1, newFilm);
    films = repofile->findAllFilms();
    assert(films.size() == 3);
    repolab0->updateFilm(film1, newFilm);
    films = repolab0->findAllFilms();
    assert(films.size() == 3);

    //update exceptions
    try {
        repository->updateFilm(film1, newFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repolab->updateFilm(film1, newFilm);
        assert(true);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repolab0->updateFilm(film1, newFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repofile->updateFilm(film1, newFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    //delete
    repository->deleteFilm(film2);
    films = repository->findAllFilms();
    assert(films.size() == 2);
    assert(films[0] == newFilm);
    assert(films[1] == film3);
    repofile->deleteFilm(film2);
    films = repofile->findAllFilms();
    assert(films.size() == 2);
    repolab0->deleteFilm(film2);
    films = repolab0->findAllFilms();
    assert(films.size() == 2);

    //delete exceptions
    try {
        repository->deleteFilm(film2);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repolab->deleteFilm(film2);
        assert(true);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repolab0->deleteFilm(film2);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        repofile->deleteFilm(film2);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    //get exceptions
    try {
        Film film = repository->getFilmByTitle("title2");
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        Film film = repolab->getFilmByTitle("title2");
        assert(true);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        Film film = repolab0->getFilmByTitle("title2");
        assert(true);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        Film film = repofile->getFilmByTitle("title2");
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    //get
    Film film = repository->getFilmByTitle("title1");
    assert(film == newFilm);
    try {
        film = repolab->getFilmByTitle("title1");
        assert(film == newFilm);
    } catch (const std::exception& e) {
        assert(true);
    }
    film = repofile->getFilmByTitle("title1");
    assert(film == newFilm);
    film = repolab0->getFilmByTitle("title1");
    assert(film == newFilm);
}

void TestModule::testFilmValidator() {
    try {
        Film invalidFilm("", "genre1", 2001, "actor1");
        FilmValidator::validateFilm(invalidFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    try {
        Film invalidFilm("title1", "", 2001, "actor1");
        FilmValidator::validateFilm(invalidFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    try {
        Film invalidFilm("title1", "genre1", 2001, "");
        FilmValidator::validateFilm(invalidFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    try {
        Film invalidFilm("title1asfdasdfaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "genre1", 2001, "actor1");
        FilmValidator::validateFilm(invalidFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    try {
        Film invalidFilm("title1", "genre1aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 2001, "actor1");
        FilmValidator::validateFilm(invalidFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    try {
        Film invalidFilm("title1", "genre1", 2001, "actor1aaaaaaaaaaaaaaaaaaaaaaa"
"               aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        FilmValidator::validateFilm(invalidFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    try {
        Film invalidFilm("title1", "genre1", 1760, "actor1");
        FilmValidator::validateFilm(invalidFilm);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
}

void TestModule::testFilmContainerService() {
    FilmRepository repository;
    FilmService service(repository);
    FilmContainerService containerService(repository);

    Film film1("title1", "genre1", 2001, "actor1");
    Film film2("title2", "genre2", 2002, "actor2");
    Film film3("title3", "genre3", 2003, "actor3");

    service.addFilm(film1);
    service.addFilm(film2);
    service.addFilm(film3);

    containerService.addFilmAfterTitle("title1");
    containerService.addFilmAfterTitle("title2");
    try {
        containerService.addFilmAfterTitle("title1");
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
    try {
        containerService.addFilmAfterTitle("title4");
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }

    assert(containerService.getNumberOfFilms() == 2);
    containerService.emptyContainer();
    assert(containerService.getNumberOfFilms() == 0);
    containerService.generateFilms(2);
    assert(containerService.getNumberOfFilms() <= 2);

    containerService.exportFilms("test");
    assert(std::filesystem::exists("test.csv"));

    film1.setTitle("title2");
    film1.setGenre("genre2");
    film1.setYearOfRelease(2002);
    film1.setPrincipalActor("actor2");
    assert(film1 == film2);
}

void TestModule::testAll() {
    testFilmService();
    testFilmContainerService();
    testFilmRepository();
    testFilmValidator();
}
