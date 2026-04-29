#include <iostream>
#include <cstdlib>

using namespace std;

//інтерфейс для функторів (предикатів)
template<class T>
class Predicate {
public:
    virtual bool operator() (T x) = 0;
};

//конкретний функтор: 
template<class T>
class Negative : public Predicate<T> {
public:
    virtual bool operator() (T x) {
        return x < 0;
    }
};

//алгоритм erase_copy: копіює всі елементи, КРІМ тих, що дорівнюють заданому значенню 
template<class T>
int erase_copy(T* begin, T* end, T* to, T valueToRemove) {
    int count = 0;
    for (T* from = begin; from < end; from++) {
        if (*from != valueToRemove) { //якщо не дорівнює — зберігаємо
            *to = *from;
            to++;
            count++;
        }
    }
    return count; //повертаємо нову кількість елементів
}

//алгоритм erase_copy_if: копіює всі елементи, КРІМ тих, що задовольняють умові предикату
template<class T>
int erase_copy_if(T* begin, T* end, T* to, Predicate<T>& p) {
    int count = 0;
    for (T* from = begin; from < end; from++) {
        if (!p(*from)) { //якщо умова видалення НЕ виконується — зберігаємо
            *to = *from;
            to++;
            count++;
        }
    }
    return count;
}


int main() {
    system("chcp 65001 > nul"); // Налаштування консолі для UTF-8

    int a[7] = { 10, -5, 3, -1, 7, 3, 8 }; // Вхідний контейнер
    int t[8] = { 6, 2, 2, 1, -6, -7, 2, 1 }; //test
    int b[7] = { 0 }; // Вихідний контейнер 1
    int c[7] = { 0 }; // Вихідний контейнер 2

    cout << "Початковий масив: ";
    for (int i = 0; i < 7; i++) cout << a[i] << " ";
    cout << endl;

   /* cout << "Додатковий масив: ";
    for (int i = 0; i < 8; i++) cout << t[i] << " ";
    cout << endl;*/

    // Тест 1: Видаляємо всі трійки (алгоритм erase_copy)
    int newSize1 = erase_copy(a, a + 7, b, 3);
    cout << "Після erase_copy (видалено всі трійки): ";
    for (int i = 0; i < newSize1; i++) cout << b[i] << " ";
    cout << endl;


    /*int newSizeT = erase_copy(t, t + 8, b, 2);
    cout << "Після erase_copy (видалено всі двійки): ";
    for (int i = 0; i < newSizeT; i++) cout << b[i] << " ";
    cout << endl;*/



    // Тест 2: Видаляємо від'ємні числа через функтор (алгоритм erase_copy_if)
    Negative<int> isNeg;
    int newSize2 = erase_copy_if(a, a + 7, c, isNeg);
    cout << "Після erase_copy_if (видалено від'ємні): ";
    for (int i = 0; i < newSize2; i++) cout << c[i] << " ";
    cout << endl;


    /*Negative<int> isNeg1;
    int newSizeTT = erase_copy_if(t, t + 8, c, isNeg1);
    cout << "Після erase_copy_if (видалено від'ємні): ";
    for (int i = 0; i < newSizeTT; i++) cout << c[i] << " ";
    cout << endl;*/

    return 0;
}