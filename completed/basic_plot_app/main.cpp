#include <QApplication>

#include "basicplotdialog.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BasicPlotDialog *dialog = new BasicPlotDialog;
    dialog->show();
    return app.exec();
}
