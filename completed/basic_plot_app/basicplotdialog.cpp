#include <QtGui>
#include <cmath>

#include "basicplotdialog.hpp"

BasicPlotDialog::BasicPlotDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QVector<double> x(1001), y(1001);
    for (int i=0; i < 1001; i++)
    {
        // We plot some nice graph of dumped oscillation.
        x[i] = i / 100.0;
        y[i] = exp(-x[i] / 2.0) * cos(2 * 3.14 * x[i]);
    }

    plot->addGraph();
    plot->graph(0)->setData(x, y);
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    plot->xAxis->setRange(0.0, 10.0);
    plot->yAxis->setRange(-1.0, 1.0);
    plot->replot();
}
