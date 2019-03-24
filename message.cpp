#include "message.h"

QString Message::getText() const
{
    return text;
}

void Message::setText(const QString &value)
{
    text = value;
}

QDateTime Message::getDateTime() const
{
    return dateTime;
}

void Message::setDateTime(const QDateTime &value)
{
    dateTime = value;
}

Message::Message()
{

}
