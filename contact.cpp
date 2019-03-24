#include "contact.h"

QString Contact::getName() const
{
    return name;
}

void Contact::setName(const QString &value)
{
    name = value;
}

vector<Message> Contact::getMessages() const
{
    return messages;
}

void Contact::setMessages(const vector<Message> &value)
{
    messages = value;
}

Contact::Contact()
{

}
