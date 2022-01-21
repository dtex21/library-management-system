#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringList>
#include "addbook.h"
#include "book.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LibraryManager; }
QT_END_NAMESPACE

class LibraryManager : public QMainWindow
{
    Q_OBJECT

public:
    LibraryManager(QWidget *parent = nullptr);
    ~LibraryManager();
    void setup_table();
    void removeBook(Book book);

private slots:
    void on_actionAddEntry_triggered();
    void on_actionRemoveEntry_triggered();
    void on_actionRefreshTable_triggered();
    void on_actionQuit_triggered();
    void update_table();
    void update_table_with_row_focus();
    void filter_table();

private:
    Ui::LibraryManager *ui;
    QStandardItemModel *model = new QStandardItemModel;
    void load_library();
    void save_library();
};
#endif // LIBRARYMANAGER_H
