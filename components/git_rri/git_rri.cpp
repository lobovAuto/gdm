#include "git_rri.hpp"

GitRri::GitRri(/* args */)
{
}

GitRri::GitRri(std::string url, std::string addr): url(url), location(addr)
{
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
int GitRri::check_repo_to_gdm_files() {
    return 0;
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