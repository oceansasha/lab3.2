#include <iostream> 
#include <vector>
#include <fstream> 
#include "class.hpp" // Импорт класса Set - различных манипуляций над множествами
#include <algorithm> // Для std::find()

void openFile(std::ifstream& file, const std::string& filename) {
    try {
        file.open(filename);
        if (!file.is_open()) { // Если файл не открылся
            throw "Файл не обнаружен.";
        }
    }
    catch (const char* exception) { // Конструция для вывода ошибки
        std::cerr << "Ошибка открытия " << filename << ": " << exception << std::endl;
        std::exit(1);
    }
}

//------заполнение данными с файла--------
void fillVector(std::ifstream& file, Set<int>& tempVector) {
    for (std::string tempLine; file;) {
        std::getline(file, tempLine);
        if (!tempLine.empty()) tempVector.add(std::stoi(tempLine));
    }
}

void showMenu()
{
    std::cout << "0. Выход \n"
        << "1. В каком из множеств больше всего элементов."
        << "Вывести на экран наименование множества количество элементов в нем.\n"
        << "2. Определить как соотносятся между собой множества М1 и М2 – пересекаются,\n"
        << "не пересекаются, одно из множеств содержит другое.\n"
        << "3. Добавить в множество М1 элемент a (вводится с клавиатуры).\n"
        << "4. Удалить из множества М2 элемент b (вводится с клавиатуры).\n"
        << "5. Получить множество М4 как объединение множеств М2 и М3.\n"
        << "6. Получить множество М5 как пересечение множеств М1 и М3\n"
        << "7. Ещё раз показать множества\n"
        << "Введи:)\t>>>\t";
}

int main()
{
    setlocale(LC_ALL, "");
    int a, b, c, d; 

    std::ifstream m1;
    std::ifstream m2;
    std::ifstream m3;

    openFile(m1, "m1.txt");
    openFile(m2, "m2.txt");
    openFile(m3, "m2.txt");

    Set<int> m1Vector; // Множество с файла m1.txt
    Set<int> m2Vector; // Множество с файла m2.txt
    Set<int> m3Vector; // Множество с файла m3.txt
    Set<int> m4Vector; // Множество объединения M2 и M3
    Set<int> m5Vector; // Множество пересечения М1 и М3

    fillVector(m1, m1Vector);
    fillVector(m2, m2Vector);
    fillVector(m3, m3Vector);

    std::cout << "Множества из файлов:\n";
    std::cout << m1Vector;
    std::cout << m2Vector;
    std::cout << m3Vector;

    int expression;
    bool boolExpression = true;

    while (boolExpression)
    {
        showMenu();
        std::cin >> expression; 
        std::cout << std::endl << std::endl << std::endl << std::endl << std::endl; 
        switch (expression)
        {

        case 0:
            boolExpression = false; 
            break;

        case 1:
            a = m1Vector.size();
            b = m2Vector.size();
            c = m3Vector.size();
            d = std::max({ a,b,c });
            if (d == a && a == b && b == c) {
                std::cout << "Размеры всех множеств равны:/\n";
            }
            else if (d == a) {
                std::cout << "Самое большое множество - M1";
            }
            else if (d == b) {
                std::cout << "Самое большое множество - M2";
            }
            else if (d == c) {
                std::cout << "Самое большое множество - M3";
            }
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            break;

        case 2:
            if (m1Vector.isEqual(m2Vector)) {
                std::cout << "М1 и М2 равны";
            }
            else if (m1Vector.isProperSubset(m2Vector)) {
                std::cout << "M1 содержит подмножество М2";
            }
            else if (m2Vector.isProperSubset(m1Vector)) {
                std::cout << "M2 содержит подмножество М1";
            }
            else if (m1Vector.isIntersects(m2Vector)) {
                std::cout << "М1 и М2 пересекаются";
            }
            else {
                std::cout << "М1 и М2 не пересекаются";
            }
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl; 
            break;
 
        case 3:
            std::cout << "M1 = " << m1Vector;
            std::cout << "Введите, что хотите добавить в M1:\n";
            m1Vector.add(); // перегрузка функции add() для ввода с клавиатуры
            std::cout << "M1 = " << m1Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl; 
            break;

        case 4: //------Удалить из множества М2 элемент b (вводится с клавиатуры)------
            std::cout << "M2 = " << m2Vector;
            std::cout << "Что удалить в M2?";
            m2Vector.removeItem(); // Вызываем перегрузку функции removeItem() для ввода с клавиатуры
            std::cout << "M2 = " << m2Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            break;

        case 5: //-------Получить множество М4 как объединение множеств М2 и М3-----
            std::cout << "M2 = " << m2Vector;
            std::cout << "M3 = " << m3Vector;
            std::cout << "Объединение M2 и M3:\n";
            m4Vector = m2Vector + m3Vector;
            std::cout << "M4 = " << m4Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            break;

        case 6: //-----Получить множество М5 как пересечение множеств М1 и М2---------
            std::cout << "M1 = " << m1Vector;
            std::cout << "M2 = " << m2Vector;
            std::cout << "Пересечение M1 и M2:\n";
            m5Vector = m1Vector.intersectVector(m2Vector); // Вызываем функцию для операции пересечения двух множеств
            std::cout << "M5 = " << m5Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            break;

        case 7:
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            std::cout << "Вектора из файлов:\n";
            std::cout << m1Vector;
            std::cout << m2Vector;
            std::cout << m3Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

            break;
        default:
            break;
        }
    }


    return 0;
}

