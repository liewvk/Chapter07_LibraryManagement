#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

struct Book
{
    int id;
    std::string title;
    std::string author;
    std::string category;
    bool borrowed;
    std::string borrowerName;
};

void displayMenu()
{
    std::cout << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "       Library Management System" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "1. Add Book" << std::endl;
    std::cout << "2. Display All Books" << std::endl;
    std::cout << "3. Search Book by Title" << std::endl;
    std::cout << "4. Update Book" << std::endl;
    std::cout << "5. Delete Book" << std::endl;
    std::cout << "6. Borrow Book" << std::endl;
    std::cout << "7. Return Book" << std::endl;
    std::cout << "8. Save Books to File" << std::endl;
    std::cout << "9. Load Books from File" << std::endl;
    std::cout << "10. Exit" << std::endl;
    std::cout << "Please choose an option: ";
}

int generateBookId(const std::vector<Book>& books)
{
    int maxId = 0;

    for (const Book& book : books)
    {
        if (book.id > maxId)
        {
            maxId = book.id;
        }
    }

    return maxId + 1;
}

void addBook(std::vector<Book>& books)
{
    Book newBook;

    newBook.id = generateBookId(books);

    std::cout << "Enter book title: ";
    std::getline(std::cin, newBook.title);

    std::cout << "Enter author name: ";
    std::getline(std::cin, newBook.author);

    std::cout << "Enter book category: ";
    std::getline(std::cin, newBook.category);

    newBook.borrowed = false;
    newBook.borrowerName = "";

    books.push_back(newBook);

    std::cout << "Book added successfully." << std::endl;
}

void displayBook(const Book& book)
{
    std::cout << "Book ID      : " << book.id << std::endl;
    std::cout << "Title        : " << book.title << std::endl;
    std::cout << "Author       : " << book.author << std::endl;
    std::cout << "Category     : " << book.category << std::endl;
    std::cout << "Status       : " << (book.borrowed ? "Borrowed" : "Available") << std::endl;
    std::cout << "Borrower Name: " << (book.borrowed ? book.borrowerName : "-") << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

void displayAllBooks(const std::vector<Book>& books)
{
    if (books.empty())
    {
        std::cout << "No books found." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "========== Book List ==========" << std::endl;

    for (const Book& book : books)
    {
        displayBook(book);
    }
}

void searchBookByTitle(const std::vector<Book>& books)
{
    std::string keyword;
    bool found = false;

    std::cout << "Enter book title or keyword to search: ";
    std::getline(std::cin, keyword);

    std::cout << std::endl;
    std::cout << "========== Search Results ==========" << std::endl;

    for (const Book& book : books)
    {
        if (book.title.find(keyword) != std::string::npos)
        {
            displayBook(book);
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No book found with the keyword: " << keyword << std::endl;
    }
}

int findBookIndexById(const std::vector<Book>& books, int id)
{
    for (int i = 0; i < static_cast<int>(books.size()); ++i)
    {
        if (books[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

void updateBook(std::vector<Book>& books)
{
    int id;

    std::cout << "Enter book ID to update: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int index = findBookIndexById(books, id);

    if (index == -1)
    {
        std::cout << "Book not found." << std::endl;
        return;
    }

    std::cout << "Enter new title: ";
    std::getline(std::cin, books[index].title);

    std::cout << "Enter new author: ";
    std::getline(std::cin, books[index].author);

    std::cout << "Enter new category: ";
    std::getline(std::cin, books[index].category);

    std::cout << "Book updated successfully." << std::endl;
}

void deleteBook(std::vector<Book>& books)
{
    int id;

    std::cout << "Enter book ID to delete: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int index = findBookIndexById(books, id);

    if (index == -1)
    {
        std::cout << "Book not found." << std::endl;
        return;
    }

    if (books[index].borrowed)
    {
        std::cout << "This book is currently borrowed. It cannot be deleted." << std::endl;
        return;
    }

    books.erase(books.begin() + index);

    std::cout << "Book deleted successfully." << std::endl;
}

void borrowBook(std::vector<Book>& books)
{
    int id;

    std::cout << "Enter book ID to borrow: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int index = findBookIndexById(books, id);

    if (index == -1)
    {
        std::cout << "Book not found." << std::endl;
        return;
    }

    if (books[index].borrowed)
    {
        std::cout << "This book is already borrowed by "
            << books[index].borrowerName << "." << std::endl;
        return;
    }

    std::cout << "Enter borrower name: ";
    std::getline(std::cin, books[index].borrowerName);

    books[index].borrowed = true;

    std::cout << "Book borrowed successfully." << std::endl;
}

void returnBook(std::vector<Book>& books)
{
    int id;

    std::cout << "Enter book ID to return: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int index = findBookIndexById(books, id);

    if (index == -1)
    {
        std::cout << "Book not found." << std::endl;
        return;
    }

    if (!books[index].borrowed)
    {
        std::cout << "This book is not currently borrowed." << std::endl;
        return;
    }

    books[index].borrowed = false;
    books[index].borrowerName = "";

    std::cout << "Book returned successfully." << std::endl;
}

void saveBooksToFile(const std::vector<Book>& books, const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
    {
        std::cout << "Error: Could not open file for writing." << std::endl;
        return;
    }

    for (const Book& book : books)
    {
        file << book.id << "|"
            << book.title << "|"
            << book.author << "|"
            << book.category << "|"
            << book.borrowed << "|"
            << book.borrowerName << std::endl;
    }

    file.close();

    std::cout << "Books saved successfully." << std::endl;
}

void loadBooksFromFile(std::vector<Book>& books, const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        std::cout << "No existing book file found. Starting with an empty library." << std::endl;
        return;
    }

    books.clear();

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idText;
        std::string borrowedText;
        Book book;

        std::getline(ss, idText, '|');
        std::getline(ss, book.title, '|');
        std::getline(ss, book.author, '|');
        std::getline(ss, book.category, '|');
        std::getline(ss, borrowedText, '|');
        std::getline(ss, book.borrowerName);

        book.id = std::stoi(idText);
        book.borrowed = (borrowedText == "1");

        books.push_back(book);
    }

    file.close();

    std::cout << "Books loaded successfully." << std::endl;
}

int main()
{
    std::vector<Book> books;
    const std::string filename = "data/books.txt";
    int choice;

    loadBooksFromFile(books, filename);

    while (true)
    {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            addBook(books);
            break;

        case 2:
            displayAllBooks(books);
            break;

        case 3:
            searchBookByTitle(books);
            break;

        case 4:
            updateBook(books);
            break;

        case 5:
            deleteBook(books);
            break;

        case 6:
            borrowBook(books);
            break;

        case 7:
            returnBook(books);
            break;

        case 8:
            saveBooksToFile(books, filename);
            break;

        case 9:
            loadBooksFromFile(books, filename);
            break;

        case 10:
            saveBooksToFile(books, filename);
            std::cout << "Thank you for using the Library Management System." << std::endl;
            return 0;

        default:
            std::cout << "Invalid option. Please choose again." << std::endl;
        }
    }
}
