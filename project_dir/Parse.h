//
// Created by Serhii Kholodniuk on 11/15/17.
//

#ifndef ABSTRACT_VM_PARSE_H
#define ABSTRACT_VM_PARSE_H

#include "IOperand.h"
#include "Int8.h"
#include "Int16.h"
#include "Int32.h"
#include "Float.h"
#include "Double.h"
#include <vector>
#include <stack>
#include "AbstractVM.h"

class Int8;
class Int16;
class Int32;
class Float;
class Double;

class Parse {
    Parse(Parse & src);
    Parse & operator=(Parse & src);
    static std::vector<std::string> _errors;
    static std::vector<std::string> _command;
    //std::stack<IOperand *>   _stack;
    static int               _line;
public:
    Parse();
    ~Parse();

    static void putErrors(std::string);
    static void putCommand(std::string);
    void read_file(std::string & str);
    void read_cin();
    static void   skipSpaceTab(std::string & str);
    int     isEmptyLine(std::string str);
    int     isComment(std::string str);
    int     IsEndReading(std::string str);
    int     isCommand(std::string & str);
    int     findDelimeter(std::string const & str, int i);
    int     findNLDelimeter(std::string const & str, int i);
    int     checkOperands(std::string str, int command);
    int     validN(std::string str);
    int     validZ(std::string str);
    static void print_errors();

    class InstructionUnknown : std::exception {
    public:
       const char* whatMy(std::string &) throw ();
    };

    class ValueSetError : std::exception {
    public:
       const char* whatMy(std::string &) throw ();
    };
};


#endif //ABSTRACT_VM_PARSE_H
