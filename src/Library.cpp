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
    for (const Book& book : books) 
    {
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
    for (const User& user : users) 
    {
        user.displayProfile();
    }
}

void Library::saveToFile()
{
    std::ofstream file(dataFile);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Error:opening file for saving");
        return;
    }

    for (const Book& b : books) 
    {
        file << "BOOK" << std::endl;
        file << "Title: " << b.getTitle() << std::endl;
        file << "Author: " << b.getAuthor() << std::endl;
        file << "Year: " << b.getYear() << std::endl;
        file << "ISBN: " << b.getISBN() << std::endl;
        file << "Available: " << (b.getAvailable() ? "yes" : "no") << std::endl;
        file << "BorrowedBy: " << b.getBorrowedBy() << std::endl;
    }

    file << "---USERS---\n\n";

    for (const User& u : users) 
    {
        file << "USER" << std::endl;
        file << "Name: " << u.getName() << std::endl;
        file << "UserID: " << u.getUserId() << std::endl;
        file << "BorrowedBooks: ";
        std::vector<std::string> books = u.getBorrowedBooks();
        for (size_t i = 0; i < books.size(); ++i) 
        {
            file << books[i];
        }
        file << std::endl;
        file << "MaxBooks: " << u.getMaxBooks() << std::endl;
    }
    file.close();
    std::cout << "Data saved to " << dataFile << std::endl;


}

void Library::loadFromFile()
{
    std::ifstream file(dataFile);
    if (!file.is_open()) return;

    std::string line;
    bool parsingUsers = false;

    std::string title, author, isbn, borrowedBy, name, userId, borrowedStr;
    int year = 0;
    int maxBooks = 3;
    bool isAvailable = true;

    while (std::getline(file, line)) 
    {
        if (line == "---USERS---")
        {
            parsingUsers = true;
            continue;
        }
        if (line.empty()) continue;

        if (!parsingUsers)
        {
            if (line == "BOOK") continue;

            if (line.find("Title: ") == 0) title = line.substr(7);
            else if (line.find("Author: ") == 0) author = line.substr(8);
            else if (line.find("Year: ") == 0) year = std::stoi(line.substr(6));
            else if (line.find("ISBN: ") == 0) isbn = line.substr(6);
            else if (line.find("Available: ") == 0) isAvailable = (line.substr(11) == "yes");
            else if (line.find("BorrowedBy: ") == 0)
            {
                borrowedBy = line.substr(12);
                try
                {
                    Book b(title, author, year, isbn);
                    b.setAvailability(isAvailable);
                    b.setBorrowedBy(borrowedBy);
                    books.push_back(b);
                } catch (...) { }
            }
        } else 
        {
            if (line == "USER") continue;
            if (line.find("Name: ") == 0) name = line.substr(6);
            else if (line.find("UserID: ") == 0) userId = line.substr(8);
            else if (line.find("BorrowedBooks: ") == 0) borrowedStr = line.substr(15);
            else if (line.find("MaxBooks: ") == 0)
            {
                maxBooks = std::stoi(line.substr(10));

                User u(name, userId, maxBooks);

                std::string current;
                for (size_t i = 0; i <= borrowedStr.size(); ++i)
                {
                    if (i == borrowedStr.size() || borrowedStr[i] == '|')
                    {
                        if (!current.empty())
                        {
                            try { u.addBook(current); } catch (...) {}
                            current.clear();
                        }
                    }
                    else
                    {
                        current += borrowedStr[i];
                    }
                }

                users.push_back(u);
            }
        }
    }
    file.close();
}