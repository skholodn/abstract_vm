//
// Created by Serhii Kholodniuk on 11/17/17.
//

#include "Double.h"

int   Double::precision = 4;
//long  Double::nMax = -2147483648;
//long   Double::nMin = 2147483647;

//Double::Double() {}
//Double::Double(Double const & src) { *this = src;}
//Double & Double::operator=(Double & src) {
//    if (this != &src)
//        *this = src;
//    return *this;
//}

Double::Double(double n) { _value = n; _str = std::to_string(n); }
Double::~Double() { }

int Double::getPrecision( void ) const {
    return precision;
}

eOperandType Double::getType( void ) const {
    return DOUBLE;
}

// ******* For operations between operands

IOperand const * Double::operator+( IOperand const & rhs ) const {
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    long double result = value1 + value2;
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, DOUBLE);
    return of.createOperand(DOUBLE, s);
}

IOperand const * Double::operator-( IOperand const & rhs ) const {
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    long double result = value1 - value2;
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, DOUBLE);
    return of.createOperand(DOUBLE, s);
}

IOperand const * Double::operator*( IOperand const & rhs ) const {
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    long double result = value1 * value2;
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, DOUBLE);
    return of.createOperand(DOUBLE, s);
}

IOperand const * Double::operator/( IOperand const & rhs ) const {
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    if (value2 == 0.0) {
        Double::DoubleZeroDivision error;
        std::cout << error.what() << std::endl;
        exit(1);
    }
    long double result = value1 / value2;
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, DOUBLE);
    return of.createOperand(DOUBLE, s);
}

IOperand const * Double::operator%( IOperand const & rhs ) const {
    std::string s;
    std::ostringstream oss;

    double value2 = atof(rhs.toString().c_str());
    double value1 = _value;
    if (value2 == 0.0) {
        Double::DoubleZeroDivision error;
        std::cout << error.what() << std::endl;
        exit(1);
    }
    long double result = fmod(value1, value2);
    oss << result;
    s = oss.str();
    OperandFactory of;
    of.checkAllValuesVM(s, DOUBLE);
    return of.createOperand(DOUBLE, s);
}

//****************************************

std::string const & Double::toString( void ) const {
    return (_str);
}

int Double::checkValue(std::string const & str, int line) {
    try {
        std::stod(str);
    }
    catch (std::out_of_range & e)
    {
        Double::DoubleOutOfRange error;
        Parse::putErrors(error.whatMy(str, line));
        return 0;
    }
    return 1;
}

int Double::checkValueVM(std::string const & str) {
    try {
        std::stod(str);
    }
    catch (std::out_of_range & e)
    {
        Double::DoubleOutOfRange error;
        std::cout << error.whatMy(str) << std::endl;
        exit(1);
    }
    return 1;
}

//const char* Double::DoubleUnderflow::what(std::string const & str, int line) const throw () {
//    std::string s;
//    std::ostringstream oss;
//
//    oss << "Line " << line << " : Error : " << str << " is less than -_______. Not fit double range.";
//    s = oss.str();
//    return (s.c_str());
//}
//
//const char* Double::DoubleUnderflow::what(std::string const & str) const throw () {
//    std::string s;
//    std::ostringstream oss;
//
//    oss << "Error : " << str << " result of operation is less than -__________. Not fit double range.";
//    s = oss.str();
//    return (s.c_str());
//}
//
//const char* Double::DoubleOverflow::what(std::string const &str, int line) const throw () {
//    std::string s;
//    std::ostringstream oss;
//
//    oss << "Line " << line << " : Error : " << str << " is more than _________. Not fit double range.";
//    s = oss.str();
//    return (s.c_str());
//}
//
//const char* Double::DoubleOverflow::what(std::string const &str) const throw () {
//    std::string s;
//    std::ostringstream oss;
//
//    oss << "Error : " << str << " result of operation is more than _________. Not fit double range.";
//    s = oss.str();
//    return (s.c_str());
//}

const char* Double::DoubleOutOfRange::whatMy(std::string const &str, int line) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << line << " : Error : " << str << ". The value doesn't fit double range.";
    s = oss.str();
    return (s.c_str());
}

const char* Double::DoubleOutOfRange::whatMy(std::string const &str) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : " << str << ". The value doesn't fit double range.";
    s = oss.str();
    return (s.c_str());
}

const char* Double::DoubleZeroDivision::what() const throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Error : Zero division error!";
    s = oss.str();
    return (s.c_str());
}

IOperand * Double::Create(std::string const & str) {
    double value = stod(str);
    return new Double(value);
}

void    Double::Free() const { delete this; }