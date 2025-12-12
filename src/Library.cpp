#include "Library.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

Library::Library(const std::string& file) : dataFile(file)
{
    loadFromFile();
}

void Library::addBook(const Book& book) 
{
    for (Book& b : books)
    {
        if (b.getISBN() == book.getISBN()) throw std::invalid_argument("Error:Book with same ISBN already exists");
    }
    books.push_back(book);
}

void Library::addUser(const User& user) 
{
    for (User& u : users)
    {
        if (u.getUserId() == user.getUserId()) throw std::invalid_argument("Error:User with same ID already exists");
    }
    users.push_back(user);
}

Book* Library::findBookByISBN(const std::string& isbn)
{
    for(Book& book: books)
    {
        if(book.getISBN() == isbn) return &book;
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name)
{
    for(User& user: users)
    {
        if(user.getName() == name) return &user;
    }
    return nullptr;
}

void Library::borrowBook(const std::string& userName, const std::string& isbn)
{
    User* user = findUserByName(userName);
    Book* book = findBookByISBN(isbn);

    if(!user) throw std::runtime_error("Error:User with that name not found");
    if(!book) throw std::runtime_error("Error:Book with that ISBN not found");

    if (!book->getAvailable()) throw std::runtime_error("Error:Book is not available");
    if (!user->canBorrowMore()) throw std::runtime_error("Error:User cannot borrow more books");

    book->borrowBook(userName);
    user->addBook(isbn);
    std::cout << "Book " << book << " borrowed by " << userName << std::endl;
}

void Library::returnBook(const std::string& isbn)
{
    Book* book = findBookByISBN(isbn);
    if(!book) throw std::runtime_error("Error:Book with that ISBN not found");
    
    if (book->getAvailable()) throw std::runtime_error("Error:Book is not borrowed");

    std::string userName = book->getBorrowedBy();
    User* user = findUserByName(userName);

    if(!user) throw std::runtime_error("Error:User with that name not found");

    book->returnBook();
    if (user) {
        user->removeBook(isbn);
    }
    std::cout << "Book returned" << std::endl;
}


void Library::displayAllBooks() const
{
    if (books.empty())
    {
        std::cout << "Library is empty" << std::endl;
        return;
    }
    for (const Book& book : books) {
        book.displayInfo();
    }
}

void Library::displayAllUsers() const
{
    if (users.empty())
    {
      std::cout << "User list is empty" << std::endl;
      return;  
    } 
    for (const User& user : users) {
        user.displayProfile();
    }
}

void Library::saveToFile()
{

}

void Library::loadFromFile()
{

}