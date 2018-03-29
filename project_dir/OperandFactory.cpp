//
// Created by Serhii Kholodniuk on 17.11.2017.
//

#include "OperandFactory.h"

//OperandFactory::OperandFactory(const OperandFactory &) {};
//OperandFactory & OperandFactory::operator=(const OperandFactory & ) { return *this; }


OperandFactory::OperandFactory() {
    _arr[INT8] = &Int8::Create;
    _arr[INT16] = &Int16::Create;
    _arr[INT32] = &Int32::Create;
    _arr[FLOAT] = &Float::Create;
    _arr[DOUBLE] = &Double::Create;

    _arrCheck[INT8] = &Int8::checkValueVM;
    _arrCheck[INT16] = &Int16::checkValueVM;
    _arrCheck[INT32] = &Int32::checkValueVM;
    _arrCheck[FLOAT] = &Float::checkValueVM;
    _arrCheck[DOUBLE] = &Double::checkValueVM;
}

OperandFactory::~OperandFactory() {

}

IOperand * OperandFactory::createOperand(eOperandType type, std::string const & value ) {
    return _arr[type](value);
}

int     OperandFactory::checkAllValuesVM(std::string const & s, eOperandType type) {
    return _arrCheck[type](s);
}