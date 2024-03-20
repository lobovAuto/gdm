#pragma once

#include <fstream>

class ComponentsStruct {
public:
    int save(); // сохранить структуру данных
    int load(); // загрузить структуру из файла
private:
    int file_parse(); // распарсить отдельный файл

public: // отладочные публичные методы
    void print_struct(); // вывести на экран текущую структуру
};