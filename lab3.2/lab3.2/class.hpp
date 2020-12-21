#include <iostream> 
#include <vector>
#include <fstream> 
#include "class.hpp" // ������ ������ Set - ��������� ����������� ��� �����������
#include <algorithm> // ��� std::find()

void openFile(std::ifstream& file, const std::string& filename) {
    try {
        file.open(filename);
        if (!file.is_open()) { // ���� ���� �� ��������
            throw "���� �� ���������.";
        }
    }
    catch (const char* exception) { // ���������� ��� ������ ������
        std::cerr << "������ �������� " << filename << ": " << exception << std::endl;
        std::exit(1);
    }
}

//------���������� ������� � �����--------
void fillVector(std::ifstream& file, Set<int>& tempVector) {
    for (std::string tempLine; file;) {
        std::getline(file, tempLine);
        if (!tempLine.empty()) tempVector.add(std::stoi(tempLine));
    }
}

void showMenu()
{
    std::cout << "0. ����� \n"
        << "1. � ����� �� �������� ������ ����� ���������."
        << "������� �� ����� ������������ ��������� ���������� ��������� � ���.\n"
        << "2. ���������� ��� ����������� ����� ����� ��������� �1 � �2 � ������������,\n"
        << "�� ������������, ���� �� �������� �������� ������.\n"
        << "3. �������� � ��������� �1 ������� a (�������� � ����������).\n"
        << "4. ������� �� ��������� �2 ������� b (�������� � ����������).\n"
        << "5. �������� ��������� �4 ��� ����������� �������� �2 � �3.\n"
        << "6. �������� ��������� �5 ��� ����������� �������� �1 � �3\n"
        << "7. ��� ��� �������� ���������\n"
        << "�����:)\t>>>\t";
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

    Set<int> m1Vector; // ��������� � ����� m1.txt
    Set<int> m2Vector; // ��������� � ����� m2.txt
    Set<int> m3Vector; // ��������� � ����� m3.txt
    Set<int> m4Vector; // ��������� ����������� M2 � M3
    Set<int> m5Vector; // ��������� ����������� �1 � �3

    fillVector(m1, m1Vector);
    fillVector(m2, m2Vector);
    fillVector(m3, m3Vector);

    std::cout << "��������� �� ������:\n";
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
                std::cout << "������� ���� �������� �����:/\n";
            }
            else if (d == a) {
                std::cout << "����� ������� ��������� - M1";
            }
            else if (d == b) {
                std::cout << "����� ������� ��������� - M2";
            }
            else if (d == c) {
                std::cout << "����� ������� ��������� - M3";
            }
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            break;

        case 2:
            if (m1Vector.isEqual(m2Vector)) {
                std::cout << "�1 � �2 �����";
            }
            else if (m1Vector.isProperSubset(m2Vector)) {
                std::cout << "M1 �������� ������������ �2";
            }
            else if (m2Vector.isProperSubset(m1Vector)) {
                std::cout << "M2 �������� ������������ �1";
            }
            else if (m1Vector.isIntersects(m2Vector)) {
                std::cout << "�1 � �2 ������������";
            }
            else {
                std::cout << "�1 � �2 �� ������������";
            }
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl; 
            break;
 
        case 3:
            std::cout << "M1 = " << m1Vector;
            std::cout << "�������, ��� ������ �������� � M1:\n";
            m1Vector.add(); // ���������� ������� add() ��� ����� � ����������
            std::cout << "M1 = " << m1Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl; 
            break;

        case 4: //------������� �� ��������� �2 ������� b (�������� � ����������)------
            std::cout << "M2 = " << m2Vector;
            std::cout << "��� ������� � M2?";
            m2Vector.removeItem(); // �������� ���������� ������� removeItem() ��� ����� � ����������
            std::cout << "M2 = " << m2Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            break;

        case 5: //-------�������� ��������� �4 ��� ����������� �������� �2 � �3-----
            std::cout << "M2 = " << m2Vector;
            std::cout << "M3 = " << m3Vector;
            std::cout << "����������� M2 � M3:\n";
            m4Vector = m2Vector + m3Vector;
            std::cout << "M4 = " << m4Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            break;

        case 6: //-----�������� ��������� �5 ��� ����������� �������� �1 � �2---------
            std::cout << "M1 = " << m1Vector;
            std::cout << "M2 = " << m2Vector;
            std::cout << "����������� M1 � M2:\n";
            m5Vector = m1Vector.intersectVector(m2Vector); // �������� ������� ��� �������� ����������� ���� ��������
            std::cout << "M5 = " << m5Vector;
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            break;

        case 7:
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            std::cout << "������� �� ������:\n";
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

