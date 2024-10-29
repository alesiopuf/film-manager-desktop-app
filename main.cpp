#include <QCoreApplication>
#include <QDebug>
#include "test/TestModule.h"
#include "repository/FilmRepoLab.h"
#include "repository/FilmRepoFile.h"
#include "ui/FilmGUI.h"


int main(int argc, char* argv[]) {

    TestModule::testAll();

    QApplication a(argc, argv);

    std::unique_ptr<FilmRepositoryAbstract> repository = std::make_unique<FilmRepository>();
//    std::unique_ptr<FilmRepositoryAbstract> repository = std::make_unique<FilmRepoLab>();
//    std::unique_ptr<FilmRepositoryAbstract> repository = std::make_unique<FilmRepoFile>();
    FilmService service(*repository);
    FilmContainerService containerService(*repository);
    FilmGUI filmGui(service, containerService);

    filmGui.show();
    return a.exec();
}
