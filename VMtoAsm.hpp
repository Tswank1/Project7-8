#ifndef VMTOASM_HPP
#define VMTOASM_HPP
using namespace std;
#include <string>
#include <fstream>
#include <iostream>

extern ofstream asmOut; 

class VMtoAsm{
    private:
        int numJumps;
        int numCall;
    public:
        VMtoAsm();
        void WriteAsm(string vmOp);
        void WriteAsm2(string vmOp, string vmLastOp);
        void WriteAsm3(string vmOp, string vmMidOp, int num);
};
#endif