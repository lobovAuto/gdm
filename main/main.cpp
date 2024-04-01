#include "main.hpp"


int main(int argc, char* argv[]){
    // GdmFile project;
    // Component temp = project.get_comp();
    // temp.add_call_source("another_addr", "another", BranchType::branch, "new_branch");
    // temp.print_to_screen();
    GitRri git_rri("ssh://git@git.redpioneer.ru:2224/tools/dbc_agent.git","./temp/tools/dbc_agent");
    git_rri.clone();
}