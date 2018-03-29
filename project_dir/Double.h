//
// Created by Serhii Kholodniuk on 11/17/17.
//

#ifndef ABSTRACT_VM_DOUBLE_H
#define ABSTRACT_VM_DOUBLE_H

#include "Parse.h"
#include "OperandFactory.h"

class Double : public IOperand {
    Double();

    Double(Double const &);

    Double &operator=(Double &);

    double _value;
    std::string _str;

public:
    static int precision;
    //static long   nMax;
    //static long   nMin;

    Double(double);

    ~Double();

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

//    class DoubleUnderflow : public std::exception {
//    public:
//        static const char* what(std::string const &, int) const throw ();
//        static const char* what(std::string const &) const throw ();
//    };
//
//    class DoubleOverflow : public std::exception {
//    public:
//        static const char* what(std::string const &, int) const throw ();
//        static const char* what(std::string const &) const throw ();
//    };

    class DoubleOutOfRange : public std::exception {
    public:
        const char *whatMy(std::string const &, int) throw();
        const char *whatMy(std::string const &) throw();
    };

    class DoubleZeroDivision : public std::exception {
    public:
        const char *what() const throw();
    };

    void Free() const;

    static IOperand *Create(std::string const &);
};

#endif //ABSTRACT_VM_DOUBLE_H
