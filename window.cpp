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

#include "renderarea.h"
#include "window.h"
#include "maze.h"

#include <QtWidgets>
#include <QMessageBox>
#include <bits/stdc++.h>

// QDockArea to be done

//! [0]
const int IdRole = Qt::UserRole;
//! [0]

Window::Window()
{
    renderArea = new RenderArea;
    maze = new Maze;

    QSize ts = QSize(40,20);
    stXEdit = new QLineEdit;
    stXEdit->setMaximumSize(ts);
    edXEdit = new QLineEdit;
    edXEdit->setMaximumSize(ts);
    stYEdit = new QLineEdit;
    stYEdit->setMaximumSize(ts);
    edYEdit = new QLineEdit;
    edYEdit->setMaximumSize(ts);
    xEdit = new QLineEdit;
    xEdit->setMaximumSize(ts);
    yEdit = new QLineEdit;
    yEdit->setMaximumSize(ts);

    stLabel = new QLabel(tr("Starting point:"));
    stLabel->setBuddy(stXEdit);
    edLabel = new QLabel(tr("Ending point:"));
    edLabel->setBuddy(edXEdit);
    xLabel = new QLabel(tr("Maze Width:"));
    xLabel->setBuddy(xEdit);
    yLabel = new QLabel(tr("Maze Height:"));
    yLabel->setBuddy(yEdit);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(renderArea);
    //renderArea->setGeometry(0, 0, 200, 200);

    openBtn = new QPushButton;
    openBtn->setText(QString::fromLocal8Bit("Open "));

//! [2]
    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(2, 10);

    penWidthLabel = new QLabel(tr("Additional Size:"));
    penWidthLabel->setBuddy(penWidthSpinBox);
//! [2]

    saveBtn = new QPushButton;
    saveBtn->setText(QString::fromLocal8Bit("Save "));

    solvBtn = new QPushButton;
    solvBtn->setText(QString::fromLocal8Bit("Solve"));

    formBtn = new QPushButton;
    formBtn->setText(QString::fromLocal8Bit("Form "));

//! [3]

//! [8]
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(sizeChanged()));
    connect(openBtn, SIGNAL(released()),
            this, SLOT(openMaze()));
    connect(saveBtn, SIGNAL(released()),
            this, SLOT(saveMaze()));
    connect(formBtn, SIGNAL(released()),
            this, SLOT(formMaze()));
    connect(solvBtn, SIGNAL(released()),
            this, SLOT(solvMaze()));
//! [8]

//! [9]
    QGridLayout *mainLayout = new QGridLayout;
//! [9] //! [10]
    mainLayout->setColumnStretch(0,2);
    mainLayout->setColumnStretch(1,2);
    mainLayout->setColumnStretch(2,20);
    mainLayout->setColumnStretch(3,2);
    mainLayout->setColumnStretch(4,1);
    mainLayout->setColumnStretch(5,1);

    mainLayout->addWidget(scrollArea, 0, 0, 20, 3);
    mainLayout->addWidget(openBtn, 0, 3, Qt::AlignCenter);
    mainLayout->addWidget(saveBtn, 1, 3, Qt::AlignCenter);

    mainLayout->addWidget(formBtn, 3, 3, Qt::AlignCenter);
    mainLayout->addWidget(xLabel, 4, 3, Qt::AlignRight);
    mainLayout->addWidget(xEdit, 4, 4, Qt::AlignRight);
    mainLayout->addWidget(yLabel, 5, 3, Qt::AlignRight);
    mainLayout->addWidget(yEdit, 5, 4, Qt::AlignRight);

    mainLayout->addWidget(solvBtn, 7, 3, Qt::AlignCenter);

    mainLayout->addWidget(stLabel, 8, 3, Qt::AlignRight);
    mainLayout->addWidget(stXEdit, 8, 4, Qt::AlignRight);
    mainLayout->addWidget(stYEdit, 8, 5, Qt::AlignRight);

    mainLayout->addWidget(edLabel, 9, 3, Qt::AlignRight);
    mainLayout->addWidget(edXEdit, 9, 4, Qt::AlignRight);
    mainLayout->addWidget(edYEdit, 9, 5, Qt::AlignRight);


    mainLayout->addWidget(penWidthLabel, 20, 0, Qt::AlignLeft);
    mainLayout->addWidget(penWidthSpinBox, 20, 1, Qt::AlignLeft);
    setLayout(mainLayout);

    setWindowTitle(tr("Maze without Livers"));
}
//! [10]

