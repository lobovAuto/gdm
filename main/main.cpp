#include "main.hpp"


int main(int argc, char* argv[]){
    GdmFile project;
    ComponentsStruct comp_struct;
    Component temp = project.get_comp();
    
    while (temp.get_health()){
        comp_struct.add_component(temp);
        temp = project.get_comp();
    }
    comp_struct.print_struct();
    // Rri * temp = new GitRri("ssh://git@git.redpioneer.ru:2224/tools/dbc_agent.git","./temp/tools/dbc_agent");
    // temp->clone();
}