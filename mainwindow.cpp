#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// add files
void MainWindow::on_pushButton_5_clicked()
{
    QStringList list = QFileDialog::getOpenFileNames(0, "Choose files", "", "*.erl");
    foreach(QString str, list){
        ui->listWidget->addItem(str);
        ui->listWidget_2->addItem((*(str.split("/").end()-1)).split(".")[0]);
    }
}

// remove files
void MainWindow::on_pushButton_6_clicked()
{
    if(ui->listWidget->count()){
		delete ui->listWidget->currentItem();
		delete ui->listWidget_2->currentItem();
	}
}

// build diagrammss
void MainWindow::on_pushButton_7_clicked()
{
    string str;
    str = "shade_modules";
    for(size_t i = ui->listWidget_3->count(); i--;){
        str.push_back('|');
        str.append(ui->listWidget_3->item(i)->text().toStdString());
    }
    write_cmd(str);

    str = "shade_functions";
    for(size_t i = ui->listWidget_5->count(); i--;){
        str.push_back('|');
        str.append(ui->listWidget_5->item(i)->text().toStdString());
    }
    write_cmd(str);

    str = "analyse_modules";
    for(size_t i = ui->listWidget->count(); i--;){
        str.push_back('|');
        str.append(ui->listWidget->item(i)->text().toStdString());
    }
    write_cmd(str);

    str = "set_dir|text.txt";
    write_cmd(str);

    str = "build diagramm";
    write_cmd(str);
}

// move module to ignored
void MainWindow::on_pushButton_clicked()
{
	if(ui->listWidget_2->currentItem())
		ui->listWidget_3->addItem(ui->listWidget_2->currentItem());
}

// pop module from ignored
void MainWindow::on_pushButton_2_clicked()
{
    if(ui->listWidget_3->count())
		delete ui->listWidget_3->currentItem();
}

// add finction to ignored
void MainWindow::on_pushButton_3_clicked()
{
	if(ui->listWidget_4->currentItem())
		ui->listWidget_5->addItem(ui->listWidget_5->currentItem());
}

// pop function from ignoged
void MainWindow::on_pushButton_4_clicked()
{

    if(ui->listWidget_3->count())
		delete ui->listWidget_3->currentItem();
}

// click on file
void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
}

// click on module
void MainWindow::on_listWidget_2_currentRowChanged(int currentRow)
{
	ui->listWidget->setCurrentRow(currentRow);	
}
