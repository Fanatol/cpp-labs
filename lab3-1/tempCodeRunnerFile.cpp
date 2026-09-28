#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

class Player
{
private:
    std::string name;
    int number;
    std::string role;
    static int count;
public:
    Player(std::string n, int nu, std::string r) : name(n), number(nu), role(r) {
        std::cout << "Создан игрок "<< name << " под номером " << number << std::endl;
        count++;
    }

    ~Player(){
        std::cout << "Удален игрок "<< name << " под номером " << number << std::endl;
        count--;
    }

    static int getCount() { return count; }

    std::string getName() const { return name; }
    int  getNumber() const { return number; }
    std::string getRole() const { return role; }

    void print() const {
        std::cout << "Игрок " << name << " под номером " 
        << number << std::endl;
    }
};
int Player::count = 0;

class Team
{
private:
    std::string name;
    std::vector<Player*> players;
public:
    Team(const std::string& n) : name(n) {
        std::cout << "Создана команда " << name << std::endl;
    }
    ~Team(){
        std::cout << "Расформирована команда " << name << std::endl;
    }

    void addPlayer(Player* p){
        if (p == nullptr) return;
        players.push_back(p);
    }
    void print() const {
        std::cout << "\nКоманда " << name << ":\n";
        for (const Player* p : players){
            p->print();
        }
        std::cout << std::endl;
    }
};

int main() {
    SetConsoleOutputCP(65001);  // вывод в UTF-8
    SetConsoleCP(65001);        // ввод в UTF-8

    Player p1("Иванов", 10, "нападающий");
    Player p2("Петров", 7, "защитник");
    Player p3("Сидоров", 1, "вратарь");

    std::cout << "Игроков до команды: " 
    << Player::getCount() << "\n";

    Team* team = new Team("Динамо");
    team->addPlayer(&p1);
    team->addPlayer(&p2);
    team->addPlayer(&p3);
    team->addPlayer(nullptr);
    team->print();

    delete team;

    std::cout << "Игроков после уничтожения команды: " 
    << Player::getCount() << "\n";

    std::cout << "Нажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
