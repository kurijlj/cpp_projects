#ifndef BASICQTDIALOG_H
#define BASICQTDIALOG_H

#include <QDialog>

#include "ui_BasicQtApp.h"

class BasicDialog : public QDialog, public Ui::BasicDialog
{
    Q_OBJECT

public:
    BasicDialog(QWidget *parent = nullptr);
};

#endif
