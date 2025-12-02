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

#include "chatviewwidget.h"

#include "UI/MessageView/MessageWidget/messagewidget.h"

#include <QListWidget>
#include <QVBoxLayout>

#include <UI/MessageView/MessageWidget/messagebuilder.h>

ChatViewWidget::ChatViewWidget(QWidget* parent)
    : QWidget(parent), _messageList{ new QListWidget(this) }
{
    setupUi();
}

void ChatViewWidget::addMessage(const MessageData& msg, const bool isMyMsg)
{
    if (msg.textMessage.isEmpty())
        return;

    auto* container = new QWidget();
    auto* item = new QListWidgetItem();
    auto* widget = MessageBuilder::createWidget(msg);
    auto* hLayout = new QHBoxLayout(container);

    const auto hAlign = isMyMsg ? Qt::AlignRight : Qt::AlignLeft;

    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addStretch();

    if (isMyMsg)
        hLayout->addWidget(widget, 0, Qt::AlignRight);
    else
        hLayout->insertWidget(0, widget, 0, Qt::AlignLeft);

    _messageList->setResizeMode(QListView::Adjust);
    _messageList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    item->setSizeHint(widget->sizeHint());
    item->setTextAlignment(hAlign | Qt::AlignVCenter);

    _messageList->addItem(item);
    _messageList->setItemWidget(item, container);
}

void ChatViewWidget::setupUi()
{
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(_messageList);
    setLayout(mainLayout);
    setStyleSheet("background-color: black;");
}
