#include "git_rri.hpp"

GitRri::GitRri(std::ostream & log_stream/* args */):log_stream(log_stream)
{
}

GitRri::GitRri(std::ostream & log_stream, std::string url, std::string addr, std::string branch, std::string commit):
                log_stream(log_stream),
                url(url), location(addr, 0, addr.find(".git")), branch(branch), commit(commit){
    // folder_name = get_folder_name();
}

GitRri::GitRri(std::ostream & log_stream, const Component & c):
    log_stream(log_stream),
    url(c.get_repo_address()), location(c.get_addr_call_file()),
    branch(c.get_branch()){
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

int GitRri::check_repo_to_gdm_file() {
    using namespace std::filesystem;

    if (not exists("./.gdm/"+folder_name))
        create_directory("./.gdm/"+folder_name);
    else {
        remove_all("./.gdm/"+folder_name);
        create_directory("./.gdm/"+folder_name);
    }

    std::vector<std::string> lines;
    std::string command = "git clone --depth 1 "+ url;
    command += " ./.gdm/"+folder_name;
    command += " -b "+branch;
    // std::cout<<command<<std::endl;
    boost_command(command.c_str(), lines);
    bool is_component_file = exists("./.gdm/"+folder_name+"/component.gdm");
    return is_component_file;
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
    std::string command ="git clone "+url;
    command += " "+location;
    command += " -b "+branch;
    log_stream<<command<<std::endl;
    int res = boost_command(command.c_str(), lines);
    for (auto str:lines) log_stream<<str<<std::endl;
    command = "git -C "+location+" checkout " + commit;
    log_stream<<command<<std::endl;
    res = boost_command(command.c_str(), lines);
    for (auto str:lines) log_stream<<str<<std::endl;    
    return 0;
}