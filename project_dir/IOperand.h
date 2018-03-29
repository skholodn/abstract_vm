//
// Created by Serhii Kholodniuk on 11/14/17.
//

#ifndef ABSTRACT_VM_IOPERAND_H
#define ABSTRACT_VM_IOPERAND_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <math.h>


typedef enum sOperandType
{
    INT8,
    INT16,
    INT32,
    FLOAT,
    DOUBLE,
}            eOperandType;

class IOperand {

public:
    virtual ~IOperand() {}
    virtual int getPrecision( void ) const = 0; // Presigion of the type of the instance
    virtual eOperandType getType( void ) const = 0; // Type of instance
    // ******* For operations between operands
    virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Division
    virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Multiplication
    virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Division
    virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
    //****************************************
    virtual std::string const & toString( void ) const = 0; // string representation of the instance

    virtual void Free() const = 0;
};




#endif //ABSTRACT_VM_IOPERAND_H
