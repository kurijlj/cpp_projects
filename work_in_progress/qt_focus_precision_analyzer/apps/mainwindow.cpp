// ============================================================================
//
// GUI Application Framework using Qt and QPlainTextEdit widget
//
//  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This code is derived from software released by Qt Company Ltd. under
// BSD-3-Clause license described below.
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


/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


// ============================================================================
//
// <Put documentation here>
//
// <yyyy>-<mm>-<dd> <Author Name> <author@mail.com>
//
// * <programfilename>.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For command line arguments parsing using clipp consult documentation and
//   examples at <https://github.com/muellan/clipp>.
//
// * For filesystem operations (C++17) visit 'filesystem' reference at:
//   <https://en.cppreference.com/w/cpp/filesystem>.
//
// ============================================================================


// ============================================================================
// Headers include section
// ============================================================================

// Qt Library headers
#include <QDate>
#include <QDateTime>
#include <QFileInfo>
#include <QRegExp>
#include <QTextStream>
#include <QTime>
#include <QtWidgets>

// Class header
#include "mainwindow.hpp"


// ============================================================================
// Constructors and Destrucors section
// ============================================================================

MainWindow::MainWindow()
    : text_edit_(new QPlainTextEdit)
{
    // Set main window widgets
    setCentralWidget(text_edit_);
    createActions();
    createStatusBar();

    // Read settings regarding window geometry and organization
    // and application name
    readSettings();

    // Connect slots and signals
    connect(text_edit_->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

#ifndef QT_NO_SESSIONMANAGER
    connect(qApp, &QGuiApplication::commitDataRequest,
            this, &MainWindow::commitData);
#endif

    // Set new empty session log
    setSession();
    setUnifiedTitleAndToolBarOnMac(true);

    // We want it to be read only widget
    text_edit_->setReadOnly(true);
}


// ============================================================================
// Protected methods section
// ============================================================================

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


// ============================================================================
// Signal slots section
// ============================================================================

void MainWindow::openLog()
{
    // QMessageBox::information(
    //         this,
    //         tr("Not Implemented"),
    //         tr("This functionality is not yet implemented.")
    //         );
    QString file_name = QFileDialog::getOpenFileName(
            this,
            "Open Focus Precision Test Log File (.rmd)",
            last_log_dir_,
            "Focus Precision Test log files (*.rmd)"
            );
    if (!file_name.isEmpty())
    {
        QFileInfo selected_file_name(file_name);
        last_log_dir_ = selected_file_name.absolutePath();
        loadLogFile(file_name);
    }
}

bool MainWindow::saveSession()
{
    if (session_log_file_.isEmpty()) {
        return saveSessionAs();
    } else {
        return saveSessionLog(session_log_file_);
    }
}

bool MainWindow::saveSessionAs()
{
    QFileDialog dialog(
            this,
            "Save Log for " + session_title_,
            QDir::toNativeSeparators(
                session_save_dir_ + "/" +  session_save_name_
                ),
            "Session log files (*.log)"
            );
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    QFileInfo saved_file_name(dialog.selectedFiles().first());
    session_save_dir_ = saved_file_name.absolutePath();
    session_save_name_ = saved_file_name.fileName();
    return saveSessionLog(session_save_dir_ + "/" + session_save_name_);
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Focus Precision Analyzer"),
            tr("The <b>Focus Precision Analyzer</b> is GUI application for "
               "inspecting and analyzing data from Focus Precision Test logs."
               "<br><br>"
               "<b>License Notice</b><br>"
               "This program is free software: you can redistribute it and/or "
               "modify<br>"
               "it under the terms of the GNU General Public License as "
               "published by<br>"
               "the Free Software Foundation, either version 3 of the License, "
               "or<br>"
               "(at your option) any later version."
               "<br><br>"
               "This program is distributed in the hope that it will be "
               "useful,<br>"
               "but WITHOUT ANY WARRANTY; without even the implied warranty "
               "of<br>"
               "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See "
               "the<br>"
               "GNU General Public License for more details."
               "<br><br>"
               "You should have received a copy of the GNU General Public "
               "License<br>"
               "along with this program.  If not, see "
               "<a href='https://www.gnu.org/licenses/'>"
               "https://www.gnu.org/licenses/</a>."
               ));
}

void MainWindow::documentWasModified()
{
    setWindowTitle("Focus Precision Analyzer - " + session_title_ + " [*]");
    setWindowModified(text_edit_->document()->isModified());
}

