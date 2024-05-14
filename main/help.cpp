#include "main.hpp"
using namespace std;

void print_help(){
    std::ifstream help;
    help.open("help.txt");
    if(not help.is_open()){
        std::cerr<<"There is no help file."<<std::endl;
        exit(1);
    }
    while (!help.eof()){
        string temp;
        getline(help,temp);
        cout<<temp<<endl;
    }
}