#include "mainwindow.h"
#include "ui_mainwindow.h"

string collect_items_from_listView(QListWidget* lv){
    termos term;
    term.put_list(lv->children().size());
    for(int i =0; i < lv->children().size(); i++)
        term.put_atom(lv->item(i)->text().toStdString().c_str());
    term.end_of_list();
    return term.str;
}

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

}

// build diagrammss
void MainWindow::on_pushButton_7_clicked()
{

    //"{config, []"
    //"{config, [{analyse, _}, {output, Name}, {shade_modules, Modules}, {shade_funs, Funs}]"
}

// move module to ignored
void MainWindow::on_pushButton_clicked()
{

}

// pop module from ignored
void MainWindow::on_pushButton_2_clicked()
{

}

// add finction to ignored
void MainWindow::on_pushButton_3_clicked()
{

}

// pop function from ignoged
void MainWindow::on_pushButton_4_clicked()
{

}

// click on file
void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    termos term("{'query', {'parse_for_functions', %a}}", ui->listWidget->item(currentRow)->text().toStdString().c_str());
    write_cmd(term.str);
}

// click on module
void MainWindow::on_listWidget_2_currentRowChanged(int currentRow)
{

}
