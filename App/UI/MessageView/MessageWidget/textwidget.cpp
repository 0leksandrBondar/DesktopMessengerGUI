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

#include "textwidget.h"

#include <QLabel>
#include <QVBoxLayout>

TextWidget::TextWidget(QWidget* parent) : QWidget(parent), _text{ new QLabel(this) }
{
    setStyleSheet("border: 0px solid black; background-color: black;");
    initializeLayout();
    setupLabelStyle();
}

void TextWidget::setText(const QString& text)
{
    _text->setText(text);

    const int textWidth = computeTextWidth(text);

    constexpr int minWidth = 50;
    constexpr int maxWidth = 400;

    const int targetWidth = std::clamp(textWidth, minWidth, maxWidth);

    _text->setMinimumWidth(targetWidth);
    _text->setMaximumWidth(targetWidth);

    _text->setWordWrap(true);

    updateGeometry();
}

void TextWidget::initializeLayout()
{
    const auto mainLayout{ new QVBoxLayout() };
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(1, 1, 1, 1);

    mainLayout->addWidget(_text);

    _text->setWordWrap(true);

    setLayout(mainLayout);
}

int TextWidget::computeTextWidth(const QString& text) const
{
    QFontMetrics fm(_text->font());
    return fm.horizontalAdvance(text);
}

void TextWidget::setupLabelStyle() const
{
    QFont font;
    font.setPointSize(12);
    _text->setFont(font);
    _text->setWordWrap(true);
}
