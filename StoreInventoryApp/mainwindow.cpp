#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemdialog.h"
#include "updateitemdialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->menuNewProduct, &QAction::triggered,
            this, &MainWindow::handleMenuItemNew);

    connect(ui->btnRemove, &QPushButton::clicked,
            this, &MainWindow::removeSelectedProduct);

    connect(ui->lstProducts, &QListWidget::itemClicked,
            this, &MainWindow::handleItemClick);

    connect(ui->menuEditSelectedProduct, &QAction::triggered,
            this, &MainWindow::handleMenuItemEdit);

    connect(ui->menuExit, &QAction::triggered,
            this, &MainWindow::handleMenuExit);

    connect(ui->menuSaveProducts, &QAction::triggered,
            this, &MainWindow::handleSaveItems);

    connect(ui->menuLoadProducts, &QAction::triggered,
            this, &MainWindow::handleLoadItems);
}

MainWindow::~MainWindow()
{
    //free up product list memory
    for (int i=0; i<productList.size(); i++)
    {
        delete productList.at(i);
    }
    productList.clear();

    delete ui;
}

void MainWindow::handleMenuExit()
{
    QApplication::quit();
}

void MainWindow::handleMenuItemNew()
{
    Item* newItem = nullptr;
    AddItemDialog addItemDialog(newItem, nullptr);

    addItemDialog.setModal(true);
    addItemDialog.exec();

    if (newItem != nullptr)
    {
        productList.push_back(newItem);
        ui->lstProducts->addItem(newItem->getName());
    }
} //end handleMenuItemNew

void MainWindow::removeSelectedProduct()
{
    int index = ui->lstProducts->currentRow();

    if (index >= 0)
    {
        //remove from vector
        Item* theItem = productList.at(index);
        delete theItem;
        productList.removeAt(index);

        //remove from list widget in the UI
        delete ui->lstProducts->currentItem();
    }
    ui->lblProductName->setText("");
    ui->lblQuantity->setText("");
    QPixmap pixmap("./images/none.png");
    ui->lblImage->setPixmap(pixmap);
} //end removeSelectedProduct

void MainWindow::handleItemClick(QListWidgetItem* item)
{
    int index = item->listWidget()->currentRow();

    if (index != -1)
    {
        Item* currentItem = productList.at(index);

        if (currentItem != nullptr)
        {
            ui->lblProductName->setText(currentItem->getName());

            ui->lblQuantity ->setText(QString::number(currentItem->getQuantity()));

            QPixmap pixmap(currentItem->getImageFilePath());

            ui->lblImage->setPixmap(pixmap);

            ui->lblImage->setScaledContents(true);
        } //end inner if
    } //end if
}// end handle item click

void MainWindow::handleMenuItemEdit()
{
    int index = ui->lstProducts->currentRow();

    if (index != -1)
    {
        Item* currentItem = productList.at(index);

        if (currentItem != nullptr)
        {
            UpdateItemDialog updateItemDialog(currentItem, nullptr);
            updateItemDialog.exec();

            //make sure UI is updated
            ui->lblProductName->setText(currentItem->getName());
            ui->lblQuantity->setText(QString::number(currentItem->getQuantity()));

            QPixmap pixmap(currentItem->getImageFilePath());
            ui->lblImage->setPixmap(pixmap);
            ui->lblImage->setScaledContents(true);
        }//end inner if
    }//end if

}//end handleMenuItemEdit

void MainWindow::handleSaveItems()
{
    QFile outputFile("products.txt");

    outputFile.open(QIODevice::WriteOnly |
                    QIODevice::Text);

    QTextStream out(&outputFile);

    for(int i=0; i<productList.size(); i++)
    {
        out << productList.at(i)->getName()<<",";
        out <<productList.at(i)->getQuantity()<<",";
        out << productList.at(i)->getImageFilePath()<<endl;
    }

}
void MainWindow::handleLoadItems()
{
    QFile inputFile("products.txt");
    inputFile.open(QIODevice::ReadOnly |
                   QIODevice::Text);

    QTextStream in(&inputFile);

    //clear current list and vector
    for (int i=0; i<productList.size(); i++)
    {
        delete productList.at(i);
    }

    productList.clear(); //clear data model
    ui->lstProducts->clear(); // view / ui

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList info = line.split(",");

        //handle list of products ui
        ui->lstProducts->addItem(info.at(0));

        //handle vector
        Item* product = new Item(info.at(0), info.at(1).toInt(),info.at(2));
        productList.push_back(product);
    } //end while

    in.flush();
    inputFile.close();
}
