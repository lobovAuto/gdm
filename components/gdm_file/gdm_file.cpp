#include "gdm_file.hpp"

GdmFile::GdmFile(){
    file.open("project.gdm");
    if(not file.is_open()){
        std::cerr<<"There is no main project file."<<std::endl;
        exit(1);
    }
}

Component GdmFile::get_comp(){
    if (file.eof()){
        return Component();
    }
    Component temp("ssh://git@git.redpioneer.ru:2224/tools/dbc_agent.git", "tools/dbc_agent", "HEAD", BranchType::branch, "last");
    return temp;
}

GdmFile::~GdmFile(){

}