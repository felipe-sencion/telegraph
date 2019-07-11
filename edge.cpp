#include "edge.h"

QString Edge::getSource() const
{
    return source;
}

void Edge::setSource(const QString &value)
{
    source = value;
}

QString Edge::getDestiny() const
{
    return destiny;
}

void Edge::setDestiny(const QString &value)
{
    destiny = value;
}

int Edge::getWeight() const
{
    return weight;
}

void Edge::setWeight(int value)
{
    weight = value;
}

bool Edge::operator <(const Edge &obj) const
{
    return weight < obj.weight;
}

bool Edge::operator ==(const Edge &obj) const
{
    return weight == obj.weight;
}

bool Edge::operator <=(const Edge &obj) const
{
    return (*this < obj || *this == obj);
}

Edge::Edge(QString s, QString d, int w)
{
    source = s;
    destiny = d;
    weight = w;
}

Edge &Edge::operator =(const Edge &other)
{
    source = other.source;
    destiny = other.destiny;
    weight = other.weight;
    return *this;
}
