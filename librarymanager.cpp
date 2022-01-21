#include "librarymanager.h"
#include "ui_librarymanager.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTableView>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include <iostream>
#include <QShortcut>

LibraryManager::LibraryManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManager)
{
    ui->setupUi(this);
    setup_table();
    load_library();
    connect(LibraryManager::ui->search, SIGNAL(returnPressed()), this, SLOT(filter_table()));
}

LibraryManager::~LibraryManager()
{
    delete ui;
}

void LibraryManager::on_actionAddEntry_triggered()
{
    auto addBookDialog = new AddBook(this);
    addBookDialog->open();
    connect(addBookDialog->buttonBox, SIGNAL(accepted()), this, SLOT(update_table_with_row_focus()));
}

void LibraryManager::on_actionQuit_triggered()
{
    QApplication::quit();
}

void LibraryManager::setup_table() {
    auto table = this->ui->table;
    QStringList horizontalHeaders;

    table->setModel(model);
    horizontalHeaders.append("ISBN");
    horizontalHeaders.append("Author");
    horizontalHeaders.append("Title");
    model->setHorizontalHeaderLabels(horizontalHeaders);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void LibraryManager::load_library() {
    QFile file("library.csv");
    int i;

    if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this,
                                     tr("Unable to open file"),
                                     file.errorString());
            return;
        }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList temp_list = line.split(";");

        for(i = 0; i < temp_list.length() / 3; i++) {
            QStandardItem *isbn_col = new QStandardItem(temp_list[3 * i]);
            QStandardItem *author_col = new QStandardItem(temp_list[3 * i + 1]);
            QStandardItem *title_col = new QStandardItem(temp_list[3 * i + 2]);

            isbn_col->setTextAlignment(Qt::AlignHCenter);
            author_col->setTextAlignment(Qt::AlignHCenter);
            title_col->setTextAlignment(Qt::AlignHCenter);

            model->appendRow(QList<QStandardItem*>() << isbn_col << author_col << title_col);
        }
    }
    file.close();
    this->ui->table->resizeRowsToContents();
    this->ui->table->resizeColumnsToContents();
}

void LibraryManager::save_library() {
    QFile file("library.csv");
    int i, j;

    if(!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this,
                                     tr("Unable to open file"),
                                     file.errorString());
            return;
       }
    QString text;
    for(i = 0; i < model->rowCount(); i++){
        for(j = 0; j < model->columnCount(); j++){
            text = model->item(i,j)->text() + ";";
            file.write(text.toUtf8());
        }
        file.write("\n");
    }
}

void LibraryManager::update_table() {
    model->setRowCount(0);
    load_library();
}

void LibraryManager::update_table_with_row_focus(){
    update_table();
    this->ui->table->selectRow(model->rowCount() - 1);
}

void LibraryManager::on_actionRefreshTable_triggered()
{
    update_table();
}

void LibraryManager::on_actionRemoveEntry_triggered()
{
    QList<QModelIndex> sel = ui->table->selectionModel()->selectedRows();
    std::sort(sel.begin(), sel.end());
    std::reverse(sel.begin(), sel.end());
    foreach (auto s, sel)
        model->removeRow(s.row());
    save_library();
    update_table();
    QMessageBox::information(this, tr("Success"), tr("Entry was removed successfully!"));
}

void LibraryManager::filter_table() {
    QString filter_string = this->ui->search->text().trimmed();
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);

    proxy->setSourceModel(model);
    proxy->setFilterRegExp(QRegExp(filter_string, Qt::CaseInsensitive, QRegExp::FixedString));
    proxy->setFilterKeyColumn(-1);
    //proxy->setDynamicSortFilter(true);
    this->ui->table->setModel(proxy);
}

