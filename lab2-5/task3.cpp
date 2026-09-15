#include <iostream>
#include <stdexcept>
#include <cmath>
#include <windows.h>

class Matrix {
private:
    int** data;
    int rows;
    int cols;

public:
    // Конструктор по умолчанию
    Matrix() : data(nullptr), rows(0), cols(0) {}

    // Параметризованный конструктор
    Matrix(int r, int c) : rows(r), cols(c) {
        if (r <= 0 or c <= 0)
            throw std::invalid_argument("Размеры должны быть положительными!");
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++)
                data[i][j] = 0;
        }
    }

    // Конструктор копирования
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++)
                data[i][j] = other.data[i][j];
        }
    }

    // Деструктор 
    ~Matrix() {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            // освободить старую память
            for (int i = 0; i < rows; i++)
                delete[] data[i];
            delete[] data;

            // скопировать
            rows = other.rows;
            cols = other.cols;
            data = new int*[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; j++)
                    data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    // Геттеры
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Оператор [] — доступ к строке (неконстантная версия)
    int* operator[](int i) {
        if (i < 0 or i >= rows)
            throw std::out_of_range("Индекс строки вне диапазона!");
        return data[i];
    }

    const int* operator[](int i) const {
        if (i < 0 or i >= rows)
            throw std::out_of_range("Индекс строки вне диапазона!");
        return data[i];
    }

    // Оператор () — доступ к элементу (i, j)
    int& operator()(int i, int j) {
        if (i < 0 or i >= rows or j < 0 or j >= cols)
            throw std::out_of_range("Индекс вне диапазона!");
        return data[i][j];
    }

    const int& operator()(int i, int j) const {
        if (i < 0 or i >= rows or j < 0 or j >= cols)
            throw std::out_of_range("Индекс вне диапазона!");
        return data[i][j];
    }

    // Сложение матриц
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows or cols != other.cols)
            throw std::invalid_argument("Размеры матриц должны совпадать!");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Вычитание матриц
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows or cols != other.cols)
            throw std::invalid_argument("Размеры матриц должны совпадать!");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    // Умножение матриц
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows)
            throw std::invalid_argument("Число столбцов первой матрицы должно равняться числу строк второй!");
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < other.cols; j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++)
                    sum += data[i][k] * other.data[k][j];
                result.data[i][j] = sum;
            }
        return result;
    }

    // Сравнение
    bool operator==(const Matrix& other) const {
        if (rows != other.rows or cols != other.cols) return false;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (data[i][j] != other.data[i][j]) return false;
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return not (*this == other);
    }

    // Транспонирование
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result.data[j][i] = data[i][j];
        return result;
    }

    // Оператор преобразования типа — определитель для 2x2
    explicit operator double() const {
        if (rows != 2 or cols != 2)
            throw std::runtime_error("Определитель вычисляется только для матрицы 2x2!");
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    // Дружественная функция для умножения на скаляр (слева)
    friend Matrix operator*(int scalar, const Matrix& m) {
        Matrix result(m.rows, m.cols);
        for (int i = 0; i < m.rows; i++)
            for (int j = 0; j < m.cols; j++)
                result.data[i][j] = m.data[i][j] * scalar;
        return result;
    }

    // Дружественная функция для умножения на скаляр (справа)
    friend Matrix operator*(const Matrix& m, int scalar) {
        return scalar * m;
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++)
                os << m.data[i][j] << " ";
            os << "\n";
        }
        return os;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::cout << "=== Класс Matrix (повышенный уровень) ===\n\n";

    // Создание матриц
    Matrix A(2, 2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    Matrix B(2, 2);
    B(0, 0) = 5; B(0, 1) = 6;
    B(1, 0) = 7; B(1, 1) = 8;

    std::cout << "A:\n" << A << "\n";
    std::cout << "B:\n" << B << "\n";

    // Сложение и вычитание
    std::cout << "A + B:\n" << A + B << "\n";
    std::cout << "A - B:\n" << A - B << "\n";

    // Умножение матриц
    std::cout << "A * B:\n" << A * B << "\n";

    // Умножение на скаляр
    std::cout << "A * 2:\n" << A * 2 << "\n";
    std::cout << "3 * A:\n" << 3 * A << "\n";

    // Оператор []
    std::cout << "A[0][1] = " << A[0][1] << "\n";
    std::cout << "A(1, 0) = " << A(1, 0) << "\n\n";

    // Транспонирование
    std::cout << "A транспонированная:\n" << A.transpose() << "\n";

    // Сравнение
    std::cout << "A == B? " << (A == B ? "да" : "нет") << "\n";
    std::cout << "A != B? " << (A != B ? "да" : "нет") << "\n\n";

    // Преобразование к double
    std::cout << "det(A) = " << static_cast<double>(A) << "\n\n";

    // Копирование
    Matrix C = A;
    std::cout << "C (копия A):\n" << C << "\n";

    // Присваивание
    Matrix D(2, 2);
    D = A;
    std::cout << "D (после D = A):\n" << D << "\n";

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}