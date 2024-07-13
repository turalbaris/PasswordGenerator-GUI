#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QRandomGenerator>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , passwordVisible(true)
{
    ui->setupUi(this);
	this->setWindowTitle("Password Generator v1.0");

    // Initialize slider
    ui->lengthSlider->setMinimum(6);
    ui->lengthSlider->setMaximum(40);
    ui->lengthSlider->setValue(32); // Default value

    // Set checkboxes to default true
    ui->includeSymbolsCheckBox->setChecked(true);
    ui->includeUppercaseCheckBox->setChecked(true);
    ui->includeNumbersCheckBox->setChecked(true);

    // Connect slider valueChanged signal to updateLengthLabel slot
    connect(ui->lengthSlider, &QSlider::valueChanged, this, &MainWindow::updateLengthLabel);

    // Update lengthLabel initially
    updateLengthLabel(ui->lengthSlider->value());

    // Generate initial password
    on_generateButton_clicked();

    // Create a menu
    QMenu *aboutMenu = menuBar()->addMenu(tr("About"));

    // Action "About Qt"
    QAction *aboutQtAction = aboutMenu->addAction(tr("About Qt"));
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::showAboutQtDialog);

    // Action "About Password Generator"
    QAction *aboutPasswordGeneratorAction = aboutMenu->addAction(tr("About Password Generator"));
    connect(aboutPasswordGeneratorAction, &QAction::triggered, this, &MainWindow::showAboutPasswordGeneratorDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLengthLabel(int length)
{
    ui->lengthLabel->setText(QString("Password Length: %1").arg(length));
}

void MainWindow::on_generateButton_clicked()
{
    int length = ui->lengthSlider->value();
    bool includeSymbols = ui->includeSymbolsCheckBox->isChecked();
    bool includeUppercase = ui->includeUppercaseCheckBox->isChecked();
    bool includeNumbers = ui->includeNumbersCheckBox->isChecked();

    // Generate password based on current settings
    QString password = generatePassword(length, includeSymbols, includeUppercase, includeNumbers);
    ui->passwordLineEdit->setText(password);
}

void MainWindow::on_copyPasswordButton_clicked()
{
    QString password = ui->passwordLineEdit->text();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(password);

    // Show copy feedback on the button
    ui->copyPasswordButton->setText("Copied");

    // Clear the feedback after a short delay
    QTimer::singleShot(1300, this, [this]() {
        ui->copyPasswordButton->setText("Copy Password");
    });
}

QString MainWindow::generatePassword(int length, bool includeSymbols, bool includeUppercase, bool includeNumbers)
{
    // Define character sets for password generation
    const QString lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
    const QString uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const QString numbers = "0123456789";
    const QString symbols = "!@#$%^&*()-_=+[]{};:'\",.<>?/|\\`~";

    // Combine character sets based on checkbox settings
    QString allCharacters = lowercaseLetters;
    if (includeUppercase) allCharacters += uppercaseLetters;
    if (includeNumbers) allCharacters += numbers;
    if (includeSymbols) allCharacters += symbols;

    // Generate the password randomly
    QString password;
    for (int i = 0; i < length; ++i)
    {
        int index = QRandomGenerator::global()->bounded(allCharacters.length());
        password.append(allCharacters.at(index));
    }

    return password;
}

void MainWindow::on_togglePasswordButton_clicked()
{
    if (passwordVisible) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        ui->togglePasswordButton->setIcon(QIcon(":/icons/eye_slash.png"));
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->togglePasswordButton->setIcon(QIcon(":/icons/eye.png"));
    }
    passwordVisible = !passwordVisible; // Toggle state
}

void MainWindow::showAboutQtDialog()
{
    QMessageBox::aboutQt(this, "About Qt");
}


void MainWindow::showAboutPasswordGeneratorDialog()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About This Application");
    aboutBox.setTextFormat(Qt::RichText);  // Set text format to rich text to enable HTML content
    aboutBox.setText(
        "Version: 1.0<br>"
        "Developed by: Baris TURAL<br>"
        "For more information, visit my "
        "<a href='https://www.linkedin.com/in/baristural'>LinkedIn</a> and "
        "<a href='https://github.com/turalbaris'>GitHub</a> profiles."
        );
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.setStandardButtons(QMessageBox::Ok);
    aboutBox.exec();
}

