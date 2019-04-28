#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include <QDateTime>

using namespace std;

class Message
{
private:
    QString text;
    QDateTime dateTime;

public:
    Message();
    QString getText() const;
    void setText(const QString &value);
    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &value);
    bool operator <(const Message &obj) const;
    bool operator ==(const Message &obj) const;
    bool operator <=(const Message &obj) const;
    bool operator >(const Message &obj) const;
};

#endif // MESSAGE_H
