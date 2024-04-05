#include "git_rri.hpp"

GitRri::GitRri(/* args */)
{
}

GitRri::GitRri(std::string url, std::string addr): url(url), location(addr)
{
    folder_name = get_folder_name();
}

GitRri::~GitRri()
{
}

int GitRri::push() {

    return 0;
}
int GitRri::pull() {
    return 0;
}

const std::string GitRri::get_folder_name(){
    size_t pos;
    for (pos=location.size();pos>0; pos--){
        if (location[pos]=='/') break;
    }
    return std::string(location, pos+1);
}

int GitRri::check_repo_to_gdm_files() {
    using namespace std::filesystem;

    if (not exists("./.gdm/"+folder_name))
        create_directory("./.gdm/"+folder_name);
    else {
        remove_all("./.gdm/"+folder_name);
        create_directory("./.gdm/"+folder_name);
    }

    std::vector<std::string> lines;
    std::string command = "git clone --depth 1 "+url+" ./.gdm/"+folder_name;
    // std::cout<<command<<std::endl;
    boost_command(command.c_str(), lines);

    return exists("./.gdm/"+folder_name+"/component.gdm");
}
int GitRri::checkout() {
    return 0;
}
int GitRri::status() {
    return 0;
}

int GitRri::boost_command(const char * command, std::vector<std::string> & result){
    boost::process::ipstream pipe_stream;
    boost::process::child c(command, boost::process::std_out > pipe_stream);

    std::string line;
    
    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty()){
        result.push_back(line);
    }
    c.wait();
    return c.exit_code();
}

int GitRri::clone() {
    std::vector<std::string> lines;
    std::string temp ="git clone "+url+" "+location;
    int res = boost_command(temp.c_str(), lines);
    // for (std::string t : lines){
        // std::cout<<t<<std::endl;
    // }
    std::cout<<"res is: ";
    std::cout<<res<<std::endl;
    
    return 0;
}