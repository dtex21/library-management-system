#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book {
private:
    QString _isbn;
    QString _author;
    QString _title;

public:
    Book(QString isbn, QString author, QString title):
        _isbn(std::move(isbn)),
        _author(std::move(author)),
        _title(std::move(title))
        {};
    
    const QString get_isbn() {
        return _isbn;
    }
    
    const QString get_author() {
        return _author;
    }
    const QString get_title() {
        return _title;
    }
};
#endif //BOOK_H
