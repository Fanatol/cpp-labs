#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

class Book {
private:
    std::string name;
    std::string author;
    static int count;
public:
    Book(const std::string& n, const std::string& a) : name(n), author(a) {
        count++;
        std::cout << "Создана книга " << name << ", автор - " << author << std::endl;
    }

    ~Book() {
        count--;
        std::cout << "Удалена книга " << name << ", автор - " << author << std::endl;
    }

    static int getCount() { return count; }
    std::string getName() const { return name; }
    std::string getAuthor() const { return author; }

    void print() const {
        std::cout << "Книга " << name << ", автор - " << author << std::endl;
    }
};
int Book::count = 0;

class Library
{
private:
    std::string name;
    std::vector<Book*> books;
    static Library* instance;

    Library(const std::string& n) : name(n) {
        std::cout << "Создана библиотека " << name << std::endl;
    }
    ~Library() {
        std::cout << "Удалена библиотека " << name << std::endl;
    }
public:
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    static Library* getInstance() {
        if (instance == nullptr) {
            instance = new Library("Городская библиотека");
        }
        return instance;
    }   

    void addBook(Book* b){
        if (b == nullptr) return;
        books.push_back(b);
    }
    void print() const {
        std::cout << "\nБиблиотека " << name << ":\n";
        for (const Book* b : books){
            b->print();
        }
        std::cout << std::endl;
    }
    static int getTotalBooks() { return Book::getCount(); }
};
Library* Library::instance = nullptr;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Book b1("Война и мир", "Л. Толстой");
    Book b2("Преступление и наказание", "Ф. Достоевский");
    Book b3("Евгений Онегин", "А. Пушкин");

    std::cout << "Книг до библиотеки: " << Book::getCount() << "\n";

    Library* lib1 = Library::getInstance();
    Library* lib2 = Library::getInstance();
    std::cout << "lib1 == lib2? " << (lib1 == lib2 ? "да" : "нет") << "\n";

    lib1->addBook(&b1);
    lib1->addBook(&b2);
    lib1->addBook(&b3);
    lib1->addBook(nullptr); 

    lib1->print();

    std::cout << "Всего книг: " << Library::getTotalBooks() << "\n";

    std::cout << "Нажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
