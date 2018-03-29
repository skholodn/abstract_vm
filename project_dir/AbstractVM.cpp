//
// Created by Serhii Kholodniuk on 17.11.2017.
//

#include "AbstractVM.h"


AbstractVM::AbstractVM(AbstractVM const & src) { *this = src; }

AbstractVM * AbstractVM::operator=(AbstractVM const & rhs) {
if (this != &rhs)
    this->_stack = rhs._stack;
    return this;
}

AbstractVM::AbstractVM() { }
AbstractVM::~AbstractVM() { }

void AbstractVM::executeVM(std::vector<std::string> & commands) {
    std::vector<std::string>::size_type sz = commands.size();

    if (!commands.size() || strncmp(commands[sz - 1].c_str(), "exit", 4)) {
        AVMNoExitAtEnd error;
        std::cout << error.what() << std::endl;
        exit(1);
    }
    for (unsigned long it = 0; it < sz; it++)
    {
        applyCommands(commands[it], it + 1);
    }
}

void    AbstractVM::applyCommands(std::string & str, unsigned long nLine)
{
    if (!strncmp(str.c_str(), "push", 4))
        applyPush(str = str.c_str() + 4);
    else if (!strncmp(str.c_str(), "assert", 6))
        applyAssert(str = str.c_str() + 6, nLine);
    else if (!strncmp(str.c_str(), "pop", 3))
        applyPop(nLine);
    else if (!strncmp(str.c_str(), "dump", 4))
        applyDump();
    else if (!strncmp(str.c_str(), "add", 3))
        applyAdd(nLine);
    else if (!strncmp(str.c_str(), "sub", 3))
        applySub(nLine);
    else if (!strncmp(str.c_str(), "mul", 3))
        applyMul(nLine);
    else if (!strncmp(str.c_str(), "div", 3))
        applyDiv(nLine);
    else if (!strncmp(str.c_str(), "mod", 3))
        applyMod(nLine);
    else if (!strncmp(str.c_str(), "print", 5))
        applyPrint(nLine);
    else if (!strncmp(str.c_str(), "exit", 4))
        return;
}

void    AbstractVM::applyPush(std::string & str) {
    Parse::skipSpaceTab(str);
    OperandFactory of;
    std::string tmp;
    if (!strncmp(str.c_str(), "int8(", 5)){
        tmp = str;
        tmp = str.c_str() + 5;
        _stack.push_back(of.createOperand(INT8, tmp));
    }
    else if (!strncmp(str.c_str(), "int16(", 6)){
        tmp = str;
        tmp = str.c_str() + 6;
        _stack.push_back(of.createOperand(INT16, tmp));
    }
    else if (!strncmp(str.c_str(), "int32(", 6)){
        tmp = str;
        tmp = str.c_str() + 6;
        _stack.push_back(of.createOperand(INT32, tmp));
    }
    else if (!strncmp(str.c_str(), "float(", 6)) {
        tmp = str;
        tmp = str.c_str() + 6;
        _stack.push_back(of.createOperand(FLOAT, tmp));
    }
    else if (!strncmp(str.c_str(), "double(", 7)) {
        tmp = str;
        tmp = str.c_str() + 7;
        _stack.push_back(of.createOperand(DOUBLE, tmp));
    }
}

