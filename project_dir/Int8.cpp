//
// Created by Serhii Kholodniuk on 11/17/17.
//

#include "Int8.h"

int   Int8::precision = 0;
long   Int8::nMin = -128;
long   Int8::nMax = 127;

Int8::Int8(int8_t n) { _value = n; _str = std::to_string(n); }
Int8::~Int8() { }

int Int8::getPrecision( void ) const {
    return precision;
}

eOperandType Int8::getType( void ) const {
    return INT8;
}

// ******* For operations between operands

IOperand const * Int8::operator+( IOperand const & rhs ) const {
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

IOperand const * Int8::operator-( IOperand const & rhs ) const {
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

IOperand const * Int8::operator*( IOperand const & rhs ) const {
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

IOperand const * Int8::operator/( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        if (value2 == 0) {
            Int8::Int8ZeroDivision error;
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
            Int8::Int8ZeroDivision error;
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

IOperand const * Int8::operator%( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        if (value2 == 0) {
            Int8::Int8ZeroDivision error;
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
            Int8::Int8ZeroDivision error;
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

std::string const & Int8::toString( void ) const {
    return (_str);
}

int Int8::checkValue(std::string const & str, int line) {
    try {
        long value = std::stol(str);

        if (value > Int8::nMax) {
            Int8::Int8Overflow error;
            Parse::putErrors(error.whatMy(str, line));
            return 0;
        } else if (value < Int8::nMin) {
            Int8::Int8Underflow error;
            Parse::putErrors(error.whatMy(str, line));
            return 0;
        }
    }
    catch (std::out_of_range & e)
    {
        Int8::Int8OutOfRange error;
        Parse::putErrors(error.whatMy(str, line));
        return 0;
    }
    return 1;
}

int Int8::checkValueVM(std::string const & str) {
    try {
        long value = std::stol(str);
        if (value > Int8::nMax) {
            Int8::Int8Overflow error;
            std::cout << error.whatMy(str) << std::endl;
            exit(1);
        } else if (value < Int8::nMin) {
            Int8::Int8Underflow error;
            std::cout << error.whatMy(str) << std::endl;
            exit(1);
        }
    }
    catch (std::out_of_range & e)
    {
        Int8::Int8OutOfRange error;
        std::cout << error.whatMy(str) << std::endl;
        exit(1);
    }
    return 1;
}

const char* Int8::Int8Underflow::whatMy(std::string const & str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << " is less than -128. Not fit int8 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int8::Int8Underflow::whatMy(std::string const & str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << " result of operation is less than -128. Not fit int8 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int8::Int8Overflow::whatMy(std::string const &str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << " is more than 127. Not fit int8 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int8::Int8Overflow::whatMy(std::string const &str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << " result of operation is more than 127. Not fit int8 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int8::Int8OutOfRange::whatMy(std::string const &str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << ". The value doesn't fit long range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int8::Int8OutOfRange::whatMy(std::string const &str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << ". The value doesn't fit long range.";
    s = oss.str();
    return (s.c_str());
}


const char* Int8::Int8ZeroDivision::what() const throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : Zero division error!";
    s = oss.str();
    return (s.c_str());
}

IOperand * Int8::Create(std::string const & str) {
    auto value = static_cast<int8_t >(atoi(str.c_str()));
    return new Int8(value);
}

void    Int8::Free() const { delete this; }