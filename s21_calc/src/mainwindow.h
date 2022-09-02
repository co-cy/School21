#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isResult = false;
    QString lastString = "";

private slots:
    void pressing_button();
    void clear_expression();
    void cancel_action();
    void calc_expression();

private:
    Ui::MainWindow *ui;

    std::map<QString, QString> converter;
};

#endif // MAINWINDOW_H
