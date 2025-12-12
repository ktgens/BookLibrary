#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string isbn;
    bool isAvailable;
    std::string borrowedBy;

public:
    Book(std::string title, std::string author, int y, std::string isbn);

    std::string getTitle();
    std::string getAuthor();
    int getYear();
    std::string getISBN();
    bool getAvailable();
    std::string getBorrowedBy();
    void borrowBook(const std::string& userName);
    void returnBook();
    void displayInfo();
    void setAvailability(bool avail);
    void setBorrowedBy(const std::string& user);
};


#endif