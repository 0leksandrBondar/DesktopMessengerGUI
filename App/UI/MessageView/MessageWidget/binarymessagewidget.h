#pragma once

#include <QWidget>

enum class BinaryMessageType
{
    Image,
    Video
};

class BinaryMessageWidget : public QWidget
{
public:
private:
protected:
    BinaryMessageType _type;
};