//
// Created by Serhii Kholodniuk on 11/15/17.
//

#include "Parse.h"

std::vector<std::string> Parse::_errors;
std::vector<std::string> Parse::_command;
int                      Parse::_line = 0;

Parse::Parse(Parse & src){
    if (this != &src)
        *this = src;
}

Parse & Parse::operator=(Parse & src){
    if (this != &src)
        *this = src;
    return *this;
}

Parse::Parse(){}
Parse::~Parse(){}

void Parse::putErrors(std::string str){
    _errors.push_back(str);
}

void Parse::putCommand(std::string str) {
    _command.push_back(str);
}

void   Parse::skipSpaceTab(std::string & str){
    int i = 0;
    for (; str[i] == ' ' || str[i] == '\t'; ) {
        str = str.c_str() + 1;
    }
}

int     Parse::isEmptyLine(std::string str){
    Parse::skipSpaceTab(str);
    if (!str[0])
        return 1;
    else
        return 0;
}

int     Parse::isComment(std::string str){
    Parse::skipSpaceTab(str);
    if (str[0] == ';' && str[1] != ';')
        return 1;
    else
        return 0;
}

int     Parse::IsEndReading(std::string str){
    Parse::skipSpaceTab(str);
    if (str[0] == ';' && str[1] == ';')
        return 1;
    else
        return 0;
}

int     Parse::findDelimeter(std::string const & str, int i){
    if (str[i] && (str[i] == '\t' || str[i] == ' '))
        return 1;
    else
        return 0;
}

int     Parse::findNLDelimeter(std::string const & str, int i){
    std::string s = str;
    s = s.c_str() + i;
    Parse::skipSpaceTab(s);
    if (!s[0])
        return 1;
    else
        return 0;
}

int     Parse::isCommand(std::string & str){
    Parse::skipSpaceTab(str);
    if (!strncmp(str.c_str(), "push", 4) && findDelimeter(str, 4))
        return 4;
    else if (!strncmp(str.c_str(), "assert", 6) && findDelimeter(str, 6))
        return 6;
    else if (!strncmp(str.c_str(), "pop", 3) && findNLDelimeter( str, 3))
        return 1;
    else if (!strncmp(str.c_str(), "dump", 4) && findNLDelimeter(str, 4))
        return 1;
    else if (!strncmp(str.c_str(), "add", 3) && findNLDelimeter(str, 3))
        return 1;
    else if (!strncmp(str.c_str(), "sub", 3) && findNLDelimeter(str, 3))
        return 1;
    else if (!strncmp(str.c_str(), "mul", 3) && findNLDelimeter(str, 3))
        return 1;
    else if (!strncmp(str.c_str(), "div", 3) && findNLDelimeter(str, 3))
        return 1;
    else if (!strncmp(str.c_str(), "mod", 3) && findNLDelimeter(str, 3))
        return 1;
    else if (!strncmp(str.c_str(), "print", 5) && findNLDelimeter(str, 5))
        return 1;
    else if (!strncmp(str.c_str(), "exit", 4) && findNLDelimeter(str, 4))
        return 1;
    return 0;
}

int     Parse::validN(std::string str){
    Parse::skipSpaceTab(str);
    if (str[0] == '-' && isdigit(str[1])) {
        str = str.c_str() + 1;
        for (; isdigit(str[0]); str = str.c_str() + 1){}
    }
    else if (isdigit(str[0]))
        for (; isdigit(str[0]); str = str.c_str() + 1){}
    else
        return 0;
    Parse::skipSpaceTab(str);
    if (str[0] != ')' && !findNLDelimeter(str, 1))
        return 0;
    return 1;
}

