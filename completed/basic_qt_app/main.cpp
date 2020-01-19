#include <QApplication>

#include "basicqtdialog.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BasicDialog *dialog = new BasicDialog;
    dialog->show();
    return app.exec();
}
