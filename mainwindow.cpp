#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Decoder");
    num_count = 5;
    str_rand_num = QString::number(Rand(10000, 99999));
    qDebug () << str_rand_num;
    model = new QStringListModel;
    ui->lcd->setDigitCount(num_count);
    model->setStringList(list_attempts);
    ui->listView->setModel(model);
    QFont font;
    font.setPixelSize(20);
    ui->listView->setFont(font);
    connect(ui->butt0, SIGNAL(clicked()), this, SLOT(slot_butt0()));
    connect(ui->butt1, SIGNAL(clicked()), this, SLOT(slot_butt1()));
    connect(ui->butt2, SIGNAL(clicked()), this, SLOT(slot_butt2()));
    connect(ui->butt3, SIGNAL(clicked()), this, SLOT(slot_butt3()));
    connect(ui->butt4, SIGNAL(clicked()), this, SLOT(slot_butt4()));
    connect(ui->butt5, SIGNAL(clicked()), this, SLOT(slot_butt5()));
    connect(ui->butt6, SIGNAL(clicked()), this, SLOT(slot_butt6()));
    connect(ui->butt7, SIGNAL(clicked()), this, SLOT(slot_butt7()));
    connect(ui->butt8, SIGNAL(clicked()), this, SLOT(slot_butt8()));
    connect(ui->butt9, SIGNAL(clicked()), this, SLOT(slot_butt9()));
    connect(ui->butt_enter, SIGNAL(clicked()), this, SLOT(slot_butt_enter()));
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_end_time()));
    connect(ui->butt_back, SIGNAL(clicked()), this, SLOT(slot_butt_back()));
    connect(ui->butt_back, SIGNAL(pressed()), this, SLOT(slot_start_time()));
    connect(ui->butt_back, SIGNAL(released()), this, SLOT(slot_stop_time()));
    connect(ui->action_3, SIGNAL(triggered()), this, SLOT(slot_set_cn()));
}

void MainWindow::slot_set_cn(){
    bool bOk;
    QIntValidator ttt(2, 8);
    int num = QInputDialog::getInt(this, "", "Number:", 2, 2, 8, 1, &bOk);
    if(bOk){
        num_count = num;
        ui->lcd->setDigitCount(num_count);
        str_number = "";
        ui->lcd->display(str_number);
        int rt = 1, rtt = 9;
        for(int i = 1; i < num_count; i++){
            rt *= 10;
            rtt = rtt * 10 + 9;
        }
        str_rand_num = QString::number(Rand(rt, rtt));
    }
    qDebug() << str_rand_num;
}

void MainWindow::slot_end_time(){
    str_number = "";
    ui->lcd->display(str_number);
}

void MainWindow::slot_start_time(){
    timer->start(500);
}

void MainWindow::slot_stop_time(){
    timer->stop();
}

void MainWindow::init_mass(QVector<int> &vec){
    vec.clear();
    for(int i = 0; i < 10; i++){
        vec << str_rand_num.count(QString::number(i));
    }
}

void MainWindow::input_num(char num){
    if(str_number.size() < num_count){
        str_number += num;
        ui->lcd->display(str_number);
    }
}

void MainWindow::slot_butt0(){
    input_num('0');
}

void MainWindow::slot_butt1(){
    input_num('1');
}

void MainWindow::slot_butt2(){
    input_num('2');
}

void MainWindow::slot_butt3(){
    input_num('3');
}

void MainWindow::slot_butt4(){
    input_num('4');
}

void MainWindow::slot_butt5(){
    input_num('5');
}

void MainWindow::slot_butt6(){
    input_num('6');
}

void MainWindow::slot_butt7(){
    input_num('7');
}

void MainWindow::slot_butt8(){
    input_num('8');
}

void MainWindow::slot_butt9(){
    input_num('9');
}

void MainWindow::slot_butt_enter(){
    if(str_number.size() != num_count){ return; }
    QString str_answer = str_number + "\t\t";
    QVector <int> vec_num;
    init_mass(vec_num);
    for(int i = 0, count = 0; i < num_count; i++){
        if(str_number[i] == str_rand_num[i]){
            if(vec_num[str_number[i].digitValue()] != 0){ vec_num[str_number[i].digitValue()]--; str_answer += "1"; count++; }
        }
        if(count == num_count){
            QMessageBox::warning(this, "Attention","Unlocked");
        }
    }
    for(int i = 0; i < num_count; i++){
        if(str_rand_num.count(str_number[i])){
            if(vec_num[str_number[i].digitValue()] != 0){ vec_num[str_number[i].digitValue()]--; str_answer += "0";}
        }
    }
    list_attempts.push_front(str_answer);
    model->setStringList(list_attempts);
}

void MainWindow::slot_butt_back(){
    if(!str_number.isEmpty()){
        str_number.chop(1);
        ui->lcd->display(str_number);
    }
}

int Rand(int min, int max){
    if (min == max){
        return min;
    }
    std::uniform_int_distribution dist(min, max);
    return dist(*QRandomGenerator::global());
}

MainWindow::~MainWindow()
{
    delete ui;
}