//! [11]
void Window::sizeChanged()
{
    renderArea->setGeometry(0, 0, 27 + penWidthSpinBox->value() * mazeX, 27 + penWidthSpinBox->value() * mazeY);
    scrollArea->setGeometry(0, 0, std::min(1020, 30 + penWidthSpinBox->value() * mazeX), std::min(700, 30 + penWidthSpinBox->value() * mazeY));
    renderArea->setBlockSize(penWidthSpinBox->value());
}
//! [11]

//! [17]

void Window::openMaze()
{
    openFD = new QFileDialog(this, tr("Open File"));
    openFD->setFileMode(QFileDialog::ExistingFile);
    openFD->setDirectory(".");
    openFD->setNameFilter(tr("Maze Files(*.maze)"));
    if(openFD->exec() == QDialog::Accepted) {
        QString path = openFD->selectedFiles()[0];
        QByteArray trans = path.toLatin1();
        char *strP = trans.data();
        freopen(strP, "r", stdin);
        std::cin >> mazeX >> mazeY;
        bool tVal;
        for (int i = 0; i <= mazeX; i++) {
            for (int j = 0; j <= mazeY; j++) {
                std::cin >> tVal;
                maze->setMat(i, j, (bool)tVal);
            }
        }
        renderArea->setGeometry(0, 0, 27 + penWidthSpinBox->value() * mazeX, 27 + penWidthSpinBox->value() * mazeY);
        scrollArea->setGeometry(0, 0, std::min(1020, 30 + penWidthSpinBox->value() * mazeX), std::min(700, 30 + penWidthSpinBox->value() * mazeY));
        renderArea->renderMaze(maze, mazeX, mazeY);
    }
}

void Window::saveMaze()
{
    saveFD = new QFileDialog(this, tr("Save File"));
    saveFD->setDirectory(".");
    saveFD->setAcceptMode(QFileDialog::AcceptSave);
    saveFD->setNameFilter(tr("Maze Files(*.maze)"));
    if(saveFD->exec() == QDialog::Accepted){
        QString path = saveFD->selectedFiles()[0];
        QByteArray trans = path.toLatin1();
        char *strP = trans.data();
        freopen(strP, "w", stdout);
        std::cout << mazeX << ' ' << mazeY << std::endl;
        for (int i = 0; i <= mazeX; i++) {
            for (int j = 0; j <= mazeY; j++) {
                if (maze->getMat(i ,j) == -1) std::cout << 0 << " ";
                else std::cout << maze->getMat(i ,j) << " ";
            }
            std::cout << std::endl;
        }
    }
}

void Window::formMaze(void)
{
    QString t1 = xEdit->text();
    mazeX = t1.toInt() * 2;
    QString t2 = yEdit->text();
    mazeY = t2.toInt() * 2;
    maze->mazeGen(mazeX / 2, mazeY / 2, 1, 1);
    renderArea->setGeometry(0, 0, 27 + penWidthSpinBox->value() * mazeX, 27 + penWidthSpinBox->value() * mazeY);
    scrollArea->setGeometry(0, 0, std::min(1200, 30 + penWidthSpinBox->value() * mazeX), std::min(700, 30 + penWidthSpinBox->value() * mazeY));
    renderArea->renderMaze(maze, mazeX, mazeY);
}

void Window::solvMaze(void)
{
    QString t1 = stXEdit->text();
    QString t2 = stYEdit->text();
    QString t3 = edXEdit->text();
    QString t4 = edYEdit->text();
    maze->findPath(t1.toInt(), t2.toInt(), t3.toInt(), t4.toInt());
    renderArea->renderMaze(maze, mazeX, mazeY);
}
