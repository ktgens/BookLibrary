#include <iostream>
#include "Library.h"

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
    while(true)
    {
        showMenu();
    }

    return 0;
}