#include "main.hpp"

int main(int argc, char* argv[]){
    GdmFile project;
    Component temp = project.get_comp();
    temp.add_call_source("another_addr", "another", BranchType::branch, "new_branch");
    std::cout<<temp<<std::endl;
}