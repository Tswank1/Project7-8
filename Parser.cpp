#include "Parser.hpp"

VMtoAsm vmAsm;

void Parser::parse(string vmInput){
    vector<string> vmCommands;
    string singleVmCommand, tempVmCommand;
    
    singleVmCommand = vmInput;
    int comment = singleVmCommand.find("//");
    int prevChar;
    if(comment > 0){
        prevChar = comment - 1;
        if(singleVmCommand.at(prevChar) == ' '){
            singleVmCommand = singleVmCommand.substr(0,prevChar);
        }
    }
    if(comment != -1){
        singleVmCommand = singleVmCommand.substr(0,comment);
    }
    
    int space = 0;  
    while(singleVmCommand.find(' ') != -1){
        space = singleVmCommand.find(' ');
        if(singleVmCommand.find("  ") != -1){
            singleVmCommand.erase(singleVmCommand.find("  "));
        }
        tempVmCommand = singleVmCommand.substr(0, space);
        vmCommands.push_back(tempVmCommand);
        singleVmCommand.erase(singleVmCommand.begin(), singleVmCommand.begin()+space+1);
    }

    if(singleVmCommand.find(' ') == -1){
        vmCommands.push_back(singleVmCommand);
    }
    
    if(vmCommands.size() == 1){
        if(vmCommands[0] == "add"){
            vmAsm.WriteAsm("add");
        }
        else if(vmCommands[0] == "sub"){
            vmAsm.WriteAsm("sub");
        }
        else if(vmCommands[0] == "neg"){
            vmAsm.WriteAsm("neg");
        }
        else if(vmCommands[0] == "eq"){
            vmAsm.WriteAsm("eq");
        }
        else if(vmCommands[0] == "gt"){
            vmAsm.WriteAsm("gt");
        }
        else if(vmCommands[0] == "lt"){
            vmAsm.WriteAsm("lt");
        }
        else if(vmCommands[0] == "and"){
            vmAsm.WriteAsm("and");
        }
        else if(vmCommands[0] == "or"){
            vmAsm.WriteAsm("or");
        }
        else if(vmCommands[0] == "not"){
            vmAsm.WriteAsm("not");
        }
        else if(vmCommands[0] == "return"){
            vmAsm.WriteAsm("return");
        }
    }
    else if(vmCommands.size()  ==  2){
        if(vmCommands[0] == "label"){
            vmAsm.WriteAsm2("label",vmCommands[1]);
        }
        else if(vmCommands[0] == "goto"){
            vmAsm.WriteAsm2("goto", vmCommands[1]);
        }
        else if(vmCommands[0] == "if-goto"){
            vmAsm.WriteAsm2("if-goto", vmCommands[1]);
        }
    }
    else if(vmCommands.size()  ==  3){
        int val = stoi(vmCommands[2]);
        if(vmCommands[0] == "push"){
            vmAsm.WriteAsm3("push", vmCommands[1], val);
        }
        else if(vmCommands[0] == "pop"){
            vmAsm.WriteAsm3("pop", vmCommands[1], val);
        }
        else if(vmCommands[0] == "function"){
            vmAsm.WriteAsm3("function", vmCommands[1], val);
        }
        else if(vmCommands[0] == "call"){
            vmAsm.WriteAsm3("call", vmCommands[1], val);
        }
    }
}