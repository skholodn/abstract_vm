//
// Created by Serhii Kholodniuk on 17.11.2017.
//

#ifndef ABSTRACT_VM_ABSTRACTVM_H
#define ABSTRACT_VM_ABSTRACTVM_H

#include "MutantStack.hpp"
#include "Parse.h"
#include "OperandFactory.h"


class AbstractVM {
    AbstractVM(AbstractVM const &);
    AbstractVM * operator=(AbstractVM const &);
    MutantStack<IOperand const *>  _stack;

public:
    AbstractVM();
    ~AbstractVM();

    void executeVM(std::vector<std::string> &);
    void applyCommands(std::string &, unsigned long);
    void    applyPush(std::string &);
    void    applyAssert(std::string &, unsigned long);
    void    applyPop(unsigned long);
    void    applyDump();
    void    applyAdd(unsigned long);
    void    applySub(unsigned long);
    void    applyMul(unsigned long);
    void    applyDiv(unsigned long);
    void    applyMod(unsigned long);
    void    applyPrint(unsigned long);

    class AVMNoExitAtEnd : public std::exception {
    public:
        const char* what() const throw ();
    };

    class AVMEmptyStack : public std::exception {
    public:
        const char* whatMy(unsigned long, std::string &) throw ();
    };

    class AVMNotEqualOp : public std::exception {
    public:
        const char* whatMy(unsigned long, std::string &) throw ();
    };
    class AVMNotEnoughOp : public std::exception {
    public:
        const char* whatMy(unsigned long, std::string &) throw ();
    };
};


#endif //ABSTRACT_VM_ABSTRACTVM_H
