#include "main.hpp"


int main(int argc, char* argv[]){
    GdmFile project;
    Component temp = project.get_comp();
    // temp.add_call_source("another_addr", "another", BranchType::branch, "new_branch");
    temp.print_to_screen();
    std::cout<<temp.get_comp_list().begin()->address_in_project<<std::endl;
    std::cout<<temp.get_comp_list().begin()->address_call_file<<std::endl;
    std::cout<<temp.get_comp_list().begin()->branch<<std::endl;
}