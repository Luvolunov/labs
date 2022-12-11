#include <iostream>
#include <cstdlib>
// Элемент связного списка
template <typename DataType>
class Element {
public:
    DataType data;
    Element *next;
    Element(DataType info) {
        next = nullptr;
        data = info;
    }
};
// АТД Стек основанный на связном списке
template <typename DataType>
class Stack {
protected:
    Element<DataType> *first;
    Element<DataType> *last;
public:
    Stack() {
        first = nullptr;
        last = nullptr;
    };
    ~Stack() {
        Element<DataType>* currentEl = first;
        while (currentEl) {
            Element<DataType>* next = currentEl->next;
            delete currentEl;
            currentEl = next;
        }
    }
    void push(DataType data) {
        Element<DataType>* el = new Element<DataType>(data);
        if (first == nullptr) {
            first = el;
            last = el;
            return;
        }
        last->next = el;
        last = el;
    }
    void pop() {
        if (first == nullptr) return;
        if (first == last) {
            delete first;
            first = nullptr;
            last = nullptr;
            return;
        }
        Element<DataType>* el = first;
        while (el->next != last) el = el->next;
        el->next = nullptr;
        delete last;
        last = el;
    }
    void printAll() {
        if (first == nullptr) return;
        Element<DataType>* currentEl = first;
        while (currentEl != nullptr) {
            printf("%i", currentEl->data);
            if (currentEl->next != nullptr) printf(" -> ");
            
            currentEl = currentEl->next;
        }
        printf("\n");
    }
    Element<DataType>* peek() {
        return last;
    }
};

int main(int argc, char *argv[]) {
    Stack<int> list;
    int key = 0;
    do {
        printf("Тестирование АТД Стек\n");
        printf("1. push - добавление элемента\n");
        printf("2. pop - удаление последнего элемента\n");
        printf("3. peek - получение последнего элемента\n");
        printf("4. printAll - вывод всего списка\n");
        printf("5. выход\n");
        std::cin >> key;
        switch (key) {
            case 1:
                int val;
                printf("Введите значение для push: ");
                std::cin >> val;
                printf("\n");
                list.push(val);
                break;
            case 2:
                list.pop();
                printf("Последний элемент удалён!\n");
                break;
            case 3:
                printf("Последний элемент: %i\n", list.peek()->data);
                break;
            case 4:
                list.printAll();
                break;
            default:
                break;
        }
    } while (key != 5);
    return 0;
}
