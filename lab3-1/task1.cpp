#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

enum class Rubber {
    Summer,
    Winter
};

std::string rubberToString(Rubber r){
    if (r == Rubber::Summer) return "летняя";
    if (r == Rubber::Winter) return "зимняя";
    return "неизвестная";
}

class Wheel
{
private:
    Rubber type;
    double diameter;
public:
    Wheel(Rubber r, double d) : type(r), diameter(d) {
        std::cout << "Создано колесо с резиной типа " 
        << rubberToString(type) << " и диаметром " << diameter << std::endl;
    }

    ~Wheel(){
        std::cout << "Уничтожено колесо с резиной типа " 
<< rubberToString(type) << " и диаметром " << diameter << std::endl;
    }

    void print() const {
        std::cout << "- тип: " << rubberToString(type)
        <<", диаметр: " << diameter << std::endl;
    }
};


class Car
{
private:
    std::string name;
    std::vector<Wheel> wheels;
public:
    Car(const std::string& n) : name(n) {
        wheels.reserve(4);
        std::cout << "Создана машина " << name << std::endl;
    }
    ~Car(){
        std::cout << "Уничтожена машина " << name << std::endl;
    }

    void addWheel(Rubber r, double d){
        wheels.emplace_back(r, d);
    }
    void print() const {
        std::cout << "\nМашина " << name << ":\n";
        for (const Wheel& w : wheels){
            w.print();
        }
        std::cout << std::endl;
    }
};

int main() {
    SetConsoleOutputCP(65001);  // вывод в UTF-8
    SetConsoleCP(65001);        // ввод в UTF-8

    Car car("Лада");
    car.addWheel(Rubber::Winter, 17.0);
    car.addWheel(Rubber::Winter, 17.0);
    car.addWheel(Rubber::Winter, 17.0);
    car.addWheel(Rubber::Winter, 17.0);
    car.print();

    std::cout << "Нажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