int     Parse::validZ(std::string str) {
    Parse::skipSpaceTab(str);
    if (str[0] == '-' && isdigit(str[1])) {
        str = str.c_str() + 1;
        for (; isdigit(str[0]); str = str.c_str() + 1){}
        if(str[0] != '.')
            return 0;
        str = str.c_str() + 1;
        for (; isdigit(str[0]); str = str.c_str() + 1){}
    }
    else if (isdigit(str[0])){
        for (; isdigit(str[0]); str = str.c_str() + 1){}
        if (str[0] != '.')
            return 0;
        str = str.c_str() + 1;
        for (; isdigit(str[0]); str = str.c_str() + 1){}}
    else
        return 0;
    Parse::skipSpaceTab(str);
    if (str[0] != ')' && !findNLDelimeter(str, 1))
        return 0;
    return 1;
}

int     Parse::checkOperands(std::string str, int command)
{
    str = str.c_str() + command;
    Parse::skipSpaceTab(str);
    if (!strncmp(str.c_str(), "int8(", 5) && validN(str.c_str() + 5)){
        if (Int8::checkValue(str.c_str() + 5, _line))
            return 1; }
    else if (!strncmp(str.c_str(), "int16(", 6) && validN(str.c_str() + 6)){
        if (Int16::checkValue(str.c_str() + 6, _line))
            return 1; }
    else if (!strncmp(str.c_str(), "int32(", 6) && validN(str.c_str() + 6)){
        if (Int32::checkValue(str.c_str() + 6, _line))
            return 1; }
    else if (!strncmp(str.c_str(), "float(", 6) && validZ(str.c_str() + 6)){
        if (Float::checkValue(str.c_str() + 6, _line))
            return 1; }
    else if (!strncmp(str.c_str(), "double(", 7) && validZ(str.c_str() + 7)){
        if (Double::checkValue(str.c_str() + 7, _line))
            return 1; }
    else {
        Parse::ValueSetError error;
        putErrors(error.whatMy(str));
    }
    return 0;
}

void Parse::read_file(std::string & str){
    std::ifstream ifs(str);
    if (!ifs){
        std::cout
                << std::overflow_error("No such file: ").what() << str << std::overflow_error(".\nUsage: [./avm - reads commands from standart input | ./avm <filename> reads commands from file").what()
                << std::endl;
        std::exit(1);
    }
    std::string buf;
    while (std::getline(ifs, buf))
    {
        int ifCommand = 0;
        _line += 1;
        if ((ifCommand = isCommand(buf))){
            if (ifCommand == 1 || checkOperands(buf, ifCommand))
                putCommand(buf);
        }
        else if (isEmptyLine(buf) || isComment(buf) || IsEndReading(buf))
            continue;
        else {
            Parse::InstructionUnknown error;
            putErrors(error.whatMy(buf));
        }
    }
    if (!_errors.empty())
       print_errors();
    else {
        AbstractVM avm;
       avm.executeVM(_command);
    }
}
void Parse::read_cin(){
    std::string buf;
    while (std::getline(std::cin, buf))
    {
        int ifCommand = 0;
        _line += 1;
        if ((ifCommand = isCommand(buf))){
            if (ifCommand == 1 || checkOperands(buf, ifCommand))
                putCommand(buf);
        }
        else if (isEmptyLine(buf) || isComment(buf))
            continue;
        else if (IsEndReading(buf))
            break;
        else {
            Parse::InstructionUnknown error;
            putErrors(error.whatMy(buf));
        }
    }
    if (!_errors.empty())
        print_errors();
    else{
        AbstractVM avm;
        avm.executeVM(_command);
    }
}

void Parse::print_errors(){
    for (unsigned long i = 0; i < _errors.size(); i++)
        std::cout << _errors[i] << std::endl;
}

const char* Parse::InstructionUnknown::whatMy(std::string & command) throw (){
    std::string s;
    std::ostringstream oss;

    oss << "Line " << _line << " : Error : " << command << " is not appropriate command";
    s = oss.str();
    return (s.c_str());
}

const char* Parse::ValueSetError::whatMy(std::string & value) throw () {
    std::string s;
    std::ostringstream oss;

    oss << "Line " << _line << " : Error : " << value << " is not appropriate value";
    s = oss.str();
    return (s.c_str());
}