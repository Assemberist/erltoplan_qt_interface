#include "mainwindow.h"
#include "ui_mainwindow.h"

term collect_items_from_listView(QListWidget* lv){
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
	if(ui->listWidget->children().size()){
		//ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
		//ui->listWidget_2->removeItemWidget(ui->listWidget_2->currentItem());
		delete ui->listWidget->currentItem();
		delete ui->listWidget_2->currentItem();
	}
}

// build diagrammss
void MainWindow::on_pushButton_7_clicked()
{
    termos term("{'config', [{'analyse', %t}, {'output', %s}, {'shade_modules', %t}, {'shade_funs', %t}]}",
                collect_items_from_listView(ui->listWidget),
                // to do 
                // it should be path where put diagrams
                "",
                collect_items_from_listView(ui->listWidget_3),
                collect_items_from_listView(ui->listWidget_5));
                
    write_cmd(term.str);
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
	if(ui->listWidget_3->children().size())
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
	if(ui->listWidget_3->children().size())
		delete ui->listWidget_3->currentItem();
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
	ui->listWidget->setCurrentRow(currentRow);	
}
