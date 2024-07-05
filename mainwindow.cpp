#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setWindowTitle("Password Generator v1.0");
}

MainWindow::~MainWindow()
{
    delete ui;
}
