//
// Created by Serhii Kholodniuk on 11/17/17.
//

#include "Int32.h"

int   Int32::precision = 2;
long   Int32::nMin = -2147483648;
long   Int32::nMax = 2147483647;

//Int32::Int32() {}
//Int32::Int32(Int32 const & src) { *this = src;}
//Int32 & Int32::operator=(Int32 & src) {
//    if (this != &src)
//        *this = src;
//    return *this;
//}

Int32::Int32(int n) { _value = n; _str = std::to_string(n); }
Int32::~Int32() { }

int Int32::getPrecision( void ) const {
    return precision;
}

eOperandType Int32::getType( void ) const {
    return INT32;
}

// ******* For operations between operands

IOperand const * Int32::operator+( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        long result = value1 + value2;
        oss << result;
        s = oss.str();
    }
    else
    {
        double value2 = atof(rhs.toString().c_str());
        double value1 = _value;
        double result = value1 + value2;
        oss << result;
        s = oss.str();
    }
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

IOperand const * Int32::operator-( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        long result = value1 - value2;
        oss << result;
        s = oss.str();
    }
    else
    {
        double value2 = atof(rhs.toString().c_str());
        double value1 = _value;
        double result = value1 - value2;
        oss << result;
        s = oss.str();
    }
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

IOperand const * Int32::operator*( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        long result = value1 * value2;
        oss << result;
        s = oss.str();
    }
    else
    {
        double value2 = atof(rhs.toString().c_str());
        double value1 = _value;
        double result = value1 * value2;
        oss << result;
        s = oss.str();
    }
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

IOperand const * Int32::operator/( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        if (value2 == 0) {
            Int32::Int32ZeroDivision error;
            std::cout << error.what() << std::endl;
            exit(1);
        }
        long result = value1 / value2;
        oss << result;
        s = oss.str();
    }
    else
    {
        double value2 = atof(rhs.toString().c_str());
        double value1 = _value;
        if (value2 == 0.0) {
            Int32::Int32ZeroDivision error;
            std::cout << error.what() << std::endl;
            exit(1);
        }
        double result = value1 / value2;
        oss << result;
        s = oss.str();
    }
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

IOperand const * Int32::operator%( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        if (value2 == 0) {
            Int32::Int32ZeroDivision error;
            std::cout << error.what() << std::endl;
            exit(1);
        }
        long result = value1 % value2;
        oss << result;
        s = oss.str();
    }
    else
    {
        double value2 = atof(rhs.toString().c_str());
        double value1 = _value;
        if (value2 == 0.0) {
            Int32::Int32ZeroDivision error;
            std::cout << error.what() << std::endl;
            exit(1);
        }
        double result = fmod(value1, value2);
        oss << result;
        s = oss.str();
    }
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

//****************************************

std::string const & Int32::toString( void ) const {
    return (_str);
}

int Int32::checkValue(std::string const & str, int line) {
    try {
        long value = std::stol(str);

        if (value > Int32::nMax) {
            Int32::Int32Overflow error;
            Parse::putErrors(error.whatMy(str, line));
            return 0;
        } else if (value < Int32::nMin) {
            Int32::Int32Underflow error;
            Parse::putErrors(error.whatMy(str, line));
            return 0;
        }
    }
    catch (std::out_of_range & e)
    {
        Int32::Int32OutOfRange error;
        Parse::putErrors(error.whatMy(str, line));
        return 0;
    }
    return 1;
}

int Int32::checkValueVM(std::string const & str) {
    try {
        long value = std::stol(str);
        if (value > Int32::nMax) {
            Int32::Int32Overflow error;
            std::cout << error.whatMy(str) << std::endl;
            exit(1);
        } else if (value < Int32::nMin) {
            Int32::Int32Underflow error;
            std::cout << error.whatMy(str) << std::endl;
            exit(1);
        }
    }
    catch (std::out_of_range & e)
    {
        Int32::Int32OutOfRange error;
        std::cout << error.whatMy(str) << std::endl;
        exit(1);
    }
    return 1;
}

const char* Int32::Int32Underflow::whatMy(std::string const & str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << " is less than -2147483648. Not fit int32 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int32::Int32Underflow::whatMy(std::string const & str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << " result of operation is less than -2147483648. Not fit int32 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int32::Int32Overflow::whatMy(std::string const &str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << " is more than 2147483647. Not fit int32 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int32::Int32Overflow::whatMy(std::string const &str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << " result of operation is more than 2147483647. Not fit int32 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int32::Int32OutOfRange::whatMy(std::string const &str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << ". The value doesn't fit long range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int32::Int32OutOfRange::whatMy(std::string const &str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << ". The value doesn't fit long range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int32::Int32ZeroDivision::what() const throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : Zero division error!";
    s = oss.str();
    return (s.c_str());
}

IOperand * Int32::Create(std::string const & str) {
    int value = atoi(str.c_str());
    return new Int32(value);
}

void    Int32::Free() const { delete this; }
