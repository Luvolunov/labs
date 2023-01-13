#include <iostream>

const int deqSize = 5;

// АТД Дек
template <typename T>
class Deque {
private:
    void showWarn() {
        printf("Дек переполнен. Вы не можете добавлять значения");
    }
    int size = 0;
    T data[deqSize];
public:
    // Полон ли дек
    bool isFull() {
        return size == deqSize;
    }
    // Пуст ли дек
    bool isEmpty() {
        return size == 0;
    }
    // Добавить элемент справа (в конец дека)
    void addRight(T element) {
        if (isFull()) {
            showWarn();
            return;
        }
        data[size++] = element;
    }
    // Добавить элемент слева (в начало дека)
    void addLeft(T element) {
        if (isFull()) {
            showWarn();
            return;
        }
        for (int i = size; i >= 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = element;
        size++;
    }
    // Получить размер
    int getSize() {
        return size;
    }
    // Получить первый элемент
    T getFirst() {
        if (isEmpty()) {
            printf("Дек пуст\n");
            return NULL;
        }
        return data[0];
    }
    // Получить последний элемент
    T getLast() {
        if (isEmpty()) {
            printf("Дек пуст\n");
            return NULL;
        }
        return data[size - 1];
    }
    // Удалить первый элемент (слева)
    void removeFirst() {
        for (int i = 0; i < size; ++i) {
            data[i] = data[i + 1];
        }
        data[size] = NULL;
        size--;
    }
    // Удалить последний элемент (справа)
    void removeLast() {
        data[size] = NULL;
        size--;
    }
    // Вывести все значения дека
    void printAll() {
        bool isFloat = typeid(float) == typeid(T);
        printf("[");
        for (int i = 0; i < size; ++i) {
            printf(isFloat ? "%f" : "%i", data[i]);
            if (i != size - 1) printf(", ");
        }
        printf("]\n");
    }
};


int main(int argc, char *argv[]) {
    // Тестирование дека на примере типа float
    Deque<float> deq;
    int res = 0;
    float val;
    do {
        printf("Меню:\n");
        printf("1. Добавить элемент в начало\n");
        printf("2. Добавить элемент в конец\n");
        printf("3. Удалить первый элемент\n");
        printf("4. Удалить последний элемент\n");
        printf("5. Получить первый элемент\n");
        printf("6. Получить последний элемент\n");
        printf("7. Текущий размер дека\n");
        printf("8. Вывести все значения дека\n");
        printf("9. Выход\n");
        printf("Введите номер: ");
        std::cin >> res;
        printf("\n");
        switch (res) {
            case 1:
                printf("Введите значение: ");
                std::cin >> val;
                printf("\n");
                deq.addLeft(val);
                break;
            case 2:
                printf("Введите значение: ");
                std::cin >> val;
                printf("\n");
                deq.addRight(val);
                break;
            case 3:
                deq.removeFirst();
                printf("Первый элемент удалён!\n");
                break;
            case 4:
                deq.removeLast();
                printf("Последний элемент удалён!\n");
                break;
            case 5:
                printf("Первый элемент: %f\n", deq.getFirst());
                break;
            case 6:
                printf("Последний элемент: %f\n", deq.getLast());
                break;
            case 7:
                printf("Размер дека: %i\n", deq.getSize());
                break;
            case 8:
                deq.printAll();
                break;
            default:
                break;
        }
        printf("\n");
    } while (res != 9);
    return 0;
}
