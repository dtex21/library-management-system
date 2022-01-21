#include "addbook.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

AddBook::AddBook(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    connect(AddBook::buttonBox, SIGNAL(accepted()), this, SLOT(AddBook::accept()));
    connect(AddBook::ISBN, SIGNAL(editingFinished()), this, SLOT(AddBook::update()));
    connect(AddBook::author, SIGNAL(editingFinished()), this, SLOT(AddBook::update()));
    connect(AddBook::title, SIGNAL(editingFinished()), this, SLOT(AddBook::update()));
    this->ISBN->setFocus();
}

Book AddBook::update(){
    Book book(this->ISBN->text(), this->author->text(), this->title->text());
    return book;
}

void AddBook::write_data_to_file(Book book){
    QString fileName = "library.csv";
  /*QString dir = QDir::homePath();
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Add Book Entry to File"),
                                                    dir,
                                                    tr("Data File (*.csv);;All Files (*)"));*/

    if(fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QMessageBox::information(this,
                                     tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QString data = book.get_isbn() + ";" + book.get_author() + ";" + book.get_title() + "\n";
        file.write(data.toUtf8());
        file.close();
        QMessageBox::information(this, tr("Success"), tr("Entry added successfully!"));
    }
}

void AddBook::accept()
{
    Book book = update();

    this->write_data_to_file(book);
    this->ISBN->clear();
    this->author->clear();
    this->title->clear();
    this->ISBN->setFocus();
}
