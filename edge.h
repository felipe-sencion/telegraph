#ifndef EDGE_H
#define EDGE_H
#include <QString>

using namespace std;

class Edge
{
private:
    QString source;
    QString destiny;
    int weight;

public:
    Edge(QString s, QString d, int w);
    Edge &operator =(const Edge &other);

    QString getSource() const;
    void setSource(const QString &value);
    QString getDestiny() const;
    void setDestiny(const QString &value);
    int getWeight() const;
    void setWeight(int value);

    bool operator <(const Edge &obj) const;
    bool operator ==(const Edge &obj) const;
    bool operator <=(const Edge &obj) const;
};

#endif // EDGE_H
