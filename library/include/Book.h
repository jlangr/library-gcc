#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    Book();
    Book(
        const std::string& title,
        const std::string& author,
        const unsigned int year,
        const std::string& classification,
        unsigned int type = Book::TYPE_BOOK);
    virtual ~Book();

    Book& operator=(const Book&);

    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
    bool operator<(const Book& other) const;

    enum BookType { TYPE_BOOK, TYPE_MOVIE, TYPE_NEW_RELEASE };
    static const unsigned int BOOK_DAILY_FINE = 10u;
    static const unsigned int MOVIE_DAILY_FINE = 100u;
    static const unsigned int NEW_RELEASE_DAILY_FINE = 20u;

    std::string title() const;
    std::string author() const;
    unsigned int year() const;
    std::string classification() const;
    unsigned int type() const;

    static const int BOOK_CHECKOUT_PERIOD{21u};
    static const int MOVIE_CHECKOUT_PERIOD{7u};
    static const int NEW_RELEASE_CHECKOUT_PERIOD{3u};

private:
    std::string mTitle;
    std::string mAuthor;
    std::string mClassification;
    unsigned int mYear;
    unsigned int mType;
};

#endif
