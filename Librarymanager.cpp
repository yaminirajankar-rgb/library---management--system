#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book(int i, string t, string a, bool status = false) {
        id = i;
        title = t;
        author = a;
        issued = status;
    }
};

vector<Book> books;

void saveData() {
    ofstream file("library.txt");

    for (const auto &book : books) {
        file << book.id << "|"
             << book.title << "|"
             << book.author << "|"
             << book.issued << endl;
    }

    file.close();
}

void loadData() {
    ifstream file("library.txt");

    int id;
    bool issued;
    string title, author;

    while (file >> id) {
        file.ignore();
        getline(file, title, '|');
        getline(file, author, '|');
        file >> issued;
        file.ignore();

        books.push_back(Book(id, title, author, issued));
    }

    file.close();
}

void addBook() {
    int id;
    string title, author;

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, title);

    cout << "Enter Author Name: ";
    getline(cin, author);

    books.push_back(Book(id, title, author));
    saveData();

    cout << "Book added successfully!\n";
}

void listBooks() {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "\n--- Book List ---\n";

    for (const auto &book : books) {
        cout << "ID: " << book.id << endl;
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "Status: "
             << (book.issued ? "Issued" : "Available") << endl;
        cout << "-------------------\n";
    }
}

void searchBook() {
    string title;
    cin.ignore();

    cout << "Enter title to search: ";
    getline(cin, title);

    bool found = false;

    for (const auto &book : books) {
        if (book.title == title) {
            cout << "\nBook Found!\n";
            cout << "ID: " << book.id << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Status: "
                 << (book.issued ? "Issued" : "Available") << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Book not found.\n";
}

void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    for (auto &book : books) {
        if (book.id == id) {
            if (book.issued) {
                cout << "Book is already issued.\n";
            } else {
                book.issued = true;
                saveData();
                cout << "Book issued successfully!\n";
            }
            return;
        }
    }

    cout << "Book not found.\n";
}

void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    for (auto &book : books) {
        if (book.id == id) {
            if (!book.issued) {
                cout << "Book is already available.\n";
            } else {
                book.issued = false;
                saveData();
                cout << "Book returned successfully!\n";
            }
            return;
        }
    }

    cout << "Book not found.\n";
}

int main() {
    loadData();

    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. List Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;

            case 2:
                listBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                returnBook();
                break;

            case 6:
                saveData();
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
