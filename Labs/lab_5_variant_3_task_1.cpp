#include <stdio.h>
#include <iostream>
#include <typeinfo>
template <typename T>
void printArr(T arr[], const unsigned long length) {
    bool isFloat = typeid(float) == typeid(T);
    printf("[");
    for (unsigned long i = 0; i < length; ++i) {
        printf(isFloat ? "%f" : "%c", arr[i]);
        if (i != length - 1) printf(", ");
        
    }
    printf("];\n");
}

template <typename T>
void swap(T* xp, T* yp)
{
    T temp = *xp;
    *xp = *yp;
    *yp = temp;
}

template <typename T>
void sortByBubble(T arr, const unsigned long length) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (arr[i] > arr[j]) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    const int arrLength = 5;
    float arr[arrLength] = {0.1, 0.2, 0.3, 0.4, 0.33};
    char chArr[arrLength + 1] = "abcde";
    int res;
    while (res != 1 && res != 2) {
        printf("Типы на выбор:\n");
        printf("1. float\n");
        printf("2. char\n");
        printf("Введите номер необходимого типа: ");
        std::cin >> res;
    }
    printf("\n");
    if (res == 1) {
        printf("Исходный массив:\n");
        printArr(arr, arrLength);
        sortByBubble(arr, arrLength);
        printf("Массив после сортировки:\n");
        printArr(arr, arrLength);
    } else {
        printf("Исходный массив:\n");
        printArr(chArr, arrLength);
        sortByBubble(chArr, arrLength);
        printf("Массив после сортировки:\n");
        printArr(chArr, arrLength);
    }
    
    return 0;
}