void    AbstractVM::applyAssert(std::string & str, unsigned long nLine) {
    Parse::skipSpaceTab(str);
    if (_stack.empty()) {
        std::string s = "assert";
        AVMEmptyStack error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    IOperand * oPtr = nullptr;
    std::string tmp;
    OperandFactory of;
    if (!strncmp(str.c_str(), "int8(", 5)){
        tmp = str;
        tmp = str.c_str() + 5;
        oPtr = of.createOperand(INT8, tmp);
    }
    else if (!strncmp(str.c_str(), "int16(", 6)){
        tmp = str;
        tmp = str.c_str() + 6;
        oPtr = of.createOperand(INT16, tmp);
    }
    else if (!strncmp(str.c_str(), "int32(", 6)){
        tmp = str;
        tmp = str.c_str() + 6;
        oPtr = of.createOperand(INT32, tmp);
    }
    else if (!strncmp(str.c_str(), "float(", 6)) {
        tmp = str;
        tmp = str.c_str() + 6;
        oPtr = of.createOperand(FLOAT, tmp);
    }
    else if (!strncmp(str.c_str(), "double(", 7)) {
        tmp = str;
        tmp = str.c_str() + 7;
        oPtr = of.createOperand(DOUBLE, tmp);
    }
    auto ite = _stack.end();
    --ite;
    if (oPtr->getType() != (*ite)->getType() || strcmp(oPtr->toString().c_str(), (*ite)->toString().c_str())) {
        std::string s = "assert";
        AVMNotEqualOp error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
}

void    AbstractVM::applyPop(unsigned long nLine) {
    if (_stack.empty()) {
        std::string s = "pop";
        AVMEmptyStack error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    auto it = _stack.end();
    --it;
    delete (*it);
    _stack.pop_back();
}

void    AbstractVM::applyDump() {
    if (_stack.empty())
        return;
    auto ite = _stack.end();
    auto it = _stack.begin();
    --ite;
    for (; ite != it ; --ite){
        std::cout << (*ite)->toString() << std::endl;
    }
    std::cout << (*it)->toString() << std::endl;
}

void    AbstractVM::applyAdd(unsigned long nLine) {
    if (_stack.size() < 2) {
        std::string s = "add";
        AVMNotEnoughOp error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    auto ite = _stack.end();
    --ite;
    IOperand const & b = **ite;
    --ite;
    IOperand const & a = **ite;
    IOperand const * c = a + b;
    b.Free();
    _stack.pop_back();
    a.Free();
    _stack.pop_back();
    _stack.push_back(c);
}

void    AbstractVM::applySub(unsigned long nLine) {
    if (_stack.size() < 2) {
        std::string s = "sub";
        AVMNotEnoughOp error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    auto ite = _stack.end();
    --ite;
    IOperand const & b = **ite;
    --ite;
    IOperand const & a = **ite;
    IOperand const * c = a - b;
    b.Free();
    _stack.pop_back();
    a.Free();
    _stack.pop_back();
    _stack.push_back(c);
}

void    AbstractVM::applyMul(unsigned long nLine) {
    if (_stack.size() < 2) {
        std::string s = "mul";
        AVMNotEnoughOp error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    auto ite = _stack.end();
    --ite;
    IOperand const & b = **ite;
    --ite;
    IOperand const & a = **ite;
    IOperand const * c = a * b;
    b.Free();
    _stack.pop_back();
    a.Free();
    _stack.pop_back();
    _stack.push_back(c);
}

void    AbstractVM::applyDiv(unsigned long nLine) {
    if (_stack.size() < 2) {
        std::string s = "div";
        AVMNotEnoughOp error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    auto ite = _stack.end();
    --ite;
    IOperand const & b = **ite;
    --ite;
    IOperand const & a = **ite;
    IOperand const * c = a / b;
    b.Free();
    _stack.pop_back();
    a.Free();
    _stack.pop_back();
    _stack.push_back(c);
}

void    AbstractVM::applyMod(unsigned long nLine) {
    if (_stack.size() < 2) {
        std::string s = "mod";
        AVMNotEqualOp error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    auto ite = _stack.end();
    --ite;
    IOperand const & b = **ite;
    --ite;
    IOperand const & a = **ite;
    IOperand const * c = a % b;
    b.Free();
    _stack.pop_back();
    a.Free();
    _stack.pop_back();
    _stack.push_back(c);

}

void    AbstractVM::applyPrint(unsigned long nLine) {
    if (_stack.empty()) {
        std::string s = "print";
        AVMEmptyStack error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    auto ite = _stack.end();
    --ite;
    if (INT8 != (*ite)->getType()) {
        std::string s = "print";
        AVMNotEqualOp error;
        std::cout << error.whatMy(nLine, s) << std::endl;
        exit(1);
    }
    char c = static_cast<char>(std::atoi((*ite)->toString().c_str()));
    if (c > 31 && c < 127)
        std::cout << "'" << c << "'" << std::endl;
    else
        std::cout << "not printable" << std::endl;
}

const char* AbstractVM::AVMNoExitAtEnd::what() const throw () {
    return ("Error : No <exit> command at the end of command list");
}

const char* AbstractVM::AVMEmptyStack::whatMy(unsigned long nLine, std::string & command) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Command " << nLine << " : Error : You can't execute command " << command << ". The stack is empty.";
    s = oss.str();
    return (s.c_str());
}

const char* AbstractVM::AVMNotEqualOp::whatMy(unsigned long nLine, std::string & command) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Command " << nLine << " : Error : You can't execute command " << command << ". Operands are not equal.";
    s = oss.str();
    return (s.c_str());
}

const char* AbstractVM::AVMNotEnoughOp::whatMy(unsigned long nLine, std::string & command) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Command " << nLine << " : Error : You can't execute command " << command << ". The stack doesn't have enough operands.";
    s = oss.str();
    return (s.c_str());
}