#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./backend/calculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    converter = {
        {ui->asin->objectName(), "asin ("}, {ui->sin->objectName(), "sin ("}, {ui->acos->objectName(), "acos ("},
        {ui->cos->objectName(), "cos ("}, {ui->tan->objectName(), "tan ("}, {ui->atan->objectName(), "atan ("},
        {ui->sqrt->objectName(), "sqrt ("}, {ui->pow->objectName(), "^"}, {ui->log->objectName(), "log ("},
        {ui->nat_log->objectName(), "ln ("}, {ui->number_0->objectName(), "0"}, {ui->number_1->objectName(), "1"},
        {ui->number_2->objectName(), "2"}, {ui->number_3->objectName(), "3"}, {ui->number_4->objectName(), "4"},
        {ui->number_5->objectName(), "5"}, {ui->number_6->objectName(), "6"}, {ui->number_7->objectName(), "7"},
        {ui->number_8->objectName(), "8"}, {ui->number_9->objectName(), "9"}, {ui->number_x->objectName(), "x"},
        {ui->open_bracket->objectName(), "("}, {ui->close_bracket->objectName(), ")"}, {ui->sum->objectName(), "+"},
        {ui->sub->objectName(), "-"}, {ui->mul->objectName(), "*"}, {ui->div->objectName(), "/"},
        {ui->mod->objectName(), "mod"}, {ui->point->objectName(), "."}, {ui->exponent->objectName(), "e"},
        {ui->pi->objectName(), "3.14"},
    };

    connect(ui->asin, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->sin, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->acos, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->cos, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->tan, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->atan, SIGNAL(clicked()), this, SLOT(pressing_button()));

    connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->pow, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->log, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->nat_log, SIGNAL(clicked()), this, SLOT(pressing_button()));

    connect(ui->number_0, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_1, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_2, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_3, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_4, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_5, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_6, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_7, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_8, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_9, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->number_x, SIGNAL(clicked()), this, SLOT(pressing_button()));

    connect(ui->clear, SIGNAL(clicked()), this, SLOT(clear_expression()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(cancel_action()));

    connect(ui->open_bracket, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->close_bracket, SIGNAL(clicked()), this, SLOT(pressing_button()));

    connect(ui->sum, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->sub, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->div, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->mul, SIGNAL(clicked()), this, SLOT(pressing_button()));
    connect(ui->mod, SIGNAL(clicked()), this, SLOT(pressing_button()));

    connect(ui->calc_exp, SIGNAL(clicked()), this, SLOT(calc_expression()));

    connect(ui->point, SIGNAL(clicked()), this, SLOT(pressing_button()));
//    connect(ui->negate, SIGNAL(clicked()), this, SLOT(pressing_button()));
//    connect(ui->exponent, SIGNAL(clicked()), this, SLOT(pressing_button()));
    ui->negate->setDisabled(true);
    ui->exponent->setDisabled(true);

    connect(ui->pi, SIGNAL(clicked()), this, SLOT(pressing_button()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
#include<QDebug>

void MainWindow::pressing_button() {
    QPushButton* button = (QPushButton*)sender();

    if (this->isResult)
        this->clear_expression();

    QString text = this->ui->expression->text();
    QString newText = this->converter[button->objectName()];

    if (text.length()) {
        QChar lastSim = text[text.length() - 1];
        QChar curSim = newText[newText.length() - 1];

        if (((curSim == 'e') && this->lastString.indexOf("e") != -1) ||
                (curSim == 'e' && lastSim == '.') ||
                (curSim == '.' && lastSim == 'e') ||
                (newText.indexOf(".") != -1 && this->lastString.indexOf(".") != -1))
            return;

        if (((lastSim.isDigit() || lastSim == 'e' || lastSim == '.') && curSim.isDigit()) ||
                (lastSim.isDigit() && (curSim == 'e' || curSim == '.'))) {
            this->ui->expression->setText(text + newText);
            this->lastString += newText;
        } else {
            this->ui->expression->setText(text + " " + newText);
            this->lastString = newText;
        }
    } else {
        this->ui->expression->setText(newText);
        this->lastString = newText;
    }
}

void MainWindow::clear_expression() {
    this->ui->expression->setText(this->lastString);
    this->isResult = false;
    this->lastString = "";
}

void MainWindow::cancel_action() {
    if (!this->isResult) {
        QString text = this->ui->expression->text();

        int index = text.lastIndexOf(" ");
        if (index == -1) {
            clear_expression();
        } else {
            this->ui->expression->setText(text.left(index));
            this->lastString = "";
        }
    } else {
        this->lastString = "";
        this->clear_expression();
    }
}

void MainWindow::calc_expression() {

    if (this->isResult)
        return;

    this->isResult = true;
    this->lastString = "";

    QString text = this->ui->expression->text();

    if (text.indexOf("x") != -1) {
        text.toStdString().c_str();
    } else {
        long double result;
        char test2[text.size()];
        memcpy( test2, text.toStdString().c_str() ,text.size());

        int error_code = calc((char *)test2, 0, &result);
        if (!error_code) {
            this->lastString = QString::number((double)result);
            this->ui->expression->setText(text + " = " + this->lastString);
        } else {
            this->lastString = text;
            this->ui->expression->setText(text + " = Ошибка");
        }
    }
}
