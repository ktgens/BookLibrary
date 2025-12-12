#include "User.h"
#include <stdexcept>

User::User(std::string name, std::string id, int maxBooks) 
    : name(name), userId(id), maxBooksAllowed(maxBooks) {}

std::string User::getName() { return name; }
std::string User::getUserId() { return userId; }
std::vector<std::string> User::getBorrowedBooks() { return borrowedBooks; }
int User::getMaxBooks() { return maxBooksAllowed; }

bool User::canBorrowMore() { return borrowedBooks.size() < maxBooksAllowed;}

void User::addBook(const std::string& isbn) 
{
    if (!canBorrowMore()) throw std::runtime_error("Error:User's book limit exceeded");
    borrowedBooks.push_back(isbn);
}

void User::removeBook(const std::string& isbn)
{
    for(int i = 0; i<borrowedBooks.size();i++)
    {
        if(borrowedBooks[i]==isbn)
        {
            std::string currentIsbn = borrowedBooks[i];
            borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), currentIsbn), borrowedBooks.end());
        }
    }
}

void User::displayProfile() 
{
    std::cout << "User:" << name << " (ID: " << userId << ")\n";
    std::cout << "Borrowed Books:" << borrowedBooks.size() << maxBooksAllowed << std::endl;
    for (std::string isbn : borrowedBooks)
    {
        std::cout << "ISBN: " << isbn << std::endl;
    }
}
