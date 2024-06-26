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
        i.print_to_screen(std::cout);
        std::cout<<"========================================"<<std::endl;
    }
}

void ComponentsStruct::print_err_res(){
    for (size_t i=0; i<comp_err.size(); i++){
        std::cout<<"pos "<<i<<" res "<<!comp_err[i]<<std::endl;
    }
}


bool ComponentsStruct::check_struct(){
    for(size_t i=0; i<components.size(); i++){  
        int check_result = components[i].check_component();
        if (check_result){ 
            std::cerr<<"Error!"<<std::endl;
            std::cerr<<"Component "<<components[i].get_repo_address()<<std::endl;
            std::cerr<<"Called from: "<<components[i].get_addr_call_file()<<std::endl;
            std::cerr<<"It has different call parameters"<<std::endl;
            comp_err.push_back(true); } // если есть ошибка, то ставим true
        else { comp_err.push_back(false);}
    }
    for (bool i : comp_err){
        if (i == true) { // если хотя бы в одном компоненте есть ошибка, выдаем общую ошибку
            return false;
        }

    }
    return true;
}

int ComponentsStruct::check_struct_comp_to_reference(){
    for(unsigned i=0;;){
        int check_res = components[i].check_component(); // проверяем компонент на коллизии версий
        if (check_res) continue; // если есть ошибки, то пропускаем этот компонет
        
        GitRri temp_repo(log_stream, components[i]);
        int res = temp_repo.check_repo_to_gdm_file();
        if (res){ // если есть подзависимости, парсим их
            GdmFile gdm_component(".dgm/temp_repo.get_folder_name()/", log_stream);
            Component temp = gdm_component.get_comp();
            while (temp.get_health()){
                add_component(temp);
                temp = gdm_component.get_comp();
            } 
        }

        if (++i>=components.size()) break; // остановка по подстижению конца вектора
    }
    //идем по каждому компоненту
    //выкачиваем его и проверяем
    //если ничего нет, идем дальше
    //если есть файл, парсим его, добавляем в общую структуру
    
    return 0;
}

int ComponentsStruct::clone_all_components(){
    int i = 0;
    for(Component j : components){
        GitRri temp_repo(log_stream,j.get_repo_address(), j.get_local_address(), j.get_branch(), j.get_commit());
        i = temp_repo.clone();
    }
    return 0;
}