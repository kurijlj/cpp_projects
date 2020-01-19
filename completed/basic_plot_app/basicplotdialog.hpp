#ifndef BASICPLOTDIALOG_H
#define BASICPLOTDIALOG_H

#include <QDialog>
#include "qcustomplot.h"

#include "ui_BasicPlotApp.h"

class BasicPlotDialog : public QDialog, public Ui::BasicPlotDialog
{
    Q_OBJECT

public:
    BasicPlotDialog(QWidget *parent = nullptr);
};

#endif
