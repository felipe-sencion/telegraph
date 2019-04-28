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

bool Contact::operator <(const Contact &obj) const
{
    Message thisLast = this->getMessages().at(this->getMessages().size()-1);
    Message objLast = obj.getMessages().at(obj.getMessages().size()-1);
    return thisLast > objLast;
}

bool Contact::operator ==(const Contact &obj) const
{
    Message thisLast = this->getMessages().at(this->getMessages().size()-1);
    Message objLast = obj.getMessages().at(obj.getMessages().size()-1);
    return thisLast == objLast;
}

Contact::Contact()
{

}
