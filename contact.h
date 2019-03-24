#ifndef CONTACT_H
#define CONTACT_H
#include <QString>
#include "message.h"
#include <vector>

class Contact
{
private:
    QString name;
    vector<Message> messages;
public:
    Contact();
    QString getName() const;
    void setName(const QString &value);
    vector<Message> getMessages() const;
    void setMessages(const vector<Message> &value);
};

#endif // CONTACT_H
