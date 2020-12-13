#include <QtWidgets>
#include "find.h"

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    QLabel *findLabel = new QLabel(tr("Enter the name of a figure:"));
    lineEdit = new QLineEdit;

    findButton = new QPushButton(tr("&Find"));
    findText = "";

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(findLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(findButton);

    setLayout(layout);
    setWindowTitle(tr("Find a figure"));
    connect(findButton, &QPushButton::clicked,
            this, &FindDialog::findClicked);
    connect(findButton, &QPushButton::clicked,
            this, &FindDialog::accept);
}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();

    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a name."));
        return;
    } else {
        findText = text;
        lineEdit->clear();
        hide();
    }
}

QString FindDialog::getFindText()
{
    return findText;
}
