#include "updateitemdialog.h"
#include "ui_updateitemdialog.h"

#include <QFileDialog>
#include <QMessageBox>

UpdateItemDialog::UpdateItemDialog(Item* currentItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateItemDialog)
{
    ui->setupUi(this);
    this->currentItem = currentItem;

    if (currentItem != nullptr)
    {
        ui->lblItemName->setText(currentItem->getName());
        QPixmap pixmap(currentItem->getImageFilePath());
        ui->lblImage->setPixmap(pixmap);
        ui->lblImage->setScaledContents(true);

        ui->sbQuantity->setValue(currentItem->getQuantity());

        imageFilePath = currentItem->getImageFilePath();
    }

    //connection
    connect(ui->btnConfirmEdit, &QPushButton::clicked,
            this, &UpdateItemDialog::confirmUpdate);

    connect(ui->btnLoadItemImage, &QPushButton::clicked,
            this, &UpdateItemDialog::loadItemImage);
}

UpdateItemDialog::~UpdateItemDialog()
{
    delete ui;
}

void UpdateItemDialog::confirmUpdate()
{
    int quantity = ui->sbQuantity->value();

    if (quantity >= 1)
    {
        currentItem->setQuantity(quantity);
        currentItem->setImageFilePath(imageFilePath);
        this->close();
    }
    else
    {
        QMessageBox mb;
        mb.setText("Quantity must be at least 1.");
        mb.exec();
    }

}//end confirmUpdate

void UpdateItemDialog::loadItemImage()
{
    QString filename;

    filename = QFileDialog::getOpenFileName(this,
                                            "Open Image", "./",
                                            "Image Files (*.png *.jpg)");

    if (filename != "")
    {
        int lastSlash = filename.lastIndexOf("/");
        QString shortName = filename.right(filename.size() - lastSlash - 1);

        QFile::copy(filename, "./images" + shortName);
        QPixmap pixmap("./images/" + shortName);

        ui->lblImage->setPixmap(pixmap);
        ui->lblImage->setScaledContents(true);

        //update internal data
        imageFilePath = "./images" + shortName;
    } //end if
}//end loadItemImage
