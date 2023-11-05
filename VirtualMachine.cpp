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

    if(vmFile.find("Sys.vm") != -1){
        asmOut << "\t@256\n"
               << "\tD=A\n"
               << "\t@SP\n"
               << "\tM=D\n"
               << "\t@RETURN\n"
               << "\tD=A\n"
               << "\t@SP\n"
               << "\tA=M\n"
               << "\tM=D\n"
               << "\t@SP\n"
               << "\tM=M+1\n"

               << "\t@LCL\n"
               << "\tD=M\n"
               << "\t@SP\n"
               << "\tA=M\n"
               << "\tM=D\n"
               << "\t@SP\n"
               << "\tM=M+1\n"

               << "\t@ARG\n"
               << "\tD=M\n"
               << "\t@SP\n"
               << "\tA=M\n"
               << "\tM=D\n"
               << "\t@SP\n"
               << "\tM=M+1\n"

               << "\t@THIS\n"
               << "\tD=M\n"
               << "\t@SP\n"
               << "\tA=M\n"
               << "\tM=D\n"
               << "\t@SP\n"
               << "\tM=M+1\n"

               << "\t@THAT\n"
               << "\tD=M\n"
               << "\t@SP\n"
               << "\tA=M\n"
               << "\tM=D\n"
               << "\t@SP\n"
               << "\tM=M+1\n"

               << "\t@SP\n"
               << "\tD=M\n"
               << "\t@5\n"
               << "\tD=D-A\n"
               << "\t@0\n"
               << "\tD=D-A\n"
               << "\t@ARG\n"
               << "\tM=D\n"
               << "\t@SP\n"
               << "\tD=M\n"
               << "\t@LCL\n"
               << "\tM=D\n"
               << "\t@Sys.init\n"
               << "\t0;JMP\n"
               << "(RETURN)" << endl;
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
