#include <iostream>
#include "Library.h"

const int MAX_BOOKS = 3;

void showMenu()
{
    std::cout << "=== LIBRARY MANAGEMENT ===" << std::endl;
    std::cout << "1. View all books\n";
    std::cout << "2. View all users\n";
    std::cout << "3. Add new book\n";
    std::cout << "4. Register user\n";
    std::cout << "5. Borrow book\n";
    std::cout << "6. Return book\n";
    std::cout << "7. Search book by ISBN\n";
    std::cout << "8. View user profile\n";
    std::cout << "9. Save data\n";
    std::cout << "10. Exit\n";
    std::cout << "Choice: ";
}

void clearIn() 
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    Library lib("data/library_data.txt");
    int choice;

    while (true)
     {
        showMenu();
        if (!(std::cin >> choice)) 
        {
            std::cout << "Invalid input" << std::endl;
            clearIn();
            continue;
        }
        clearIn();

        try {
            switch (choice) {
            case 1: 
            {
                lib.displayAllBooks();
                break;
            }

            case 2: 
            {
                lib.displayAllUsers();
                break;
            }

            case 3: 
            {
                std::string title, author, isbn;
                int year;
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter year: ";
                std::cin >> year;
                clearIn();
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);

                lib.addBook(Book(title, author, year, isbn));
                std::cout << "Book added successfully." << std::endl;
                break;
            }

            case 4: 
            {
                std::string name, id;
                std::cout << "Enter user name: ";
                std::getline(std::cin, name);
                std::cout << "Enter user ID: ";
                std::getline(std::cin, id);

                lib.addUser(User(name, id, MAX_BOOKS));
                std::cout << "User registered successfully." << std::endl;
                break;
            }

            case 5: 
            {
                std::string name, isbn;
                std::cout << "Enter user name: ";
                std::getline(std::cin, name);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                lib.borrowBook(name, isbn);
                break;
            }

            case 6: 
            {
                std::string isbn;
                std::cout << "Enter ISBN to return: ";
                std::getline(std::cin, isbn);
                lib.returnBook(isbn);
                break;
            }

            case 7: 
            {
                std::string isbn;
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                Book* b = lib.findBookByISBN(isbn);
                if (b)
                    b->displayInfo();
                else
                    std::cout << "Book not found." << std::endl;
                break;
            }

            case 8: 
            {
                std::string n;
                std::cout << "Enter user name: ";
                std::getline(std::cin, n);
                User* u = lib.findUserByName(n);
                if (u)
                    u->displayProfile();
                else
                    std::cout << "User not found." << std::endl;
                break;
            }

            case 9: 
            {
                lib.saveToFile();
                break;
            }

            case 10: 
            {
                break;
            }

            default: 
            {
                std::cout << "Invalid option." << std::endl;
                break;
            }
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}