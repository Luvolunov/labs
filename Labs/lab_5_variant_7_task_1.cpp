#include <iostream>

template <typename T>
void printArr(T arr[], const unsigned long length) {
    bool isFloat = typeid(float) == typeid(T);
    printf("[");
    for (unsigned long i = 0; i < length; ++i) {
        printf(isFloat ? "%f" : "%i", arr[i]);
        if (i != length - 1) printf(", ");
        
    }
    printf("];\n");
}

template <typename T>
T getMaxNegative(T arr[], const unsigned long length) {
    T max = 0;
    for (unsigned long i = 0; i < length; ++i) {
        if (max == 0 && arr[i] < 0) max = arr[i];
        if (arr[i] < 0 && arr[i] > max) max = arr[i];
    }
    return max;
}

int main(int argc, char *argv[]) {
    const int length = 5;
    int arr[length] = { -120, 12, -60, -100, 100 };
    float arr2[length] = { -1.2, -0.4, 0, 2.1, 4.5 };
    int res = 0;
    do {
        printf("Меню:\n");
        printf("1. int\n");
        printf("2. float\n");
        printf("3. выход\n");
        printf("Введите номер: ");
        std::cin >> res;
        printf("\n");
        switch (res) {
            case 1:
                printf("Массив: ");
                printArr(arr, length);
                printf("Максимальный отрицательный элемент: %i\n", getMaxNegative(arr, length));
                break;
            case 2:
                printf("Массив: ");
                printArr(arr2, length);
                printf("Максимальный отрицательный элемент: %f\n", getMaxNegative(arr2, length));
            default:
                break;
        }
        printf("\n");
    } while (res != 3);
    return 0;
}
