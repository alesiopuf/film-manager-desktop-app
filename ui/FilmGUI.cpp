#include "FilmGUI.h"
#include "exceptions/FilmRepositoryException.h"
#include "exceptions/FilmValidatorException.h"
#include "CosCRUDGUI.h"
#include "exceptions/FilmServiceException.h"
#include "CosReadOnlyGUI.h"
#include "MyListModel.h"

void FilmGUI::initializeGUIComponents() {

	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu melodii
	
	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente
	
	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unei melodii
	//folosim un QFormLayout pentru detaliile de adaugare a unei melodii
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editTitlu = new QLineEdit;
	editGen = new QLineEdit;
	editAn = new QLineEdit;
	editActor = new QLineEdit;

	lyForm->addRow(lblTitlu, editTitlu);
	lyForm->addRow(lblGen, editGen);
	lyForm->addRow(lblAn, editAn);
	lyForm->addRow(lblActor, editActor);
	btnAddFilm = new QPushButton("Adauga film");
	lyForm->addWidget(btnAddFilm);

	//componente pentru functionalitatea de modificare
	//folosim un QFormLayout pentru detaliile de modificare a unui film
	QWidget* form1 = new QWidget;
	QFormLayout* lyForm1 = new QFormLayout;
	form1->setLayout(lyForm1);
	editTitluVechi = new QLineEdit;
	editGenVechi = new QLineEdit;
	editAnVechi = new QLineEdit;
	editActorVechi = new QLineEdit;
	editTitluNou = new QLineEdit;
	editGenNou = new QLineEdit;
	editAnNou = new QLineEdit;
	editActorNou = new QLineEdit;

	lyForm1->addRow(lblTitluVechi, editTitluVechi);
	lyForm1->addRow(lblGenVechi, editGenVechi);
	lyForm1->addRow(lblAnVechi, editAnVechi);
	lyForm1->addRow(lblActorVechi, editActorVechi);
	lyForm1->addRow(lblTitluNou, editTitluNou);
	lyForm1->addRow(lblGenNou, editGenNou);
	lyForm1->addRow(lblAnNou, editAnNou);
	lyForm1->addRow(lblActorNou, editActorNou);
	btnUpdateFilm = new QPushButton("Modifica film");
	lyForm1->addWidget(btnUpdateFilm);

	//componente pentru functionalitatea de adaugare a unei melodii
	//folosim un QFormLayout pentru detaliile de adaugare a unei melodii
	QWidget* form2 = new QWidget;
	QFormLayout* lyForm2 = new QFormLayout;
	form2->setLayout(lyForm2);
	editTitluDelete = new QLineEdit;
	editGenDelete = new QLineEdit;
	editAnDelete = new QLineEdit;
	editActorDelete = new QLineEdit;

	lyForm2->addRow(lblTitluSters, editTitluDelete);
	lyForm2->addRow(lblGenSters, editGenDelete);
	lyForm2->addRow(lblAnSters, editAnDelete);
	lyForm2->addRow(lblActorSters, editActorDelete);
	btnDeleteFilm = new QPushButton("Sterge film");
	lyForm2->addWidget(btnDeleteFilm);

	//adaugam toate componentele legate de adaugare melodie
	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);
	lyLeft->addWidget(form1);
    lyLeft->addWidget(form2);

	//Radio Buttons: ne ajuta cand trebuie sa selectam doar o 
	//optiune din mai multe (doar un RadioButton poate fi selectat
	//la un moment dat)


	//vs. CheckBox (see documentation)
	//also see documentation on QGroupBox, QRadioButton pentru detalii

	//cream un GroupBox pentru radiobuttons care corespund 
	//criteriilor de sortare pe care le avem (dupa artist+titlu 
	//si durata) + butonul de sortare

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtAnGen);
	lyRadioBox->addWidget(radioSrtTitlu);

	btnSortFilms = new QPushButton("Sorteaza filme");
	lyRadioBox->addWidget(btnSortFilms);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);

	//cream un form pentru filtrarea dupa gen 
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterTitlu = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterTitlu);
	btnFilterFilms = new QPushButton("Filtreaza filme dupa titlu");
	lyFormFilter->addWidget(btnFilterFilms);

	lyLeft->addWidget(formFilter);

    //Undo
    btnUndo = new QPushButton("Undo");
    lyLeft->addWidget(btnUndo);

    //Cos
    lyLeft->addWidget(lblCos);
    QGridLayout* lyCos = new QGridLayout;
    lyLeft->addLayout(lyCos);
    editAddCos = new QLineEdit;
    lyCos->addWidget(editAddCos, 0, 0);
    editGenerateCos = new QLineEdit;
    lyCos->addWidget(editGenerateCos, 0, 1);
    editExportCos = new QLineEdit;
    lyCos->addWidget(editExportCos, 0, 2);
    btnAddCos = new QPushButton("Adauga in cos");
    lyCos->addWidget(btnAddCos, 1, 0);
    btnGenerateCos = new QPushButton("Genereaza cos");
    lyCos->addWidget(btnGenerateCos, 1, 1);
    btnExportCos = new QPushButton("Exporta cos in CSV");
    lyCos->addWidget(btnExportCos, 1, 2);
    btnClearCos = new QPushButton("Goleste cos");
    lyCos->addWidget(btnClearCos, 1, 3);

    btnCosCRUD = new QPushButton("Cos CRUD");
    lyLeft->addWidget(btnCosCRUD);
    btnCosReadOnly = new QPushButton("Cos Read Only");
    lyLeft->addWidget(btnCosReadOnly);


	
	//Buton folosit pentru a reincarca datele
	//i.e. afisam toate melodiile in tabel, in ordinea initiala din fisier
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);
	
	
	//componenta right - contine doar tabelul cu melodii si cosul
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->tableFilms = new QTableWidget{noLines, noColumns};
	
	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Gen" << "An" << "Actor";
	this->tableFilms->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableFilms->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->listCos = new QListView;
    sl = new QStringList;
    for (auto& film : this->containerService.getAllFilms()) {
        sl->append(QString::fromStdString(film.getTitle()));
    }
    MyListModel* model = new MyListModel(*sl);
    this->listCos->setModel(model);
	
	lyRight->addWidget(tableFilms);
    lyRight->addWidget(listCos);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}
