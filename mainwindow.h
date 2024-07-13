#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateLengthLabel(int length);

    void on_generateButton_clicked();

    void on_copyPasswordButton_clicked();

    void on_togglePasswordButton_clicked();

    void showAboutQtDialog();

    void showAboutPasswordGeneratorDialog();

private:
    Ui::MainWindow *ui;
    QString generatePassword(int length, bool includeSymbols, bool includeUppercase, bool includeNumbers);
    bool passwordVisible;
};
#endif // MAINWINDOW_H
