// ============================================================================
//
// custom_graph_framework - Framework for building graph plotting apps
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
// * custom_graph_framework.cpp: created.
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// Standard Library headers ---------------------------------------------------
#include <cmath>
#include <iostream>

// Qt Library headers ---------------------------------------------------------
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>

// Project library headers ----------------------------------------------------
#include "custom_graph_view.hpp"


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
    QApplication    *app         = new QApplication(argc, argv);
    QMainWindow     *main_window = new QMainWindow();                 // Qwidget
    QSplitter       *layout      = new QSplitter(main_window);
    QWidget         *fill        = new QWidget(layout);
    CustomGraphView *main_view   = new CustomGraphView(layout);
    QGraphicsScene  *graph_scene = new QGraphicsScene(layout);
    QChart          *chart       = new QChart;                       // QGraphicsObject
    QLineSeries     *s1          = new QLineSeries(chart);           // QAbstractSeries
    QLineSeries     *s2          = new QLineSeries(chart);           // QAbstractSeries

    // Populate series with data
    for(uint index = 0; index < 361; index++) {
        float i = static_cast<float>(index);
        s1->append(i, sin((3.14*i)/180));
        s2->append(i, pow(i, 2)/pow(360, 2));
    }

    // Set up chart object
    s1->setName("sine");
    s2->setName("quadratic");
    chart->setMinimumSize(640, 480);
    chart->addSeries(s1);
    chart->addSeries(s2);
    chart->createDefaultAxes();
    chart->setTitle("Custom Graph View Framework");
    chart->setAcceptHoverEvents(true);

    // Set up the view object
    main_view->setScene(graph_scene);
    main_view->setGraph(chart);

    // Connect signals and slots
    main_view->connect(
            s1,
            &QLineSeries::clicked,
            main_view,
            &CustomGraphView::save_callout
            );
    main_view->connect(
            s1,
            &QLineSeries::hovered,
            main_view,
            &CustomGraphView::callout
            );
    main_view->connect(
            s2,
            &QLineSeries::clicked,
            main_view,
            &CustomGraphView::save_callout
            );
    main_view->connect(
            s2,
            &QLineSeries::hovered,
            main_view,
            &CustomGraphView::callout
            );

    // Spawn the main window and assign objects to be displayed
    layout->addWidget(fill);
    layout->addWidget(main_view);
    std::cout << "Main window\n";
    main_window->setCentralWidget(layout);
    main_window->show();

    int result = app->exec();
    cout << result << endl;

    // Clean up
    delete chart;
    delete main_window;
    // delete chart_view;
    // delete s2;
    // delete s1;

    // Exit the app
    return result;

}
