#include <iostream> 
#include <vector> 
#include <algorithm> // Для std::sort

template <typename T> // Прототип шаблонного класса
                     
class Set; // Прототип перегрузки оператора вывода, для вывода векторов просто как std::cout << множество;

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
    void add(const T tempValue); //для доб-я в вектор поэлементно
    void add(); //ввод перемен-1 с клав-ры
    void removeItem(const T tempValue); //удал-е перем-ой
    void removeItem(); //перегр-ка для ввода с клав-ры

    size_t size() const; // Геттер для получения размера вектора из привата класса
    Set<T> operator+(const Set<T>& tempVector) const;    // Перегрузка оператора сложения, в частности используется для объединения множеств
    Set<T>& operator=(const Set<T>& tempVector);    // Перегрузка присваивания
    Set<T> uniteVector(const Set<T>& tempVector) const; // Функция для объединения множеств, она же вызывается при вызове оператора сложения
    Set<T> intersectVector(const Set<T>& tempVector) const;   // Функция для пересечения множеств
    friend std::ostream& operator<< <T>(std::ostream& tempStream, const Set<T>& tempVector);    // Перегрузка оператора вывода, сделана дружественной, чтобы выводить не только используя вектор класса

    bool isIntersects(const Set<T>& tempVector) const; // Если пересекаются
    bool isProperSubset(const Set<T>& tempVector) const; // Если входит в н-ое множество
    bool isEqual(const Set<T>& tempVector) const; // Если равны
    bool isUnique(const T tempValue) const; // Если имеются уникальные значения в векторе
    bool isPresented(const T tempValue) const; // Если значения уже имеются в векторе
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
        // Если есть повтор элементы, удаляем из массива
        if (isPresented(tempValue)) {
            setVector.erase(std::remove(setVector.begin(), setVector.end(), tempValue), setVector.end());
        }
    }
    catch (const char* exception) {
        std::cerr << "Не получилось удалить объект:\n" << exception << std::endl;
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
        std::cerr << "Произошла ошибка при чтении введенной переменной." << std::endl;
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
    Set<T> newSet = size() > tempVector.size() ? *this : tempVector; //если размер больше
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
