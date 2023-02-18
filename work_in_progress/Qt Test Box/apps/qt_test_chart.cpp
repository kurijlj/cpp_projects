// ============================================================================
//
// qt_test_chart - Simple GUI app to test basic QChart functionality
//
//  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================


// ============================================================================
//
// 2023-02-16 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * qt_test_chart.cpp: created.
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// Standard Library headers ---------------------------------------------------
#include <cmath>

// Qt Library headers ---------------------------------------------------------
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>


// ============================================================================
// Aliases section
// ============================================================================

using ushort = unsigned short int;
using uint   = unsigned int;
using ulong  = unsigned long int;
using ullong = unsigned long long int;


// ============================================================================
// Used namespaces section
// ============================================================================

using namespace std;
using namespace QtCharts;


// ============================================================================
// App's main function body
// ============================================================================

int main(int argc, char *argv[]) {
    QApplication *app = new QApplication(argc, argv);
    QMainWindow *main_window = new QMainWindow();  // Qwidget
    QChart *chart = new QChart;  // QGraphicsObject
    QLineSeries *s1 = new QLineSeries(chart);  // QAbstractSeries
    QLineSeries *s2 = new QLineSeries(chart);  // QAbstractSeries
    QChartView *chart_view;  // Qwidget

    // Populate series with data
    for(uint index = 0; index < 361; index++) {
        float i = static_cast<float>(index);
        s1->append(i, sin((3.14*i)/180));
        s2->append(i, pow(i, 2)/pow(360, 2));
    }

    // Set up chart object
    s1->setName("sine");
    s2->setName("quadratic");
    chart->addSeries(s1);
    chart->addSeries(s2);
    chart->createDefaultAxes();
    chart->setTitle("Simple Chart Test");

    // Set up chart view
    chart_view = new QChartView(chart);
    chart_view->setRenderHint(QPainter::Antialiasing);

    // Spawn the main window and assign objects to be displayed
    main_window->setCentralWidget(chart_view);
    main_window->resize(1280, 960);
    main_window->show();

    int result = app->exec();

    // Clean up
    delete chart;
    delete main_window;

    // Exit the app
    return result;

}
