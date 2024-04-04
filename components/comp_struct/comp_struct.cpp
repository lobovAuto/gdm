#include "comp_struct.hpp"

int ComponentsStruct::add_component(const Component & input){
    unsigned find_result = find_component(input);
    if (find_result){
        expand_components(input, find_result-1);
    } else {
        components.push_back(input);
    }
    return 0;
}

unsigned ComponentsStruct::find_component(const Component & input) const {
    for(size_t i=0; i<components.size(); i++){
        if(components[i].addr_is_eq(input)) return i+1;
    }
    return 0;
}

int ComponentsStruct::expand_components(const Component & input, unsigned pos){
    components[pos].add_call_source(input.get_brdunit());
    return 0;
}

void ComponentsStruct::print_struct(){
    std::cout<<"========================================"<<std::endl;
    for(auto i : components){
        i.print_to_screen();
        std::cout<<"========================================"<<std::endl;
    }
}

void ComponentsStruct::print_err_res(){
    for (size_t i=0; i<comp_err.size(); i++){
        std::cout<<"pos "<<i<<" res "<<comp_err[i]<<std::endl;
    }
}

bool ComponentsStruct::chech_struct(){
    for(size_t i=0; i<components.size(); i++){  // Если вектор ComponentBroadcastUnit единичного размера, то пропускам
        if (components[i].get_comp_list().size()==1) {
            comp_err.push_back(true);           // Не забываем эту позицию отметить верной
            continue;
        }
        bool res=false; // временная переменная
        for (size_t j=0; j<components[i].get_comp_list().size(); j++){ // идем по всем значениям вектора ComponentBroadcastUnit
            
            for (size_t k=j+1; k<components[i].get_comp_list().size(); k++){ // сравниваем "взятое" ранее значение со следующим
                if (not(components[i].get_comp_list()[j]==                   // если они не равны, то поднимаем флаг ошибки
                        components[i].get_comp_list()[k])){
                    res = true;
                    break;
                }
                
            }
            if (res) break;
        }
        if (res) comp_err.push_back(false); // пушим ошибку
        else comp_err.push_back(true); 
    }

    for (bool i : comp_err){
        if (i == false) return false;
    }
    return true;
}