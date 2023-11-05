#include "VMtoAsm.hpp"
#include "Parser.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
Parser virtualparser;
ofstream asmOut;
 
int main(int argc, char const *argv[]){
    string vmFile, asmFile;
    ifstream VM;

    vmFile = string(argv[1]);
    VM.open(vmFile);
    if(!VM.is_open() || argc < 2){
        return -1;
    }

    asmFile = vmFile.substr(0, vmFile.find_last_of('.')) + ".asm";
    asmOut.open(asmFile);
    if(!asmOut.is_open()){
        return -1;
    }

    cout << "Outputing to asm file" << endl;
    string input;
    while(getline(VM, input)){
        virtualparser.parse(input);
    }

    asmOut.close();
    VM.close();

    cout << "Completed outputing" << endl;

    return 0;
}
