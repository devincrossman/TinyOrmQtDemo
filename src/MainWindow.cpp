#include "MainWindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QApplication>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("TinyOrmQtDemo");
    resize(1024, 768);

    setupTabs();
    setupMenu();
}

void MainWindow::setupTabs()
{
    tabWidget = new QTabWidget(this);

    // Products tab
    productsTable = new QTableWidget();
    productsTable->setColumnCount(2);
    productsTable->setHorizontalHeaderLabels({"Product", "Price"});
    productsTable->horizontalHeader()->setStretchLastSection(true);

    // Orders tab
    ordersTable = new QTableWidget();
    ordersTable->setColumnCount(3);
    ordersTable->setHorizontalHeaderLabels({"Order ID", "Customer", "Total"});
    ordersTable->horizontalHeader()->setStretchLastSection(true);

    // Users tab
    usersTable = new QTableWidget();
    usersTable->setColumnCount(2);
    usersTable->setHorizontalHeaderLabels({"Name", "Email"});
    usersTable->horizontalHeader()->setStretchLastSection(true);

    tabWidget->addTab(productsTable, "Products");
    tabWidget->addTab(ordersTable, "Orders");
    tabWidget->addTab(usersTable, "Users");

    setCentralWidget(tabWidget);
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
    QMessageBox::information(this, "About", "TinyOrmQtDemo\n© 2025");
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
