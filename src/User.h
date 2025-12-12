#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class User {
private:
    std::string name;
    std::string userId;
    std::vector<std::string> borrowedBooks;
    int maxBooksAllowed;

public:
    User(std::string name, std::string id, int maxBooks);

    std::string getName();
    std::string getUserId();
    std::vector<std::string> getBorrowedBooks();
    int getMaxBooks();
    bool canBorrowMore();
    void addBook(const std::string& isbn);
    void removeBook(const std::string& isbn);
    void displayProfile();
};

#endif