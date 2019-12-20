#include "help.h"
#include "ui_help.h"
#include<menu.h>
help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
}

help::~help()
{
    delete ui;
}

void help::on_pushButton_clicked()
{
    this->close();
    menu *m=new menu();
    m->show();
}
