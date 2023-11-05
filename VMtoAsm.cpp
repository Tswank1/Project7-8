#include "VMtoAsm.hpp"

VMtoAsm::VMtoAsm(){
    numJumps = 0;
    numCall = 0;
}

void VMtoAsm::WriteAsm(string vmOp){
    if(vmOp == "add"){
        asmOut << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\tA=A-1\n"
               << "\tM=D+M" << endl;
    }
    else if(vmOp == "sub"){
        asmOut << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\tA=A-1\n"
               << "\tM=M-D" << endl;
    }
    else if(vmOp == "neg"){
        asmOut << "\t@SP\n"
               << "\tA=M-1\n"
               << "\tM=-M" << endl;
    }
    else if(vmOp == "and"){
        asmOut << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\tA=A-1\n"
               << "\tM=D&M" << endl;
    }
    else if(vmOp == "or"){
        asmOut << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\tA=A-1\n"
               << "\tM=D|M\n" << endl;
    }
    else if(vmOp == "not"){
        asmOut << "\t@SP\n"
               << "\tA=M-1\n"
               << "\tM=!M" << endl;
    }
    else if(vmOp == "eq"){
        asmOut << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\tA=A-1\n"
               << "\tD=M-D\n"
               << "\t@FALSE" << numJumps << "\n"
               << "\tD;JNE\n"
               << "\t@SP\n"
               << "\tA=M-1\n"
               << "\tM=-1\n"
               << "\t@SKIP" << numJumps << "\n"
               << "\t0;JMP\n"
               << "(FALSE" << numJumps << ")\n"
               << "\t@SP\n"
               << "\tA=M-1\n"
               << "\tM=0\n"
               << "(SKIP" << numJumps << ")" << endl;
        numJumps++;
    }
    else if(vmOp == "gt"){
        asmOut << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\tA=A-1\n"
               << "\tD=M-D\n"
               << "\t@FALSE" << numJumps << "\n"
               << "\tD;JLE\n"
               << "\t@SP\n"
               << "\tA=M-1\n"
               << "\tM=-1\n"
               << "\t@SKIP" << numJumps << "\n"
               << "\t0;JMP\n"
               << "(FALSE" << numJumps <<  ")\n"
               << "\t@SP\n"
               << "\tA=M-1\n"
               << "\tM=0\n"
               << "(SKIP" << numJumps << ")" << endl;
        numJumps++;
    }
    else if(vmOp == "lt"){
        asmOut << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\tA=A-1\n"
               << "\tD=M-D\n"
               << "\t@FALSE" << numJumps << "\n"
               << "\tD;JGE\n"
               << "\t@SP\n"
               << "\tA=M-1\n"
               << "\tM=-1\n"
               << "\t@SKIP" << numJumps << "\n"
               << "\t0;JMP\n"
               << "(FALSE" << numJumps << ")\n"
               << "\t@SP\n"
               << "\tA=M-1\n"
               << "\tM=0\n"
               << "(SKIP" << numJumps << ")" << endl;
        numJumps++;
    }
    else if(vmOp == "return"){
        asmOut << "\t@LCL\n"
               << "\tD=M\n"
               << "\t@R11\n"
               << "\tM=D\n"
               << "\t@5\n"
               << "\tA=D-A\n"
               << "\tD=M\n"
               << "\t@R12\n"
               << "\tM=D\n"

               << "\t@ARG\n"
               << "\tD=M\n"
               << "\t@0\n"
               << "\tD=D+A\n"
               << "\t@R13\n"
               << "\tM=D\n"
               << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\t@R13\n"
               << "\tA=M\n"
               << "\tM=D\n"

               << "\t@ARG\n"
               << "\tD=M\n"
               << "\t@SP\n"
               << "\tM=D+1\n"

               << "\t@R11\n"
               << "\tD=M-1\n"
               << "\tAM=D\n"
               << "\tD=M\n"
               << "\t@THAT\n"
               << "\tM=D\n"

               << "\t@R11\n"
               << "\tD=M-1\n"
               << "\tAM=D\n"
               << "\tD=M\n"
               << "\t@THIS\n"
               << "\tM=D\n"

               << "\t@R11\n"
               << "\tD=M-1\n"
               << "\tAM=D\n"
               << "\tD=M\n"
               << "\t@ARG\n"
               << "\tM=D\n"

               << "\t@R11\n"
               << "\tD=M-1\n"
               << "\tAM=D\n"
               << "\tD=M\n"
               << "\t@LCL\n"
               << "\tM=D\n"

               << "\t@R12\n"
               << "\tA=M\n"
               << "\t0;JMP" << endl;
    }
}

void VMtoAsm::WriteAsm2(string vmOp, string vmLastOp){
    if(vmOp == "label"){
        asmOut << "(" << vmLastOp << ")" << endl;
    }
    else if(vmOp == "goto"){
        asmOut << "\t@" << vmLastOp << "\n"
               << "\t0;JMP" << endl;
    }
    else if(vmOp == "if-goto"){
        asmOut << "\t@SP\n"
               << "\tAM=M-1\n"
               << "\tD=M\n"
               << "\t@" << vmLastOp << "\n"
               << "\tD;JNE" << endl;
    }
}

