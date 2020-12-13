
#include <QtWidgets>
#include "figurebook.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FigureBook figureBook;
    figureBook.show();

    return app.exec();
}
