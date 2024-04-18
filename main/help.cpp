#include "main.hpp"
using namespace std;
void print_line(const char * in){
    cout<<in<<endl;
}
void print_help(){
    print_line("Программа для выкачивания зависимостей из репозиториев");
    print_line("В начале каждого файла обязательно должно быть указание");
    print_line("на систему удаленного управления репозиториям");
    print_line("Пример:");
    print_line("ROOT_RMS ssh://git@git.redpioneer.ru:2224");
    print_line("Так же можно добавить корневую папку для выкачиваемых зависимостей");
    print_line("Это значит, что при выкачивании компонента");
    print_line("путь, указанный в корневой зависимости, будет опускаться");
    print_line("Пример:");
    print_line("ROOT_FOLDER //embedded");
    print_line("Символ комментария строки - #");
    print_line("Синтаксис подтяжки зависимости:");
    print_line("LINK logic/drivers/stepper.git main/head force");
    print_line("Где LINK - указатель на то, что далее следует ссылка на компонент");
    print_line("logic ... git - ссылка на компонент. В данном случае, начальный путь embedded опущен");
    print_line("main/head - ветка и комит");
    print_line("Если указать только ветку, то выкачается последний комит");
    print_line("Вместо комита можно указывать тег");
    print_line("Хинт force нужно добавлять, если несколько компоннетов");
    print_line("ссылаются на разные версии другого компонента.");
    print_line("Может быть вызван только в главном файле");
}