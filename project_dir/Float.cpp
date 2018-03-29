//
// Created by Serhii Kholodniuk on 11/17/17.
//

#include "Float.h"

int   Float::precision = 3;
//long  Float::nMax = -2147483648;
//long   Float::nMin = 2147483647;

Float::Float(float z) { _value = z; _str = std::to_string(z); }
Float::~Float() { }

int Float::getPrecision( void ) const {
    return precision;
}

eOperandType Float::getType( void ) const {
    return FLOAT;
}

// ******* For operations between operands

IOperand const * Float::operator+( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    long double result = value1 + value2;
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

IOperand const * Float::operator-( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    long double result = value1 - value2;
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

IOperand const * Float::operator*( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    long double result = value1 * value2;
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

IOperand const * Float::operator/( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    if (value2 == 0.0) {
        Float::FloatZeroDivision error;
        std::cout << error.what() << std::endl;
        exit(1);
    }
    long double result = value1 / value2;
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

IOperand const * Float::operator%( IOperand const & rhs ) const {
    eOperandType oType = (getPrecision() < rhs.getPrecision()) ? rhs.getType() : getType();
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    if (value2 == 0.0) {
        Float::FloatZeroDivision error;
        std::cout << error.what() << std::endl;
        exit(1);
    }
    long double result = fmod(value1, value2);
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, oType);
    return of.createOperand(oType, s);
}

//****************************************

std::string const & Float::toString( void ) const {
    return (_str);
}

int Float::checkValue(std::string const & str, int line) {
    try {
        std::stof(str);
    }
    catch (std::out_of_range & e)
    {
        Float::FloatOutOfRange error;
        Parse::putErrors(error.whatMy(str, line));
        return 0;
    }
    return 1;
}

int Float::checkValueVM(std::string const & str) {
    try {
        std::stof(str);
    }
    catch (std::out_of_range & e)
    {
        Float::FloatOutOfRange error;
        std::cout << error.whatMy(str) << std::endl;
        exit(1);
    }
    return 1;
}

//const char* Float::FloatUnderflow::what(std::string const & str, int line) const throw () {
//    std::string s;
//    std::ostringstream oss;
//
//    oss << "Line " << line << " : Error : " << str << " is less than -_______. Not fit float range.";
//    s = oss.str();
//    return (s.c_str());
//}
//
//const char* Float::FloatUnderflow::what(std::string const & str) const throw () {
//    std::string s;
//    std::ostringstream oss;
//
//    oss << "Error : " << str << " result of operation is less than -__________. Not fit float range.";
//    s = oss.str();
//    return (s.c_str());
//}
//
//const char* Float::FloatOverflow::what(std::string const &str, int line) const throw () {
//    std::string s;
//    std::ostringstream oss;
//
//    oss << "Line " << line << " : Error : " << str << " is more than _________. Not fit float range.";
//    s = oss.str();
//    return (s.c_str());
//}
//
//const char* Float::FloatOverflow::what(std::string const &str) const throw () {
//    std::string s;
//    std::ostringstream oss;
//
//    oss << "Error : " << str << " result of operation is more than _________. Not fit float range.";
//    s = oss.str();
//    return (s.c_str());
//}

const char* Float::FloatOutOfRange::whatMy(std::string const &str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << ". The value doesn't fit float range.";
    s = oss.str();
    return (s.c_str());
}

const char* Float::FloatOutOfRange::whatMy(std::string const &str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << ". The value doesn't fit float range.";
    s = oss.str();
    return (s.c_str());
}

const char* Float::FloatZeroDivision::what() const throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : Zero division error!";
    s = oss.str();
    return (s.c_str());
}

IOperand * Float::Create(std::string const & str) {
    float value = stof(str);
    return new Float(value);
}

void    Float::Free() const { delete this; }