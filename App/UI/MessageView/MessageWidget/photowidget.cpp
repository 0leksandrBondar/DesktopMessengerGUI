// MIT License

// Copyright (c) 2025 Oleksandr

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "photowidget.h"

#include <QFileInfo>
#include <QVBoxLayout>

#include <qevent.h>

PhotoWidget::PhotoWidget(QWidget* parent, const QString& fileName) : _imageLabel{ new QLabel }
{
    initializeLayout();

    setStyleSheet("border: 0px solid black; background-color: red;");

    setMinimumSize(400, 200);

    if (!fileName.isEmpty())
        createImage(fileName);
}

void PhotoWidget::loadImage(const QString& filePath) { createImage(filePath); }

void PhotoWidget::initializeLayout()
{
    const auto mainLayout{ new QVBoxLayout() };
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(1, 1, 1, 1);

    setLayout(mainLayout);
}

void PhotoWidget::createImage(const QString& fileName)
{
    QPixmap pixmap;
    if (!pixmap.load(fileName))
    {
        qWarning() << "Failed to load image:" << fileName;
        return;
    }

    _imageLabel->setMinimumSize(400, 300);
    _imageLabel->setMaximumSize(400, 700);

    QPixmap scaled
        = pixmap.scaled(_imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    _imageLabel->setPixmap(scaled);
    _imageLabel->setAlignment(Qt::AlignCenter);

    layout()->addWidget(_imageLabel);
}

void PhotoWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _popupDisplay = new QWidget();
        _popupDisplay->setWindowFlags(Qt::Popup);
        _popupDisplay->setWindowOpacity(0.5);
        _popupDisplay->showFullScreen();
    }
}