void MainWindow::showMessage(const QString &msg, MainWindow::MessageType type)
{
    QDateTime now(QDateTime::currentDateTime());
    QString type_string;

    switch(type) {
        case MainWindow::Error: type_string = "(EE)"; break;
        case MainWindow::Warning: type_string = "(WW)"; break;
        default: type_string = "(II)";
    };

    text_edit_->appendPlainText(
            now.toString("hh:mm:ss ")
            + type_string + ": "
            + msg // + '\n'
            );
}


// ============================================================================
// Private methods section
// ============================================================================

void MainWindow::createActions()
{

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon openIcon = QIcon::fromTheme(
            "document-open",
            QIcon(":/images/open.png")
            );
    QAction *openLogAct = new QAction(
            openIcon,
            tr("&Open Focus Precision Test Log..."),
            this
            );
    openLogAct->setShortcuts(QKeySequence::Open);
    openLogAct->setStatusTip(tr("Open an test log file"));
    connect(openLogAct, &QAction::triggered, this, &MainWindow::openLog);
    fileMenu->addAction(openLogAct);
    fileToolBar->addAction(openLogAct);

    const QIcon saveIcon = QIcon::fromTheme(
            "document-save",
            QIcon(":/images/save.png")
            );
    QAction *saveSessionAct = new QAction(saveIcon, tr("&Save Session"), this);
    saveSessionAct->setShortcuts(QKeySequence::Save);
    saveSessionAct->setStatusTip(tr("Update session log file"));
    connect(
            saveSessionAct,
            &QAction::triggered,
            this,
            &MainWindow::saveSession
            );
    fileMenu->addAction(saveSessionAct);
    fileToolBar->addAction(saveSessionAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction *saveSessionAsAct = fileMenu->addAction(
            saveAsIcon,
            tr("Save Session &As..."),
            this,
            &MainWindow::saveSessionAs
            );
    saveSessionAsAct->setShortcuts(QKeySequence::SaveAs);
    saveSessionAsAct->setStatusTip(tr("Save the session to a log file"));


    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(
            exitIcon,
            tr("E&xit"),
            this,
            &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

#ifndef QT_NO_CLIPBOARD
    const QIcon copyIcon = QIcon::fromTheme(
            "edit-copy",
            QIcon(":/images/copy.png")
            );
    QAction *copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, text_edit_, &QPlainTextEdit::copy);
    editMenu->addAction(copyAct);
    editToolBar->addAction(copyAct);

#endif

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(
            tr("&About"),
            this,
            &MainWindow::about
            );
    aboutAct->setStatusTip(tr("Show the application's About box"));

    QAction *aboutQtAct = helpMenu->addAction(
            tr("About &Qt"),
            qApp,
            &QApplication::aboutQt
            );
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
#ifndef QT_NO_CLIPBOARD
    copyAct->setEnabled(false);
    connect(
            text_edit_,
            &QPlainTextEdit::copyAvailable,
            copyAct,
            &QAction::setEnabled
            );
#endif // !QT_NO_CLIPBOARD
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(
            QCoreApplication::organizationName(),
            QCoreApplication::applicationName()
            );
    const QByteArray geometry = settings.value(
            "geometry",
            QByteArray()
            ).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(
            QCoreApplication::organizationName(),
            QCoreApplication::applicationName()
            );
    settings.setValue("geometry", saveGeometry());
}

bool MainWindow::maybeSave()
{
    if (!text_edit_->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(
                this,
                tr("Focus Precision Analyzer"),
                tr("The document has been modified.\n"
                   "Do you want to save your changes?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
                );
    switch (ret) {
    case QMessageBox::Save:
        return saveSession();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void MainWindow::loadLogFile(const QString &file_name)
{
//     QFile file(fileName);
//     if (!file.open(QFile::ReadOnly | QFile::Text)) {
//         QMessageBox::warning(this, tr("Application"),
//                              tr("Cannot read file %1:\n%2.")
//                              .arg(QDir::toNativeSeparators(fileName), file.errorString()));
//         return;
//     }
// 
//     QTextStream in(&file);
// #ifndef QT_NO_CURSOR
//     QGuiApplication::setOverrideCursor(Qt::WaitCursor);
// #endif
//     text_edit_->setPlainText(in.readAll());
// #ifndef QT_NO_CURSOR
//     QGuiApplication::restoreOverrideCursor();
// #endif
// 
//     setCurrentFile(fileName);
//     statusBar()->showMessage(tr("File loaded"), 2000);
    QFile log_file(file_name);
    if (!log_file.open(QFile::ReadOnly | QFile::Text)) {
        showMessage(
                tr("Cannot read file %1:\n").arg(
                    QDir::toNativeSeparators(file_name)
                    ),
                MainWindow::Error
                );
        showMessage(log_file.errorString(), MainWindow::Error);

        return;
    }

    showMessage(
            tr("Validating file: %1 ...").arg(
                QDir::toNativeSeparators(file_name)
                ),
            MainWindow::Info
            );

    // Validate file name by convention used for naming focus precision test
    // log files
    QString strip_fn = strippedFileName(file_name);
    QRegExp fn_pattern(
            "QAFocusPrecisionTest\\([0-9]{4}(-[0-9]{2}){2} "
            "([0-9]{2}\\.){2}[0-9]{2}\\)\\.rmd"
            );

    if(!fn_pattern.exactMatch(strip_fn)) {
        showMessage(
                tr("File name \"%1\" does not comply to focus precision test "
                   "log files naming convention.").arg(
                    QDir::toNativeSeparators(file_name)
                    ),
                MainWindow::Error
                );

        return;
    }

    // File name matches naming convention. Let's extract time and date of
    // log's creation
    bool result = true;
    QString date_string = strip_fn.mid(21, 10);
    QString time_string = strip_fn.mid(32, 8);

    QDate log_date(
            date_string.mid(0, 4).toInt(&result, 10),
            date_string.mid(5, 2).toInt(&result, 10),
            date_string.mid(8, 2).toInt(&result, 10)
            );
    QTime log_time(
            time_string.mid(0, 2).toInt(&result, 10),
            time_string.mid(3, 2).toInt(&result, 10),
            time_string.mid(6, 2).toInt(&result, 10)
            );

    showMessage(
            tr("Log date: ") + log_date.toString("d. MMMM yyyy"),
            MainWindow::Info
            );
    showMessage(
            tr("Log time: ") + log_time.toString("h:mm:ss"),
            MainWindow::Info
            );

    // Read file contents
    QTextStream in(&log_file);
    while (!in.atEnd()) {
        QString record = "| ";
        QString line = in.readLine();
        QStringList fields = line.split(", ");
        for (int i = 0; i < fields.size(); ++i) {
            record += fields.at(i) + " |";
        }
        showMessage(record, MainWindow::Info);

    }

}

bool MainWindow::saveSessionLog(const QString &file_name)
{
    QString error_message;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(file_name);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << text_edit_->toPlainText() << '\n';
        if (!file.commit()) {
            error_message = tr("Cannot write file %1:\n%2.").arg(
                    QDir::toNativeSeparators(file_name),
                    file.errorString()
                    );
        }
    } else {
        error_message = tr("Cannot open file %1 for writing:\n%2.").arg(
                QDir::toNativeSeparators(file_name),
                file.errorString()
                );
    }
    QGuiApplication::restoreOverrideCursor();

    if (!error_message.isEmpty()) {
        QMessageBox::warning(
                this,
                tr("Focus Precision Analyzer"),
                error_message
                );
        return false;
    }

    session_log_file_ = file_name;
    text_edit_->document()->setModified(false);
    setWindowTitle("Focus Precision Analyzer - " + session_title_);
    statusBar()->showMessage(session_title_ + tr(" saved"), 3000);
    return true;
}

void MainWindow::setSession()
{
    text_edit_->document()->setModified(false);
    setWindowModified(false);

    // Set default save and load directories
    session_save_dir_ = "./";
    last_log_dir_ = "./";

    // Initialize session title and session save name
    QDateTime now(QDateTime::currentDateTime());
    // session_title_ = tr("Session ") + now.toString("yyyy-MMM-dd hh.mm.ss");
    // setWindowTitle(session_title_ + " - Focus Precision Analyzer [*]");
    session_title_ = tr("Session ") + now.toString("yyyy-MMM-dd hh:mm:ss");
    setWindowTitle("Focus Precision Analyzer - " + session_title_ + " [*]");
    session_save_name_ = "Session "
        + now.toString("yyyy-MMM-dd hh.mm.ss")
        + ".log";

    // Set session welcome message
    showMessage(session_title_ + tr(" started ..."), MainWindow::Info);
}

QString MainWindow::strippedFileName(const QString &full_file_name)
{
    return QFileInfo(full_file_name).fileName();
}

#ifndef QT_NO_SESSIONMANAGER
void MainWindow::commitData(QSessionManager &manager)
{
    if (manager.allowsInteraction()) {
        if (!maybeSave())
            manager.cancel();
    } else {
        // Non-interactive: save without asking
        if (text_edit_->document()->isModified())
            saveSession();
    }
}
#endif
