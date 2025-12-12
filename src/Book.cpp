#include "Book.h"
#include <stdexcept>

const int CURRENT_YEAR = 2025;

Book::Book(std::string title, std::string author, int year, std::string isbn) : title(title), author(author), year(year), isbn(isbn), isAvailable(true),borrowedBy("")
{
    if(year < 0 || year > CURRENT_YEAR)
    {
        throw std::invalid_argument("Error:year input is invalid");
    }

    if(title.empty()) throw std::invalid_argument("Error:name cannot be empty");
    if(title.empty()) throw std::invalid_argument("Error:author field cannot be empty");
    if(title.empty()) throw std::invalid_argument("Error:ISBN cannt be empty");

}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const{ return author; }
int Book::getYear() const{ return year; }
std::string Book::getISBN() const { return isbn; }
bool Book::getAvailable() const{ return isAvailable; }
std::string Book::getBorrowedBy() const { return borrowedBy; }

void Book::borrowBook(const std::string& userName) 
{
    if (!isAvailable) {
        throw std::runtime_error("Book is already borrowed.");
    }
    isAvailable = false;
    borrowedBy = userName;
}

void Book::returnBook()
{
    isAvailable = true;
    borrowedBy = "";
}

void Book::displayInfo() const
{
    std::cout << "Title: " << title << " | Author: " << author << " | Year: " << year << " | ISBN: " << isbn  << " | Available: " << (isAvailable ? "Yes" : "No");

    if (!isAvailable) {
        std::cout << " Borrowed by: " << borrowedBy;
    }
    std::cout << std::endl;
}

void Book::setAvailability(bool avail) { isAvailable = avail; }
void Book::setBorrowedBy(const std::string& user) { borrowedBy = user; }