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
        {ui->mod->objectName(), "mod"}, {ui->point->objectName(), "."},
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
    connect(ui->negate, SIGNAL(clicked()), this, SLOT(negate()));

    connect(ui->pi, SIGNAL(clicked()), this, SLOT(pressing_button()));


    connect(ui->calc_credit, SIGNAL(clicked()), this, SLOT(calc_credit()));


    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::red)); // line color blue for first graph
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssCircle,5));

    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->customPlot->graph(0)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->customPlot->setBackground(ui->graph_grid->palette().color(ui->graph_grid->backgroundRole()));

    ui->customPlot-> xAxis-> setBasePen (QPen (Qt :: white, 1)); // Перо оси
    ui->customPlot-> xAxis-> setTickPen (QPen (Qt :: white, 1)); // Перо отметки оси
    ui->customPlot-> xAxis-> setSubTickPen (QPen (Qt :: white, 1)); // Перо отметки оси
    ui->customPlot-> xAxis-> setTickLabelColor (Qt :: white); // цвет текста шкалы оси
    ui->customPlot-> xAxis-> setLabelColor (Qt :: white); // Цвет метки оси
    ui->customPlot-> xAxis-> setTickLengthIn (3); // Длина шкалы по оси
    ui->customPlot-> xAxis-> setTickLengthOut (5); // Длина шкалы вне оси

    ui->customPlot-> yAxis-> setBasePen (QPen (Qt :: white, 1)); // Перо оси
    ui->customPlot-> yAxis-> setTickPen (QPen (Qt :: white, 1)); // Перо отметки оси
    ui->customPlot-> yAxis-> setSubTickPen (QPen (Qt :: white, 1)); // Перо отметки оси
    ui->customPlot-> yAxis-> setTickLabelColor (Qt :: white); // цвет текста шкалы оси
    ui->customPlot-> yAxis-> setLabelColor (Qt :: white); // Цвет метки оси
    ui->customPlot-> yAxis-> setTickLengthIn (3); // Длина шкалы по оси
    ui->customPlot-> yAxis-> setTickLengthOut (5); // Длина шкалы вне оси
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pressing_button() {
    QPushButton* button = (QPushButton*)sender();

    if (this->isResult)
        this->cancel_action();

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
    this->isResult = false;
    this->lastString = "";
    this->ui->expression->setText(this->lastString);
}

void MainWindow::cancel_action() {
    QString text = this->ui->expression->text();

    if (this->isResult) {
        this->isResult = false;

        text = this->lastString;

        this->ui->expression->setText(text);
    } else {

        int index = text.lastIndexOf(" ");
        if (index == -1) {
            clear_expression();
        } else {
            this->lastString = text.left(index);
            this->ui->expression->setText(this->lastString);
        }
    }
}

void MainWindow::calc_expression() {
    QString text = this->ui->expression->text();

    if (!text.length())
        return;

    if (this->isResult)
        text = this->lastString;
    this->isResult = true;

    if (text.indexOf("x") != -1) {
        int N = abs(ui->max_x->value() - ui->min_x->value()) / ui->step_x->value();
        QVector<double> x(N), y(N);
        for (int i = 0; i < N; ++i) {
          x[i] = ui->min_x->value() + ui->step_x->value() * i;

          long double result;
          char test2[text.size() + 1];
          memcpy( test2, text.toStdString().c_str(), text.size());
          test2[text.size()] = 0;

          int error_code = calc((char *)test2, x[i], &result);
          if (error_code) {
              this->lastString = text;
              this->ui->expression->setText(text + " = Ошибка");

              ui->customPlot->clearGraphs();
              ui->customPlot->replot();
              return;
          }
          y[i] = (double)result;
        }

        this->lastString = text;
        this->ui->expression->setText(text + " = График построен");

        ui->customPlot->graph(0)->setData(x, y);
        ui->customPlot->replot();

        ui->tabWidget->setCurrentWidget(ui->graph_grid);
    } else {
        long double result;
        char test2[text.size() + 1];
        memcpy( test2, text.toStdString().c_str() ,text.size());
        test2[text.size()] = 0;

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

void MainWindow::negate() {
    QString text = this->ui->expression->text();

    if (!text.length())
        return;

    if (this->isResult) {
        this->cancel_action();

        text = this->ui->expression->text();
    }

    int index = text.lastIndexOf(" ");
    if (text[index + 1] == '-')
        text[index + 1] = '+';
    else if (text[index + 1] == '+')
        text[index + 1] = '-';
    else
        text.insert(index + 1, '-');

    this->ui->expression->setText(text);
}

void MainWindow::calc_credit() {
    if (this->ui->annuity->isChecked()) {
        double loan = this->ui->loan_amount->value();
        int period = this->ui->period->value();

        double res = credit_calc_annuity(loan, period, this->ui->percent->value());
        double all = res * period;

        this->ui->label_mon_pay->setText("Ежемесячный платеж: " + QString::number(res));
        this->ui->label_overpay->setText("Переплата по кредиту: " + QString::number(all - loan ));
        this->ui->label_all_pay->setText("Общая выплата: " + QString::number(all));
    } else {
        double loan = this->ui->loan_amount->value();
        int period = this->ui->period->value();


        double start_res = credit_calc_differentiate(loan, period, 1, this->ui->percent->value());
        double end_res = 0;
        if (period > 1)
            end_res = credit_calc_differentiate(loan, period, period, this->ui->percent->value());


        double all = start_res + end_res;
        for (int i = 2; i < period; i++)
            all += credit_calc_differentiate(loan, period, i, this->ui->percent->value());


        QString text = "Ежемесячный платеж: " + QString::number(start_res);
        if (period > 1)
            text +=  + " - " + QString::number(end_res);

        this->ui->label_mon_pay->setText(text);
        this->ui->label_overpay->setText("Переплата по кредиту: " + QString::number(all - loan));
        this->ui->label_all_pay->setText("Общая выплата: " + QString::number(all));
    }
}
