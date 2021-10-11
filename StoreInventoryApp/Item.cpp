#include "Item.h"

Item::Item(QString name, int quantity, QString imageFilePath)
{
    this->name = name;
    this->quantity = quantity;
    this->imageFilePath = imageFilePath;
}

void Item::setName(QString name)
{
    this->name = name;
}

QString Item::getName() const
{
    return name;
}

void Item::setQuantity(int quanity)
{
    this->quantity = quanity;
}

int Item::getQuantity() const
{
    return quantity;
}

void Item::setImageFilePath(QString imageFilePath)
{
    this->imageFilePath = imageFilePath;
}

QString Item::getImageFilePath() const
{
    return imageFilePath;
}
