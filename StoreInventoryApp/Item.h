#ifndef ITEM_H
#define ITEM_H
#include <QString>


class Item
{
public:
    Item(QString name, int quantity, QString imageFilePath = "none.png");

    void setName(QString name);
    QString getName() const;

    void setQuantity(int quanity);
    int getQuantity() const;

    void setImageFilePath(QString imageFilePath);
    QString getImageFilePath() const;

private:
    QString name;
    int quantity;
    QString imageFilePath;

};

#endif // ITEM_H
