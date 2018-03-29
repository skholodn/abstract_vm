//
// Created by Serhii Kholodniuk on 11/17/17.
//

#ifndef ABSTRACT_VM_FLOAT_H
#define ABSTRACT_VM_FLOAT_H

#include "Parse.h"
#include "OperandFactory.h"

class Float : public IOperand {
    Float();
    Float(Float const &);
    Float &operator=(Float &);

    float _value;
    std::string _str;

public:
    static int precision;

    Float(float);

    ~Float();

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

//    class FloatUnderflow : public std::exception {
//    public:
//        static const char* what(std::string const &, int) const throw ();
//        static const char* what(std::string const &) const throw ();
//    };
//
//    class FloatOverflow : public std::exception {
//    public:
//        static const char* what(std::string const &, int) const throw ();
//        static const char* what(std::string const &) const throw ();
//    };

    class FloatOutOfRange : public std::exception {
    public:
        const char *whatMy(std::string const &, int) throw();
        const char *whatMy(std::string const &) throw();
    };

    class FloatZeroDivision : public std::exception {
    public:
        const char *what() const throw();
    };

    void Free() const;

    static IOperand *Create(std::string const &);
};

#endif //ABSTRACT_VM_FLOAT_H
