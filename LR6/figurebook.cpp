#include <QtWidgets>
#include "figurebook.h"
FigureBook::FigureBook(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);

    QLabel *specLabel = new QLabel(tr("Specs:"));
    specText = new QTextEdit;
    specText->setReadOnly(true);

    addButton = new QPushButton(tr("&Add"));

    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);
    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();

    nextButton = new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);

    loadButton = new QPushButton(tr("&Load..."));
    loadButton->setToolTip(tr("Load Figures from a file"));
    saveButton = new QPushButton(tr("&Save..."));
    saveButton->setToolTip(tr("Save Figures to a file"));
    saveButton->setEnabled(false);

    dialog = new FindDialog(this);

    connect(addButton, &QPushButton::clicked,
            this, &FigureBook::addFigure);
    connect(submitButton, &QPushButton::clicked,
            this, &FigureBook::submitFigure);
    connect(editButton, &QPushButton::clicked,
            this, &FigureBook::editFigure);
    connect(removeButton, &QPushButton::clicked,
            this, &FigureBook::removeFigure);
    connect(cancelButton, &QPushButton::clicked,
            this, &FigureBook::cancel);
    connect(findButton, &QPushButton::clicked,
            this, &FigureBook::findFigure);
    connect(nextButton, &QPushButton::clicked,
            this, &FigureBook::next);
    connect(previousButton, &QPushButton::clicked,
            this, &FigureBook::previous);
    connect(loadButton, &QPushButton::clicked,
            this, &FigureBook::loadFromFile);
    connect(saveButton, &QPushButton::clicked,
            this, &FigureBook::saveToFile);

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(findButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(loadButton);
    buttonLayout1->addWidget(saveButton);
    buttonLayout1->addStretch();

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(specLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(specText, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 2, 1);

    setLayout(mainLayout);
    setWindowTitle(tr("FigureBook"));
}

void FigureBook::addFigure()
{
    oldName = nameLine->text();
    oldSpec = specText->toPlainText();

    nameLine->clear();
    specText->clear();

    updateInterface(AddingMode);
}

void FigureBook::editFigure()
{
    oldName = nameLine->text();
    oldSpec = specText->toPlainText();

    updateInterface(EditingMode);
}

void FigureBook::submitFigure()
{
    QString name = nameLine->text();
    QString spec = specText->toPlainText();

    if (name.isEmpty() || spec.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a name and spec."));
        return;
    }
    if ((!name.contains("circle")) &&
        (!name.contains("square")) &&
        (!name.contains("rectangle")) &&
        (!name.contains("triangle"))){
        QMessageBox::information(this, tr("Wrong name"),
            tr("Its not a figure."));
        return;
    }

    if (currentMode == AddingMode) {

        if (!Figures.contains(name)) {
            Figures.insert(name, spec);
            QMessageBox::information(this, tr("Add Successful"),
                tr("\"%1\" has been added to your figure book.").arg(name));
        } else {
            QMessageBox::information(this, tr("Add Unsuccessful"),
                tr("Sorry, \"%1\" is already in your figure book.").arg(name));
        }
    } else if (currentMode == EditingMode) {

        if (oldName != name) {
            if (!Figures.contains(name)) {
                QMessageBox::information(this, tr("Edit Successful"),
                    tr("\"%1\" has been edited in your figure book.").arg(oldName));
                Figures.remove(oldName);
                Figures.insert(name, spec);
            } else {
                QMessageBox::information(this, tr("Edit Unsuccessful"),
                    tr("Sorry, \"%1\" is already in your figure book.").arg(name));
            }
        } else if (oldSpec != spec) {
            QMessageBox::information(this, tr("Edit Successful"),
                tr("\"%1\" has been edited in your figure book.").arg(name));
            Figures[name] = spec;
        }
    }

    updateInterface(NavigationMode);
}

void FigureBook::cancel()
{
    nameLine->setText(oldName);
    specText->setText(oldSpec);
    updateInterface(NavigationMode);
}

void FigureBook::removeFigure()
{
    QString name = nameLine->text();
    QString spec = specText->toPlainText();

    if (Figures.contains(name)) {

        int button = QMessageBox::question(this,
            tr("Confirm Remove"),
            tr("Are you sure you want to remove \"%1\"?").arg(name),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {

            previous();
            Figures.remove(name);

            QMessageBox::information(this, tr("Remove Successful"),
                tr("\"%1\" has been removed from your figure book.").arg(name));
        }
    }

    updateInterface(NavigationMode);
}

void FigureBook::next()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = Figures.find(name);

    if (i != Figures.end())
        i++;

    if (i == Figures.end())
        i = Figures.begin();

    nameLine->setText(i.key());
    specText->setText(i.value());
}

void FigureBook::previous()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = Figures.find(name);

    if (i == Figures.end()) {
        nameLine->clear();
        specText->clear();
        return;
    }

    if (i == Figures.begin())
        i = Figures.end();

    i--;
    nameLine->setText(i.key());
    specText->setText(i.value());
}

void FigureBook::findFigure()
{
    dialog->show();

    if (dialog->exec() == 1) {
        QString FigureName = dialog->getFindText();

        if (Figures.contains(FigureName)) {
            nameLine->setText(FigureName);
            specText->setText(Figures.value(FigureName));
        } else {
            QMessageBox::information(this, tr("Figure Not Found"),
                tr("Sorry, \"%1\" is not in your figure book.").arg(FigureName));
            return;
        }
    }

    updateInterface(NavigationMode);
}

void FigureBook::updateInterface(Mode mode)
{
    currentMode = mode;

    switch (currentMode) {

    case AddingMode:
    case EditingMode:

        nameLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);
        specText->setReadOnly(false);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);

        nextButton->setEnabled(false);
        previousButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();

        loadButton->setEnabled(false);
        saveButton->setEnabled(false);
        break;

    case NavigationMode:

        if (Figures.isEmpty()) {
            nameLine->clear();
            specText->clear();
        }

        nameLine->setReadOnly(true);
        specText->setReadOnly(true);
        addButton->setEnabled(true);

        int number = Figures.size();
        editButton->setEnabled(number >= 1);
        removeButton->setEnabled(number >= 1);
        findButton->setEnabled(number > 2);
        nextButton->setEnabled(number > 1);
        previousButton->setEnabled(number > 1);

        submitButton->hide();
        cancelButton->hide();

        loadButton->setEnabled(true);
        saveButton->setEnabled(number >= 1);
        break;
    }
}

void FigureBook::saveToFile()
{
    Serializator SRLZ;
    for (auto i = Figures.begin(); i != Figures.end(); i++){
        if (i.key().contains("circle")){
            Shapes.push_back(new Circle(i.key().toStdString(), i.value().toStdString()));
        }
        else if (i.key().contains("square")){
            Shapes.push_back(new Square(i.key().toStdString(), i.value().toStdString()));
        }
        else if (i.key().contains("rectangle")){
            Shapes.push_back(new class Rectangle(i.key().toStdString(), i.value().toStdString()));
        }
        else if   (i.key().contains("triangle")){
            Shapes.push_back(new Triangle(i.key().toStdString(), i.value().toStdString()));
        }
    }
    SRLZ.serialize(&Shapes);
}

void FigureBook::loadFromFile()
{
    Serializator SRLZ;
        Shapes = SRLZ.deserialize("C:\\Users\\Squirrel\\Documents\\LR6\\shapes.json");
        for (auto x : Shapes) {
            Figures.insert(QString::fromStdString(x->getName()), QString::fromStdString(x->getSpec()));
        }
    updateInterface(NavigationMode);
}

