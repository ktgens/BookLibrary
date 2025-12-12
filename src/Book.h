#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>

class Book 
{
private:
    std::string title;
    std::string author;
    int year;
    std::string isbn;
    bool isAvailable;
    std::string borrowedBy;

public:
    Book(std::string title, std::string author, int y, std::string isbn);

    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getISBN() const;
    bool getAvailable() const;
    std::string getBorrowedBy() const;
    void borrowBook(const std::string& userName);
    void returnBook();
    void displayInfo();
    void setAvailability(bool avail);
    void setBorrowedBy(const std::string& user);
};


#endif