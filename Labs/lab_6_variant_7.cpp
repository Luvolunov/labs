#include <iostream>
#include <sstream>

// Ключевые слова в С, которые нельзя использовать для идентификаторов
const unsigned long keywordsArrLength = 36;
const char notAllowedInIdentifiers[keywordsArrLength][10] = {
    "auto", "bool", "break", "case", "catch", "char", "const", "continue", "default", "do", "double", "else", "enum",
    "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

const std::string firstLetters {"abcdefghijklmnopqrstuvwxyz_"}; // Разрешённые символы для первой буквы идентификатора
const std::string allowedSymbols {"abcdefghijklmnopqrstuvwxyz_123456789"}; // Разрешённые символы для идентификатора
const std::string hexSymbols {"0123456789abcdef"}; // Разрешённые символы для 16-ричной системы счисления

// Функция, которая сравнивает 2 строки
bool isStrEqual(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
};
// Функция, которая проверяет включает ли в себя строка str первый символ из массива символов c[0]
bool includesFirstSymbol(const std::string &str, const char *c) {
    return str.find(tolower(c[0])) != std::string::npos;
}
// Класс строки
class MyStr {
protected:
    char *string;
    unsigned long length;
    // Функция для задания строки с расчётом длины
    void setStr(const char *str) {
        length = strlen(str);
        string = new char[length + 1];
        strcpy(string, str);
    }
public:
    // Пустой конструктор, длина = 0
    MyStr(): length(0) {
        string = new char[1];
        string[0] = '\0';
    };
    // Конструктор со строкой
    MyStr(const char *str) {
        printf("Constructor\n");
        setStr(str);
    };
    // Конструктор с одним символом
    MyStr(char c) {
        string = new char[2];
        string[0] = c;
        string[1] = '\0';
        length = 1;
    };
    // Конструктор копирования
    MyStr(const MyStr &obj) {
        printf("Copy constructor\n");
        length = obj.length;
        string = new char[length];
        strcpy(string, obj.string);
    };
    // Деструктор с очищением памяти от строки
    ~MyStr() {
       delete []string;
    }
    // Метод для получения строки
    char* getStr() {
        return string;
    }
    // Метод для получения длины строки
    unsigned long getLength() {
        return length;
    }
    // Перегрузка оператора присваивания
    MyStr& operator =(const char* str) noexcept {
        printf("Operator =\n");
        length = strlen(str);
        delete []string; // Удаляем предыдушее значение
        string = new char[length];
        strcpy(string, str);
        return *this;
    }
};
// Класс строки-идентификатора
class IdentifierString: public MyStr {
public:
    // Статический метод, который проверяет строку на корректность идентификаторам в C
    static bool checkStrIsCorrect(const char* str) {
        const unsigned long length = firstLetters.length();
        bool correctFirstLetter = false;
        for (int i = 0; i < length; ++i) {
            const char letter = firstLetters.at(i);
            if (letter == tolower(str[0])) { // Проверяем первый символ строки на корректность
                correctFirstLetter = true;
            }
        }
        if (!correctFirstLetter) return false; // Если первый символ некорректный, то и сам идентификатор тоже
        
        const unsigned long allowedSymbolsLength = allowedSymbols.length();
        const unsigned long strLength = strlen(str);
        
        for (int i = 0; i < strLength; ++i) {
            if (!includesFirstSymbol(allowedSymbols, &str[i])) return false; // Если символ идентификатора не входит в список разрешённых, то идентификатор некорректен
        }
        
        for (int i = 0; i < keywordsArrLength; ++i) {
            if (isStrEqual(notAllowedInIdentifiers[i], str)) return false; // Если строка равна одному из ключевых слов в C, то идентификатор некорректен
        }
        
        return true;
    }
    IdentifierString(const char* str): MyStr() {
        printf("IdentifierString constructor\n");
        if (checkStrIsCorrect(str)) { // Если идентификатор корректный, то сохраняем его
            setStr(str);
            return;
        }
        setStr(""); // Иначе пустая строка
    }
    // Перегрузка оператора присваивания
    IdentifierString& operator =(const char* str) noexcept {
        printf("Operator =\n");
        delete []string; // Очищаем память от предыдущего значения
        const char* correctStr = checkStrIsCorrect(str) ? str : ""; // Если строка корректная, то сохраняем, иначе пустая строка
        setStr(correctStr);
        return *this;
    }
    // Перегрузка оператора сравнения
    bool operator ==(IdentifierString str) {
        return isStrEqual(string, str.string);
    }
    
    void toLowerCase() {
        const unsigned long strLength = strlen(string);
        for (int i = 0; i < strLength; ++i) {
            string[i] = tolower(string[i]);
        }
    }
};

class HexString: public MyStr {
public:
    // Статический метод для проверки строки на принадлежность к 16-ричной системе счисления
    static bool checkHexIsCorrect(const char* str) {
        if (!includesFirstSymbol(hexSymbols, &str[0]) && str[0] != '+' && str[0] != '-') return false;
        const unsigned long strLength = strlen(str);
        for (int i = 1; i < strLength; ++i) {
            if (!includesFirstSymbol(hexSymbols, &str[i])) return false;
        }
        return true;
    }
    HexString(const char* str): MyStr() {
        setStr(checkHexIsCorrect(str) ? str : "0");
    }
    // Проверка, может ли 16-ричная строка быть приведена к long int без потери данных
    bool canBeLong() {
        bool strHasSymbol = string[0] == '-' || string[0] == '+'; // Есть ли в начале строки символы + или -
        unsigned long strLength = strlen(string);
        strLength -= strHasSymbol ? 1 : 0; // Если строка содержит + или -, то уменьшить строку на 1 это будет настоящая длина hex записи
        if (strLength > 8) return false; // Если длина строки превышает 8 символов, то такая строка точно больше long int, т.к. максимальное значение long int в 16-ричной системе 7FFFFFFF - и состоит из 8 символов
        if (strLength < 8) return true; // Если меньше 8, то тогда строка точно меньше long int и может быть приведена к 10-ричной системе
        
        // Если же строка равна 8 символам, то проверяем
        // Если первый символ будет равен 8, то минимальное число по hex будет 80000000 - имеет 8 символов и самое минимальное с первой цифрой 8 - которое равняется максимальному числу в long int + 1, соответственно если первый символ меньше или равен 7, то такая запись корректна
        // Первый символ может быть представлен знаками + или -, поэтому есть проверка на strHasSymbol
        return (strHasSymbol && string[1] <= '7') || (!strHasSymbol && string[0] <= '7');
    }
    // Перегрузка оператора "меньше"
    bool operator <(HexString str) {
        long long int first;
        long long int second;
        
        std::stringstream ss; // Создаём поток
        ss << std::hex << string; // Строку переводим из hex в 10-ричную систему
        ss >> first; // Из потока записываем в переменную
        ss.str(""); // Сбрасываем строку
        ss.clear(); // Очищаем флаги
        
        ss << std::hex << str.string;
        ss >> second;

        return first < second; // Сраниваем как обычные числа
    }
    const char* operator +(HexString str) {
        long long int first;
        long long int second;
        
        std::stringstream ss; // Создаём поток
        ss << std::hex << string; // Строку переводим из hex в 10-ричную систему
        ss >> first; // Из потока записываем в переменную
        ss.str(""); // Сбрасываем строку
        ss.clear(); // Очищаем флаги
        
        ss << std::hex << str.string;
        ss >> second;
        ss.str(""); // Сбрасываем строку
        ss.clear(); // Очищаем флаги
        
        first += second;
        
        ss << std::hex << first;
        
        return ss.str().c_str();
    }
};

int main(int argc, char *argv[]) {
    IdentifierString identifier("int");
    IdentifierString secondIdentifier("Int");
    printf("Некорректный идентификатор: %s\n", identifier.getStr());
    identifier = "CORRECT";
    printf("Корректный идентификатор: %s\n\n", identifier.getStr());
    printf("Сравнение идентификаторов: %d\n\n", identifier == secondIdentifier);
    HexString hexStr("FFF");
    HexString hexStr2("FFF");
    printf("Идентификатор: %s\n", identifier.getStr());
    identifier.toLowerCase();
    printf("Идентификатор после приведения к нижнему регистру: %s\n\n", identifier.getStr());
    printf("Меньше ли первая hex строка: %d\n", hexStr < hexStr2);
    printf("Сложение двух hex строк: %s\n", hexStr + hexStr2);
    return 0;
}
