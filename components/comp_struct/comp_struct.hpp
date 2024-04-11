#pragma once

#include <fstream>
#include <vector>
#include "component.hpp"
#include "git_rri.hpp"
#include "gdm_file.hpp"

class ComponentsStruct {
public:
    int save(); // сохранить структуру данных
    int load(); // загрузить структуру из файла
    int add_component(const Component &); // добавить файл в структуру
    bool check_struct();
    int check_struct_comp_to_reference(); // проверяет все элементы структуры на ссылочные зависимости
    int clone_all_components(); // скачивает все компоненты
private:
    unsigned find_component(const Component &) const; // проверить массив на наличие такого компонента
    int expand_components(const Component &, unsigned pos); // добавить данные вызова к существующему компоненту
    int file_parse(); // распарсить отдельный файл
    std::vector<Component> components;
    std::vector<bool> comp_err; // если true - в компоненте есть ошибка
public: // отладочные публичные методы
    void print_struct(); // вывести на экран текущую структуру
    void print_err_res(); // вывести на экран результаты по ошибкам
};