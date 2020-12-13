#ifndef FigureBOOK_H
#define FigureBOOK_H

#include <QWidget>
#include <QMap>
#include "find.h"
#include "Serialization.h"
QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE


class FigureBook : public QWidget
{
    Q_OBJECT

public:
    FigureBook(QWidget *parent = nullptr);
    enum Mode { NavigationMode, AddingMode, EditingMode };

public slots:
    void addFigure();
    void editFigure();
    void submitFigure();
    void cancel();
    void removeFigure();
    void findFigure();
    void next();
    void previous();
    void saveToFile();
    void loadFromFile();

private:
    void updateInterface(Mode mode);

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QLineEdit *nameLine;
    QTextEdit *specText;
    std::list<IShape*> Shapes;
    QMap<QString, QString> Figures;
    FindDialog *dialog;
    QString oldName;
    QString oldSpec;
    Mode currentMode;
};

#endif
