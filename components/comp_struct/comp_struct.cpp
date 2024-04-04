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