void FilmGUI::reloadFilmList(vector<Film> films) {
	this->tableFilms->clearContents();
	this->tableFilms->setRowCount(films.size());
	
	int lineNumber = 0;
	for (auto& film : films) {
		this->tableFilms->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(film.getTitle())));
		this->tableFilms->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(film.getGenre())));
		this->tableFilms->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(film.getYearOfRelease())));
		this->tableFilms->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(film.getPrincipalActor())));
		lineNumber++;
	}
}

void FilmGUI::reloadCos(vector<Film> films) {
    sl = new QStringList;
    for (auto& film : films) {
        sl->append(QString::fromStdString(film.getTitle()));
    }
    MyListModel* model = new MyListModel(*sl);
    this->listCos->setModel(model);
}

void FilmGUI::connectSignalsSlots() {
	QObject::connect(btnAddFilm, &QPushButton::clicked, this, &FilmGUI::guiAddFilm);
	QObject::connect(btnUpdateFilm, &QPushButton::clicked, this, &FilmGUI::guiUpdateFilm);
	QObject::connect(btnDeleteFilm, &QPushButton::clicked, this, &FilmGUI::guiDeleteFilm);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &FilmGUI::guiUndo);
	QObject::connect(btnCosCRUD, &QPushButton::clicked, this, &FilmGUI::guiShowCosCRUD);
	QObject::connect(btnCosReadOnly, &QPushButton::clicked, this, &FilmGUI::guiShowCosReadOnly);
    QObject::connect(btnGenerateCos, &QPushButton::clicked, this, &FilmGUI::guiGenerateCos);
    QObject::connect(btnClearCos, &QPushButton::clicked, this, &FilmGUI::guiClearCos);
    QObject::connect(btnAddCos, &QPushButton::clicked, this, &FilmGUI::guiAddCos);
    QObject::connect(btnExportCos, &QPushButton::clicked, this, &FilmGUI::guiExportCos);

	QObject::connect(btnSortFilms, &QPushButton::clicked, [&]() {
		if (this->radioSrtAnGen->isChecked())
			this->reloadFilmList(service.sortFilmsByYearAndGenre());
		else if (this->radioSrtTitlu->isChecked())
			this->reloadFilmList(service.sortFilmsByTitle());
		});

	QObject::connect(btnFilterFilms, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterTitlu->text().toStdString();
		this->reloadFilmList(service.filterFilmsByTitle(filterC));
		});
	
	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadFilmList(service.getAllFilms());
		});
	
}


