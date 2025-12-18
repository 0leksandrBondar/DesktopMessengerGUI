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

#include "inpumessagefield.h"

#include "UI/MessageView/ChatViewWidget/chatviewwidget.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStandardPaths>
#include <QTextEdit>

#include <qevent.h>

InputMessageField::InputMessageField(QWidget* parent)
    : QWidget(parent),
      _inputField{ new QTextEdit(this) },
      _sendButton{ new QPushButton("Send", this) },
      _fileExplorerButton{ new QPushButton("...", this) }
{
    setupUi();
    setupConnections();
}

void InputMessageField::setupUi()
{
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto* fileButtonLayout = new QVBoxLayout();
    fileButtonLayout->setContentsMargins(0, 0, 0, 0);
    fileButtonLayout->addWidget(_fileExplorerButton);
    fileButtonLayout->setAlignment(Qt::AlignBottom);

    auto* sendButtonLayout = new QVBoxLayout();
    sendButtonLayout->setContentsMargins(0, 0, 0, 0);
    sendButtonLayout->addWidget(_sendButton);
    sendButtonLayout->setAlignment(Qt::AlignBottom);

    auto* inputFieldLayout = new QVBoxLayout();
    inputFieldLayout->setContentsMargins(0, 0, 0, 0);
    inputFieldLayout->addWidget(_inputField, 1);
    inputFieldLayout->setAlignment(Qt::AlignBottom);

    mainLayout->addLayout(fileButtonLayout);
    mainLayout->addLayout(inputFieldLayout, 1);
    mainLayout->addLayout(sendButtonLayout);

    setLayout(mainLayout);

    setStyleSheet("background-color: black; color: white;");

    _sendButton->setFixedHeight(40);
    _fileExplorerButton->setFixedHeight(40);

    QFont font;
    font.setPointSize(14);
    _inputField->setFont(font);
    _inputField->setFontPointSize(14);
    _inputField->setPlaceholderText("Write a message...");
    _inputField->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _inputField->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedHeight(40);
}

void InputMessageField::autoResizeWidget()
{
    int docHeight = static_cast<int>(_inputField->document()->size().height());

    if (docHeight > 300)
        docHeight = 300;
    if (docHeight < 40)
        docHeight = 40;

    setFixedHeight(docHeight);
}

void InputMessageField::setupConnections()
{
    connect(_inputField, &QTextEdit::textChanged, this, &InputMessageField::autoResizeWidget);
    connect(_sendButton, &QPushButton::clicked, this, &InputMessageField::onSendButtonClicked);
    connect(_fileExplorerButton, &QPushButton::clicked, this,
            &InputMessageField::onFileExplorerButtonCLicked);
}

void InputMessageField::onSendButtonClicked()
{
    MessageData data;

    if (!_inputField->toPlainText().isEmpty())
        data.textMessage = _inputField->toPlainText();

    if (!_filePath.isEmpty())
        data.filePath = _filePath;

    emit sendButtonClicked(data);
    _inputField->clear();
}

void InputMessageField::onFileExplorerButtonCLicked()
{
    static const QString filter
        = "Image files (*.avif *.avifs *.bmp *.gif *.heic *.heif *.jpeg *.jpg *.jxl *.pbm *.pgm "
          "*.png *.ppm *.qoi *.webp *.xbm *.xpm);;All files (*.*)";

    static const QString downloadsPath
        = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    _filePath = QFileDialog::getOpenFileName(this, "Select an image", downloadsPath, filter);

    if (!_filePath.isEmpty())
    {
        qDebug() << "Selected file:" << _filePath;
    }
}
void InputMessageField::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if (event->modifiers() & Qt::ControlModifier)
            onSendButtonClicked();
    }
}
