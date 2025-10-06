#pragma once
#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showAbout();
    void logout();
    void quitApp();

private:
    void setupTabs();
    void setupMenu();

    QTabWidget *tabWidget;
    QTableWidget *productsTable;
    QTableWidget *ordersTable;
    QTableWidget *usersTable;
};
