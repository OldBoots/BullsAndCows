#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <QString>
#include <QStringListModel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void input_num(char num);
    void init_mass(QVector<int> &vec);
private slots:
    void slot_butt0();
    void slot_butt1();
    void slot_butt2();
    void slot_butt3();
    void slot_butt4();
    void slot_butt5();
    void slot_butt6();
    void slot_butt7();
    void slot_butt8();
    void slot_butt9();
    void slot_butt_enter();
    void slot_butt_back();
    void slot_end_time();
    void slot_start_time();
    void slot_stop_time();
private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QTimer *timer;
    QStringList list_attempts;
    QString str_rand_num;
    QString str_number;
    int num_count;
};

int Rand(int min, int max);
#endif // MAINWINDOW_H
