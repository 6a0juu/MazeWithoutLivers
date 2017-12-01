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
#include <bits/stdc++.h>
#include <QPainter>
#include "maze.h"
#include "window.h"

extern int path[300];

//! [0]
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    mazeH = mazeW = 0;
    blockSize = 2;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}
//! [0]

//! [1]
QSize RenderArea::minimumSizeHint() const
{
    return QSize(200, 300);
}
//! [1]

//! [2]
QSize RenderArea::sizeHint() const
{
    return QSize(800, 400);
}
//! [2]

//! [3]
void RenderArea::setBlockSize(qint8 blockSize)
{
    this->blockSize = blockSize;
    update();
}
//! [3]

void RenderArea::renderMaze(Maze* maze, int mazeH, int mazeW)
{
    this->mazeH = mazeH;
    this->mazeW = mazeW;
    this->maze = maze;
    update();
}

//! [8]
void RenderArea::paintEvent(QPaintEvent * /* event */)
{

    QRect rect(0, 0, blockSize - 1, blockSize - 1);
//! [8]

//! [9]
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
    painter.setPen(QPen(Qt::gray, Qt::SolidPattern));
    painter.setRenderHint(QPainter::Antialiasing, false);
//! [9]

//! [10]
    for (int x = 0; x <= mazeH && x <= width()/blockSize; x += 1) {
        for (int y = 0; y <= mazeW && y <= height()/blockSize; y += 1) {
            if(maze->getMat(x, y) == 0) {
                painter.save();
                painter.translate(x * blockSize, y * blockSize);
                painter.drawRect(rect);
                painter.restore();
            } else if (maze->getMat(x, y) == -1) {
                painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                painter.setPen(QPen(Qt::red, Qt::SolidPattern));
                painter.save();
                painter.translate(x * blockSize, y * blockSize);
                painter.drawRect(rect);
                painter.restore();
                painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
                painter.setPen(QPen(Qt::gray, Qt::SolidPattern));
            }
        }
    }
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
//! [10]
