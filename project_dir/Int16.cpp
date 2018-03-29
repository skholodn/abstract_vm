//
// Created by Serhii Kholodniuk on 11/17/17.
//

#include "Int16.h"

int   Int16::precision = 1;
long   Int16::nMin = -32768;
long   Int16::nMax = 32767;

Int16::Int16(int16_t n) { _value = n;  _str = std::to_string(n); }
Int16::~Int16() { }

int Int16::getPrecision( void ) const {
    return precision;
}

eOperandType Int16::getType( void ) const {
    return INT16;
}

// ******* For operations between operands

IOperand const * Int16::operator+( IOperand const & rhs ) const {
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

IOperand const * Int16::operator-( IOperand const & rhs ) const {
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

IOperand const * Int16::operator*( IOperand const & rhs ) const {
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

IOperand const * Int16::operator/( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        if (value2 == 0) {
            Int16::Int16ZeroDivision error;
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
            Int16::Int16ZeroDivision error;
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

IOperand const * Int16::operator%( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    if (oType < FLOAT) {
        long value2 = atoi(rhs.toString().c_str());
        long value1 = _value;
        if (value2 == 0) {
            Int16::Int16ZeroDivision error;
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
            Int16::Int16ZeroDivision error;
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

std::string const & Int16::toString( void ) const {
    //std::string s;
//    std::ostringstream oss;
//
//    oss << _value;
//    str = oss.str();
//    str = s;
    //str = std::to_string(_value);
    return (_str);
}

int Int16::checkValue(std::string const & str, int line) {
    try {
        long value = std::stol(str);

        if (value > Int16::nMax) {
            Int16::Int16Overflow error;
            Parse::putErrors(error.whatMy(str, line));
            return 0;
        } else if (value < Int16::nMin) {
            Int16::Int16Underflow error;
            Parse::putErrors(error.whatMy(str, line));
            return 0;
        }
    }
    catch (std::out_of_range & e)
    {
        Int16::Int16OutOfRange error;
        Parse::putErrors(error.whatMy(str, line));
        return 0;
    }
    return 1;
}

int Int16::checkValueVM(std::string const & str) {
    try {
        long value = std::stol(str);
        if (value > Int16::nMax) {
            Int16::Int16Overflow error;
            std::cout << error.whatMy(str) << std::endl;
            exit(1);
        } else if (value < Int16::nMin) {
            Int16::Int16Underflow error;
            std::cout << error.whatMy(str) << std::endl;
            exit(1);
        }
    }
    catch (std::out_of_range & e)
    {
        Int16::Int16OutOfRange error;
        std::cout << error.whatMy(str) << std::endl;
        exit(1);
    }
    return 1;
}

const char* Int16::Int16Underflow::whatMy(std::string const & str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << " is less than -32768. Not fit int16 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int16::Int16Underflow::whatMy(std::string const & str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << " result of operation is less than -32768. Not fit int16 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int16::Int16Overflow::whatMy(std::string const &str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << " is more than 32767. Not fit int16 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int16::Int16Overflow::whatMy(std::string const &str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << " result of operation is more than 32767. Not fit int16 range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int16::Int16OutOfRange::whatMy(std::string const &str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << ". The value doesn't fit long range.";
    s = oss.str();
    return (s.c_str());
}

const char* Int16::Int16OutOfRange::whatMy(std::string const &str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << ". The value doesn't fit long range.";
    s = oss.str();
    return (s.c_str());
}


const char* Int16::Int16ZeroDivision::what() const throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : Zero division error!";
    s = oss.str();
    return (s.c_str());
}

IOperand * Int16::Create(std::string const & str) {
    auto value = static_cast<int16_t >(atoi(str.c_str()));
    return new Int16(value);
}

void    Int16::Free() const { delete this; }