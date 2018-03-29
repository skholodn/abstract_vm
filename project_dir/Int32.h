//
// Created by Serhii Kholodniuk on 11/17/17.
//

#ifndef ABSTRACT_VM_INT32_H
#define ABSTRACT_VM_INT32_H


#include "Parse.h"
#include "OperandFactory.h"

class Int32 : public IOperand {
    Int32();

    Int32(Int32 const &);

    Int32 &operator=(Int32 &);

    int _value;
    std::string _str;

public:
    static int precision;
    static long nMax;
    static long nMin;

    Int32(int);

    ~Int32();

    int getPrecision(void) const; // Presigion of the type of the instance
    eOperandType getType(void) const; // Type of instance
    // ******* For operations between operands
    IOperand const *operator+(IOperand const &rhs) const; // Sum
    IOperand const *operator-(IOperand const &rhs) const; // Division
    IOperand const *operator*(IOperand const &rhs) const; // Multiplication
    IOperand const *operator/(IOperand const &rhs) const; // Division
    IOperand const *operator%(IOperand const &rhs) const; // Modulo
    //****************************************
    std::string const &toString(void) const; // string representation of the instance

    static int checkValue(std::string const &, int);

    static int checkValueVM(std::string const &str);

    class Int32Underflow : public std::exception {
    public:
        const char *whatMy(std::string const &, int) throw();
        const char *whatMy(std::string const &) throw();
    };

    class Int32Overflow : public std::exception {
    public:
        const char *whatMy(std::string const &, int) throw();
        const char *whatMy(std::string const &) throw();
    };

    class Int32OutOfRange : public std::exception {
    public:
        const char *whatMy(std::string const &, int) throw();
        const char *whatMy(std::string const &) throw();
    };

    class Int32ZeroDivision : public std::exception {
    public:
        const char *what() const throw();
    };

    void Free() const;

    static IOperand *Create(std::string const &);
};

#endif //ABSTRACT_VM_INT32_H
