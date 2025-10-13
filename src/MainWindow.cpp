#include "MainWindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QApplication>
#include <QHeaderView>
#include "Models/User.h"
#include "Models/Product.h"
#include "Models/Order.h"
#include "Models/OrderProduct.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("TinyOrmQtDemo");
    resize(1024, 768);

    setupTabs();
    setupMenu();
    loadData();
}

void MainWindow::setupTabs()
{
    tabWidget = new QTabWidget(this);

    // Products tab
    productsTable = new QTableWidget();
    productsTable->setColumnCount(3);
    productsTable->setHorizontalHeaderLabels({"Product ID", "Product", "Price"});
    productsTable->horizontalHeader()->setStretchLastSection(true);
    productsTable->verticalHeader()->setVisible(false);

    // Orders tab
    ordersTable = new QTableWidget();
    ordersTable->setColumnCount(4);
    ordersTable->setHorizontalHeaderLabels({"Order ID", "Customer", "Product", "Total"});
    ordersTable->horizontalHeader()->setStretchLastSection(true);
    ordersTable->verticalHeader()->setVisible(false);

    // Users tab
    usersTable = new QTableWidget();
    usersTable->setColumnCount(3);
    usersTable->setHorizontalHeaderLabels({"User ID", "Name", "Email"});
    usersTable->horizontalHeader()->setStretchLastSection(true);
    usersTable->verticalHeader()->setVisible(false);

    tabWidget->addTab(productsTable, "Products");
    tabWidget->addTab(ordersTable, "Orders");
    tabWidget->addTab(usersTable, "Users");

    setCentralWidget(tabWidget);
}

void MainWindow::loadData()
{
    // Load users
    auto users = Models::User::all();
    usersTable->setRowCount(users.size());
    for (int i = 0; i < users.size(); ++i) {
        usersTable->setItem(i, 0, new QTableWidgetItem(users[i].getAttribute<QString>("id")));
        usersTable->setItem(i, 1, new QTableWidgetItem(users[i].getAttribute<QString>("name")));
        usersTable->setItem(i, 2, new QTableWidgetItem(users[i].getAttribute<QString>("email")));
    }

    // Load products
    auto products = Models::Product::all();
    productsTable->setRowCount(products.size());
    for (int i = 0; i < products.size(); ++i) {
        productsTable->setItem(i, 0, new QTableWidgetItem(products[i].getAttribute<QString>("id")));
        productsTable->setItem(i, 1, new QTableWidgetItem(products[i].getAttribute<QString>("name")));
        productsTable->setItem(i, 2, new QTableWidgetItem(QString::number(products[i].getAttribute<double>("price"))));
    }

    // Load orders
    auto orders = Models::Order::with({"user", "products"})->get();
    ordersTable->setRowCount(orders.size());
    int i = 0;

    for (auto &order : orders) {
        Models::User *user = order.getRelation<Models::User, Orm::One>("user");
        QString productsSummary;
        
        for (auto *product : order.getRelation<Models::Product>("products")) {
            auto quantity = product->getRelation<Models::OrderProduct, Orm::One>("pivot")
              ->getAttribute<unsigned char>("quantity");
            productsSummary += QString::number(quantity) + "x " + product->getAttribute<QString>("name") + "; ";
        }
        
        ordersTable->setItem(i, 0, new QTableWidgetItem(QString::number(order.getAttribute<quint64>("id"))));
        ordersTable->setItem(i, 1, new QTableWidgetItem(user->getAttribute<QString>("name")));
        ordersTable->setItem(i, 2, new QTableWidgetItem(productsSummary)); 
        ordersTable->setItem(i, 3, new QTableWidgetItem(QString::number(order.getAttribute<double>("total"), 'f', 2))); 
        
        i++;
    }
}

void MainWindow::setupMenu()
{
    auto *fileMenu = menuBar()->addMenu("&File");

    QAction *aboutAction = new QAction("&About", this);
    QAction *logoutAction = new QAction("&Logout", this);
    QAction *quitAction = new QAction("&Quit", this);

    fileMenu->addAction(aboutAction);
    fileMenu->addAction(logoutAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    connect(logoutAction, &QAction::triggered, this, &MainWindow::logout);
    connect(quitAction, &QAction::triggered, this, &MainWindow::quitApp);
}

void MainWindow::showAbout()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About");
    aboutBox.setTextFormat(Qt::RichText);
    aboutBox.setText(R"(
    <b>TinyOrmQtDemo</b><br>
    © 2025<br><br>
    This application uses the Qt framework.<br>
    © The Qt Company Ltd.<br>
    Licensed under the GNU Lesser General Public License (LGPL) version 3.<br><br>
    You may obtain the Qt source code from:<br>
    <a href="https://www.qt.io/download">https://www.qt.io/download</a>
    )");
    aboutBox.exec();
}

void MainWindow::logout()
{
    QMessageBox::information(this, "Logout", "Logging out...");
    // Add logout logic here
}

void MainWindow::quitApp()
{
    QApplication::quit();
}
