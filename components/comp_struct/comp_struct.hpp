#pragma once

#include <fstream>
#include <vector>
#include "component.hpp"

class ComponentsStruct {
public:
    int save(); // сохранить структуру данных
    int load(); // загрузить структуру из файла
    int add_component(const Component &); // добавить файл в структуру
    bool check_struct();
private:
    unsigned find_component(const Component &) const; // проверить массив на наличие такого компонента
    int expand_components(const Component &, unsigned pos); // добавить данные вызова к существующему компоненту

    int file_parse(); // распарсить отдельный файл
    std::vector<Component> components;
    std::vector<bool> comp_err;
public: // отладочные публичные методы
    void print_struct(); // вывести на экран текущую структуру
    void print_err_res(); // вывести на экран результаты по ошибкам
};