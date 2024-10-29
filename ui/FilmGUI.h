#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>
#include "../service/FilmService.h"
#include "../service/FilmContainerService.h"
#include "observer.h"

using std::vector;
using std::string;
class FilmGUI : public QWidget, public Observer{
private:

    FilmService& service;
    FilmContainerService& containerService;
	
	QLabel* lblTitlu = new QLabel{ "Titlu film:" };
    QLabel* lblGen = new QLabel{ "Gen film:" };
    QLabel* lblAn = new QLabel{ "An film:" };
    QLabel* lblActor = new QLabel{ "Actor film:" };

	QLineEdit* editTitlu{};
	QLineEdit* editGen{};
	QLineEdit* editAn{};
	QLineEdit* editActor{};

	QPushButton* btnAddFilm{};

    QLabel* lblTitluVechi = new QLabel{ "Titlu film vechi:" };
    QLabel* lblGenVechi = new QLabel{ "Gen film vechi:" };
    QLabel* lblAnVechi = new QLabel{ "An film vechi:" };
    QLabel* lblActorVechi = new QLabel{ "Actor film vechi:" };

    QLabel* lblTitluNou = new QLabel{ "Titlu film nou:" };
    QLabel* lblGenNou = new QLabel{ "Gen film nou:" };
    QLabel* lblAnNou = new QLabel{ "An film nou:" };
    QLabel* lblActorNou = new QLabel{ "Actor film nou:" };

    QLineEdit* editTitluVechi{};
    QLineEdit* editGenVechi{};
    QLineEdit* editAnVechi{};
    QLineEdit* editActorVechi{};

    QLineEdit* editTitluNou{};
    QLineEdit* editGenNou{};
    QLineEdit* editAnNou{};
    QLineEdit* editActorNou{};

    QPushButton* btnUpdateFilm{};

    QLabel* lblTitluSters = new QLabel{ "Titlu film de sters:" };
    QLabel* lblGenSters = new QLabel{ "Gen film de sters:" };
    QLabel* lblAnSters = new QLabel{ "An film de sters:" };
    QLabel* lblActorSters = new QLabel{ "Actor film sters:" };

    QLineEdit* editTitluDelete{};
    QLineEdit* editGenDelete{};
    QLineEdit* editAnDelete{};
    QLineEdit* editActorDelete{};

    QPushButton* btnDeleteFilm{};

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSrtAnGen = new QRadioButton(QString::fromStdString("An+Gen"));
	QRadioButton* radioSrtTitlu = new QRadioButton(QString::fromStdString("Titlu"));
	QPushButton* btnSortFilms{};

	QLabel* lblFilterCriteria = new QLabel{ "Titlu dupa care se filtreaza:" };
	QLineEdit* editFilterTitlu{};
	QPushButton* btnFilterFilms{};

    QPushButton* btnUndo{};

    QPushButton* btnCosCRUD{};
    QPushButton* btnCosReadOnly{};

    QLabel* lblCos = new QLabel{ "Cos filme"};
//    QListWidget* listCos{};
    QStringList* sl;
    QListView* listCos{};

    QLineEdit* editAddCos{};
    QPushButton* btnAddCos{};

    QLineEdit* editGenerateCos{};
    QPushButton* btnGenerateCos{};

    QLineEdit* editExportCos{};
    QPushButton* btnExportCos{};

    QPushButton* btnClearCos{};

	QPushButton* btnReloadData{};

	QTableWidget* tableFilms{};

	
	void initializeGUIComponents();
	
	void connectSignalsSlots();
	void reloadFilmList(vector<Film> films);
    void reloadCos(vector<Film> films);
public:
	FilmGUI(FilmService &s, FilmContainerService &cs)
            : service(s), containerService(cs) {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadFilmList(service.getAllFilms());
        this->containerService.addObserver(this);
	}
	void guiAddFilm();
	void guiUpdateFilm();
	void guiDeleteFilm();
    void guiUndo();
    void guiShowCosCRUD();
    void guiShowCosReadOnly();
    void guiAddCos();
    void guiGenerateCos();
    void guiClearCos();
    void guiExportCos();
    void update() override;
};
