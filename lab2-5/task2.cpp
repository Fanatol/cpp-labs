#include <iostream>
#include <cmath>
#include <stdexcept>
#include <windows.h>

class Rational {
private:
    int num, den;

    // поиск НОД
    static int gcd(int a, int b) {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            int temp = a;
            a = b;
            b = temp % b;
        }
        return a;
    }

    // перенос минуса в числитель
    void normalize() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

    // сокращение дроби
    void reduce() {
        int g = gcd(num, den);  // вызов static-метода
        num /= g;
        den /= g;
    }

public:

    // конструкторы
    Rational(int n = 0, int d = 1) {
        if (d == 0)
            throw std::invalid_argument("Знаменатель не может быть равен нулю!");
        num = n;
        den = d;
        normalize();
        reduce();
    }

    Rational(const Rational& other) {
        num = other.num;
        den = other.den;
    }

    // деструктор
    ~Rational() {}

    // геттеры
    int getNum() const { return num; }
    int getDen() const { return den; }

    // сеттеры
    void setNum(int n) {
        num = n;
        normalize();
        reduce();
    }
    void setDen(int d) {
        if (d == 0) throw std::invalid_argument("Знаменатель не может быть равен нулю!");
        den = d;
        normalize();
        reduce();
    }
    // Дружественные функции для потокового ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        if (r.den == 1)
            os << r.num;
        else
            os << r.num << "/" << r.den;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Rational& r) {
        int n, d;
        is >> n >> d;
        
        if (!is.fail()) {
            r = Rational(n, d);
        }
        
        return is;
    }

    // сравнение дробей
    bool operator==(const Rational& other) const {
        return num == other.num and den == other.den;
    }
    bool operator!=(const Rational& other) const {
        return num != other.num or den != other.den;
    }
        bool operator<(const Rational& other) const {
        return num * other.den < other.num * den;
    }
    bool operator>(const Rational& other) const {
        return num * other.den > other.num * den;
    }
        bool operator<=(const Rational& other) const {
        return (*this < other) or (*this == other);
    }
    bool operator>=(const Rational& other) const {
        return (*this > other) or (*this == other);
    }

    // сложение дробей
    Rational operator+(const Rational& other) const {
        return Rational(num * other.den + other.num * den, den * other.den);
    }

    // вычитание дробей
    Rational operator-(const Rational& other) const {
        return Rational(num * other.den - other.num * den, den * other.den);
    }
    // умножение дробей
    Rational operator*(const Rational& other) const {
        return Rational(num * other.num, den * other.den);
    }

    // деление дробей
    Rational operator/(const Rational& other) const {
        if (other.num == 0)
            throw std::runtime_error("Деление на ноль!");
        return Rational(num * other.den, den * other.num);
    }

    // быстрые операции
    Rational& operator+=(const Rational& other) {
        *this = *this + other;
        return *this;
    }
    Rational& operator-=(const Rational& other) {
        *this = *this - other;
        return *this;
    }
    Rational& operator*=(const Rational& other) {
        *this = *this * other;
        return *this;
    }
    Rational& operator/=(const Rational& other) {
        *this = *this / other;
        return *this;
    }

    //инкрименты
    Rational& operator++() {
        *this = *this + Rational(1);
        return *this;
    }
    Rational operator++(int) {
        Rational temp = *this;
        ++(*this);
        return temp; 
    }

    // ()
    double operator()() const {
    return static_cast<double>(num) / den;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "=== БАЗОВЫЙ УРОВЕНЬ ===\n\n";

    // Конструкторы
    Rational a(3, 4);
    Rational b(2, 3);
    Rational c;
    Rational d(a);

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c (по умолчанию) = " << c << "\n";
    std::cout << "d (копия a) = " << d << "\n\n";

    // Арифметика
    std::cout << "a + b = " << a + b << "\n";
    std::cout << "a - b = " << a - b << "\n";
    std::cout << "a * b = " << a * b << "\n";
    std::cout << "a / b = " << a / b << "\n\n";

    // Сокращение и нормализация
    Rational e(6, 8);
    Rational f(3, -4);
    std::cout << "6/8 сокращено до: " << e << "\n";
    std::cout << "3/(-4) нормализовано до: " << f << "\n\n";

    // Сравнение ==, !=
    Rational g(3, 4);
    std::cout << "a == g? " << (a == g ? "да" : "нет") << "\n";
    std::cout << "a != b? " << (a != b ? "да" : "нет") << "\n\n";

    std::cout << "=== СРЕДНИЙ УРОВЕНЬ ===\n\n";

    // Составные операторы
    std::cout << "--- Составные операторы ---\n";
    Rational s(1, 2);
    std::cout << "s = " << s << "\n";
    s += Rational(1, 3);
    std::cout << "s += 1/3 -> " << s << "\n";
    s -= Rational(1, 6);
    std::cout << "s -= 1/6 -> " << s << "\n";
    s *= Rational(2, 1);
    std::cout << "s *= 2 -> " << s << "\n";
    s /= Rational(3, 1);
    std::cout << "s /= 3 -> " << s << "\n\n";

    // Операторы сравнения <, >, <=, >=
    std::cout << "--- Сравнения ---\n";
    Rational p(1, 2);
    Rational q(2, 3);
    std::cout << "p = " << p << ", q = " << q << "\n";
    std::cout << "p < q? " << (p < q ? "да" : "нет") << "\n";
    std::cout << "p > q? " << (p > q ? "да" : "нет") << "\n";
    std::cout << "p <= q? " << (p <= q ? "да" : "нет") << "\n";
    std::cout << "p >= q? " << (p >= q ? "да" : "нет") << "\n\n";

    // Инкремент
    std::cout << "--- Инкремент ---\n";
    Rational inc(1, 2);
    std::cout << "inc = " << inc << "\n";
    ++inc;
    std::cout << "++inc -> " << inc << "\n";
    inc++;
    std::cout << "inc++ -> " << inc << "\n\n";

    // Функтор
    std::cout << "--- Функтор ---\n";
    Rational func(3, 4);
    std::cout << "func = " << func << "\n";
    std::cout << "func() = " << func() << "\n\n";

    // Ввод с клавиатуры
    Rational h;
    std::cout << "Введите дробь (числитель знаменатель): ";
    std::cin >> h;
    std::cout << "Вы ввели: " << h << "\n\n";

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