void VMtoAsm::WriteAsm3(string vmOp, string vmMidOp, int num){
    if(vmOp == "push"){
        if(vmMidOp == "constant"){
            asmOut << "\t@" << num << "\n"
                   << "\tD=A\n"
                   << "\t@SP\n"
                   << "\tA=M\n"
                   << "\tM=D\n"
                   << "\t@SP\n"
                   << "\tM=M+1" << endl;
        }
        else if(vmMidOp == "local" ||vmMidOp == "argument" || vmMidOp == "this" || vmMidOp == "that" || vmMidOp == "temp"){
            if(vmMidOp == "local"){
                asmOut << "\t@LCL" << endl;
            }
            else if(vmMidOp == "argument"){
                asmOut << "\t@ARG" << endl;
            }
            else if(vmMidOp == "this"){
                asmOut << "\t@THIS" << endl;
            }
            else if(vmMidOp == "that"){
                asmOut << "\t@THAT" << endl;
            }
            else if(vmMidOp == "temp"){
                asmOut << "\t@R5" << endl;
                num += 5;
            }
            asmOut << "\tD=M\n"
                   << "\t@" << num << "\n"
                   << "\tA=D+A\n"
                   << "\tD=M\n"
                   << "\t@SP\n"
                   << "\tA=M\n"
                   << "\tM=D\n"
                   << "\t@SP\n"
                   << "\tM=M+1" << endl;
        }
        else if(vmMidOp == "static" || vmMidOp == "pointer"){
            if(vmMidOp == "static"){
                asmOut << "\t@" << 16+num << endl;
            }
            else if(vmMidOp == "pointer"){
                if(num == 0){
                    asmOut << "\t@THIS" << endl;
                }
                else if(num == 1){
                    asmOut << "\t@THAT" << endl;
                }   
            }
            asmOut << "\tD=M\n"
                   << "\t@SP\n"
                   << "\tA=M\n"
                   << "\tM=D\n"
                   << "\t@SP\n"
                   << "\tM=M+1" << endl;
        }
    }
    else if(vmOp == "pop"){
        if(vmMidOp == "local" ||vmMidOp == "argument" || vmMidOp == "this" || vmMidOp == "that" || vmMidOp == "temp"){
            if(vmMidOp == "local"){
                asmOut << "\t@LCL" << endl;
            }
            else if(vmMidOp == "argument"){
                asmOut << "\t@ARG" << endl;
            }
            else if(vmMidOp == "this"){
                asmOut << "\t@THIS" << endl;
            }
            else if(vmMidOp == "that"){
                asmOut << "\t@THAT" << endl;
            }
            else if(vmMidOp == "temp"){
                asmOut << "\t@R5" << endl;
                num += 5;
            }
            asmOut << "\tD=M\n"
                   << "\t@" << num << "\n"
                   << "\tD=D+A\n"
                   << "\t@R13\n"
                   << "\tM=D\n"
                   << "\t@SP\n"
                   << "\tAM=M-1\n"
                   << "\tD=M\n"
                   << "\t@R13\n"
                   << "\tA=M\n"
                   << "\tM=D" << endl;
        }
        else if(vmMidOp == "static" || vmMidOp == "pointer"){
            if(vmMidOp == "static"){
                asmOut << "\t@" << 16+num << endl;
            }
            else if(vmMidOp == "pointer"){
                if(num == 0){
                    asmOut << "\t@THIS" << endl;
                }
                else if(num == 1){
                    asmOut << "\t@THAT" << endl;
                }   
            }
            asmOut << "\tD=A\n"
                   << "\t@R13\n"
                   << "\tM=D\n"
                   << "\t@SP\n"
                   << "\tAM=M-1\n"
                   << "\tD=M\n"
                   << "\t@R13\n"
                   << "\tA=M\n"
                   << "\tM=D" << endl;
        }
    }
    else if(vmOp == "function"){
        asmOut << "(" << vmMidOp << ")" << endl;
        for(int i = 0; i < num; i++){
            asmOut << "\t@SP\n"
                   << "\tA=M\n"
                   << "\tM=0\n"
                   << "\t@SP\n"
                   << "\tM=M+1" << endl;
        }
    }
    else if(vmOp == "call"){
        numCall++;
        asmOut << "\t@retAddrLabel" << numCall << "\n"
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
               << "\t@" << num << "\n"
               << "\tD=D-A\n"
               << "\t@ARG\n"
               << "\tM=D\n"

               << "\t@SP\n"
               << "\tD=M\n"
               << "\t@LCL\n"
               << "\tM=D\n"

               << "\t@" << vmMidOp << "\n"
               << "\t0;JMP\n"
               << "(retAddrLabel" << numCall << ")" << endl;
    }
}
