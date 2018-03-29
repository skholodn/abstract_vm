//
// Created by Serhii Kholodniuk on 17.11.2017.
//

#ifndef ABSTRACT_VM_OPERANDFACTORY_H
#define ABSTRACT_VM_OPERANDFACTORY_H

#include "Int8.h"
#include "Int16.h"
#include "Int32.h"
#include "Float.h"
#include "Double.h"

class OperandFactory;

typedef IOperand * (*create)(std::string const &);
typedef int (*check)(std::string const &);

class OperandFactory {
    OperandFactory(const OperandFactory &);
    OperandFactory &operator=(const OperandFactory & );
    // array of pointers to functions of Operands creation
    create _arr[5];
    check   _arrCheck[5];


public:
    OperandFactory();
    ~OperandFactory();
    IOperand * createOperand(eOperandType type, std::string const & value );
    int     checkAllValuesVM(std::string const & s, eOperandType type);
};


#endif //ABSTRACT_VM_OPERANDFACTORY_H

/*
 *  MAKE CHAR EXCEPTION FOR PRINT
 */