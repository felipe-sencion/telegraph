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

bool Message::operator <(const Message &obj) const
{
    return dateTime < obj.getDateTime();
}

bool Message::operator ==(const Message &obj) const
{
    return dateTime == obj.getDateTime();
}

bool Message::operator <=(const Message &obj) const
{
    return (*this < obj || *this == obj);
}

bool Message::operator >(const Message &obj) const
{
    return dateTime > obj.getDateTime();
}

Message::Message()
{

}
