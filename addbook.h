#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include "book.h"
#include "ui_addBook.h"

class AddBook : public QDialog, public Ui::addBookDialog {
Q_OBJECT

public:
    AddBook(QWidget *parent = nullptr);
    void write_data_to_file(Book book);

private slots:
    void accept();
    Book update();
};

#endif // ADDBOOK_H
