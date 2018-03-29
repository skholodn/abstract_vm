//
// Created by Serhii Kholodniuk on 11/17/17.
//

#ifndef ABSTRACT_VM_INT16_H
#define ABSTRACT_VM_INT16_H

#include "Parse.h"
#include "OperandFactory.h"

class Int16 : public IOperand {
    Int16();
    Int16(Int16 const &);
    Int16 & operator=(Int16 &);

    int16_t  _value;
    std::string _str;

public:
    static int   precision;
    static long   nMax;
    static long   nMin;

    Int16(int16_t);
    ~Int16();
    int getPrecision( void ) const; // Presigion of the type of the instance
    eOperandType getType( void ) const; // Type of instance
    // ******* For operations between operands
    IOperand const * operator+( IOperand const & rhs ) const; // Sum
    IOperand const * operator-( IOperand const & rhs ) const; // Division
    IOperand const * operator*( IOperand const & rhs ) const; // Multiplication
    IOperand const * operator/( IOperand const & rhs ) const; // Division
    IOperand const * operator%( IOperand const & rhs ) const; // Modulo
    //****************************************
    std::string const & toString( void ) const; // string representation of the instance

    static int checkValue(std::string const &, int);
    static int checkValueVM(std::string const & str);

    class Int16Underflow : public std::exception {
    public:
        const char* whatMy(std::string const &, int) throw ();
        const char* whatMy(std::string const &) throw ();
    };

    class Int16Overflow : public std::exception {
    public:
        const char* whatMy(std::string const &, int) throw ();
        const char* whatMy(std::string const &) throw ();
    };

    class Int16ZeroDivision : public std::exception {
    public:
        const char* what() const throw ();
    };

    class Int16OutOfRange : public std::exception {
    public:
        const char* whatMy(std::string const &, int) throw ();
        const char* whatMy(std::string const &) throw ();
    };


    void   Free() const;
    static IOperand * Create(std::string const &);
};



#endif //ABSTRACT_VM_INT16_H
