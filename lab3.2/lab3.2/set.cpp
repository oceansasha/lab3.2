#include <iostream> 
#include <vector> 
#include <algorithm> // ��� std::sort

template <typename T> // �������� ���������� ������
                     
class Set; // �������� ���������� ��������� ������, ��� ������ �������� ������ ��� std::cout << ���������;

template <typename T>
std::ostream& operator<<(std::ostream& tempStream, const Set<T>& tempVector);

template <typename T>
class Set {
private:
    std::vector <T> setVector; 
public:
    Set(); 
    Set(const Set<T>& tempVector);
    ~Set(); 
    void add(const T tempValue); //��� ���-� � ������ �����������
    void add(); //���� �������-1 � ����-��
    void removeItem(const T tempValue); //����-� �����-��
    void removeItem(); //������-�� ��� ����� � ����-��

    size_t size() const; // ������ ��� ��������� ������� ������� �� ������� ������
    Set<T> operator+(const Set<T>& tempVector) const;    // ���������� ��������� ��������, � ��������� ������������ ��� ����������� ��������
    Set<T>& operator=(const Set<T>& tempVector);    // ���������� ������������
    Set<T> uniteVector(const Set<T>& tempVector) const; // ������� ��� ����������� ��������, ��� �� ���������� ��� ������ ��������� ��������
    Set<T> intersectVector(const Set<T>& tempVector) const;   // ������� ��� ����������� ��������
    friend std::ostream& operator<< <T>(std::ostream& tempStream, const Set<T>& tempVector);    // ���������� ��������� ������, ������� �������������, ����� �������� �� ������ ��������� ������ ������

    bool isIntersects(const Set<T>& tempVector) const; // ���� ������������
    bool isProperSubset(const Set<T>& tempVector) const; // ���� ������ � �-�� ���������
    bool isEqual(const Set<T>& tempVector) const; // ���� �����
    bool isUnique(const T tempValue) const; // ���� ������� ���������� �������� � �������
    bool isPresented(const T tempValue) const; // ���� �������� ��� ������� � �������
};

template <typename T>
Set<T>::Set() {
    setVector.clear();
}

template <typename T>
Set<T>::Set(const Set<T>& tempVector) {}

template <typename T>
Set<T>::~Set() {} 

template <typename T>
void Set<T>::removeItem(const T tempValue) {
    try {
        // ���� ���� ������ ��������, ������� �� �������
        if (isPresented(tempValue)) {
            setVector.erase(std::remove(setVector.begin(), setVector.end(), tempValue), setVector.end());
        }
    }
    catch (const char* exception) {
        std::cerr << "�� ���������� ������� ������:\n" << exception << std::endl;
    }
}

template <typename T>
void Set<T>::removeItem() {
    T inputItem;
    std::cin >> inputItem;

    if (!std::cin.fail()) {
        removeItem(inputItem);
    }
    else {
        std::cerr << "��������� ������ ��� ������ ��������� ����������." << std::endl;
        std::cin.clear();
        std::exit(1);
    }
}

template <typename T>
size_t Set<T>::size() const {
    return setVector.size();
}

template <typename T>
std::ostream& operator<<(std::ostream& tempStream, const Set<T>& tempVector) {
    tempStream << "{ ";
    for (auto it = tempVector.setVector.begin(); it < tempVector.setVector.end() - 2; it++) {
        tempStream << *it << ", ";
    }
    tempStream << *(tempVector.setVector.end() - 1) << " }";
    std::cout << std::endl;
    return tempStream;
}

template <typename T>
Set<T>& Set<T>::operator=(const Set<T>& tempVector) {
    if (this != &tempVector) {
        setVector = tempVector.setVector;
    }
    return *this;
}

template <typename T>
Set<T> Set<T>::operator+(const Set<T>& tempVector) const {
    return uniteVector(tempVector);
}

template <typename T>
Set<T> Set<T>::uniteVector(const Set<T>& tempVector) const {
    Set<T> newSet = size() > tempVector.size() ? *this : tempVector; //���� ������ ������
    if (size() > tempVector.size()) {
        for (const T& item : tempVector.setVector) {
            if (!newSet.isPresented(item)) {
                newSet.add(item);
            }
        }
    }
    else {
        for (const T& item : setVector) {
            if (!newSet.isPresented(item)) {
                newSet.add(item);
            }
        }
    }
    return newSet;
}

template <typename T>
Set<T> Set<T>::intersectVector(const Set<T>& tempVector) const {
    Set<T> newSet;
    if (size() <= tempVector.size()) {
        for (const T& item : setVector) {
            if (isPresented(item)) {
                newSet.add(item);
            }
        }
    }
    else {
        for (const T& item : setVector) {
            if (isPresented(item)) {
                newSet.add(item);
            }

        }
    }
    return newSet;
}

//----------------bool------

template <typename T>
bool Set<T>::isIntersects(const Set<T>& tempValue) const {
    return std::any_of(setVector.begin(), setVector.end(), [&](const T item) {
        return tempValue.isPresented(item);
    });
}

template <typename T>
bool Set<T>::isProperSubset(const Set<T>& tempValue) const {
    return std::any_of(setVector.begin(), setVector.end(), [&](const T item) {
        return tempValue.isPresented(item);
    });
}

template <typename T>
bool Set<T>::isEqual(const Set<T>& tempValue) const {
    return size() == tempValue.size() && isProperSubset(tempValue);
}

template <typename T>
bool Set<T>::isUnique(const T tempValue) const {
    return std::find(setVector.begin(), setVector.end(), tempValue) == setVector.end();
}

template <typename T>
bool Set<T>::isPresented(const T tempValue) const {
    return std::find(setVector.begin(), setVector.end(), tempValue) != setVector.end();
}

template <typename T>
bool isTypeValid(const T tempValue) {
    return tempValue % 3;
}

template <typename T>
void Set<T>::add(const T tempValue) {
    if (isTypeValid(tempValue) && isUnique(tempValue)) {
        setVector.push_back(tempValue);
    }
}

template <typename T>
void Set<T>::add() {
    T yourInput;
    std::cin >> yourInput;
    if (!std::cin.fail()) {
        add(yourInput);
    }
}