void FilmGUI::guiAddFilm() {
	try {
		//preluare detalii din QLineEdit-uri
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		int an = editAn->text().toInt();
		string actor = editActor->text().toStdString();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editTitlu->clear();
		editGen->clear();
		editAn->clear();
		editActor->clear();

        Film f(titlu, gen, an, actor);
		this->service.addFilm(f);
		this->reloadFilmList(this->service.getAllFilms());

		QMessageBox::information(this, "Info", QString::fromStdString("Film adaugat cu succes."));

	}
	catch (FilmRepositoryException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (FilmValidatorException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessage()));
	}
}

void FilmGUI::guiUpdateFilm() {
    try {
        //preluare detalii din QLineEdit-uri
        string titlu = editTitluVechi->text().toStdString();
        string gen = editGenVechi->text().toStdString();
        int an = editAnVechi->text().toInt();
        string actor = editActorVechi->text().toStdString();
        Film filmVechi(titlu, gen, an, actor);

        titlu = editTitluNou->text().toStdString();
        gen = editGenNou->text().toStdString();
        an = editAnNou->text().toInt();
        actor = editActorNou->text().toStdString();
        Film filmNou(titlu, gen, an, actor);

        //optional - golim QLineEdit-urile dupa apasarea butonului
        editTitluNou->clear();
        editGenNou->clear();
        editAnNou->clear();
        editActorNou->clear();
        editTitluVechi->clear();
        editGenVechi->clear();
        editAnVechi->clear();
        editActorVechi->clear();

        this->service.updateFilm(filmVechi, filmNou);
        this->reloadFilmList(this->service.getAllFilms());

        QMessageBox::information(this, "Info", QString::fromStdString("Film modificat cu succes."));

    }
    catch (FilmRepositoryException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
    }
    catch (FilmValidatorException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessage()));
    }
}

void FilmGUI::guiDeleteFilm() {
    try {
        //preluare detalii din QLineEdit-uri
        string titlu = editTitluDelete->text().toStdString();
        string gen = editGenDelete->text().toStdString();
        int an = editAnDelete->text().toInt();
        string actor = editActorDelete->text().toStdString();

        //optional - golim QLineEdit-urile dupa apasarea butonului
        editTitluDelete->clear();
        editGenDelete->clear();
        editAnDelete->clear();
        editActorDelete->clear();

        Film f(titlu, gen, an, actor);
        this->service.deleteFilm(f);
        this->reloadFilmList(this->service.getAllFilms());

        QMessageBox::information(this, "Info", QString::fromStdString("Film sters cu succes."));

    }
    catch (FilmRepositoryException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
    }
    catch (FilmValidatorException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessage()));
    }
}

void FilmGUI::guiUndo() {
    try {
        this->service.undoOperation();
        this->reloadFilmList(this->service.getAllFilms());

        QMessageBox::information(this, "Info", QString::fromStdString("Operatie refacuta."));
    }
    catch (FilmServiceException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));

    }
}

void FilmGUI::guiAddCos() {
    try {
        string titlu = editAddCos->text().toStdString();
        this->containerService.addFilmAfterTitle(titlu);

        QMessageBox::information(this, "Info", QString::fromStdString("Film adaugat in cos."));
    }
    catch (FilmRepositoryException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));

    }
}

void FilmGUI::guiGenerateCos() {
    try {
        int nr = editGenerateCos->text().toInt();
        this->containerService.generateFilms(nr);

        QMessageBox::information(this, "Info", QString::fromStdString("Filme generate in cos."));
    }
    catch (FilmRepositoryException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));

    }
}

void FilmGUI::guiClearCos() {
    this->containerService.emptyContainer();

    QMessageBox::information(this, "Info", QString::fromStdString("Cos golit."));
}

void FilmGUI::guiExportCos() {
    try {
        string filename = editExportCos->text().toStdString();
        this->containerService.exportFilms(filename);
        QMessageBox::information(this, "Info", QString::fromStdString("Cos exportat cu succes."));
    }
    catch (FilmRepositoryException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));

    }
}

void FilmGUI::guiShowCosCRUD() {
    CosCRUDGUI* cosCRUD = new CosCRUDGUI(this->containerService);
    cosCRUD->show();
}

void FilmGUI::guiShowCosReadOnly() {
    CosReadOnlyGUI* cosReadOnly = new CosReadOnlyGUI(this->containerService);
    cosReadOnly->show();
}

void FilmGUI::update() {
    reloadCos(containerService.getAllFilms());
}
