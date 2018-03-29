//
// Created by Serhii Kholodniuk on 11/15/17.
//

//#include "IOperand.h"
#include "Parse.h"

int     main(int ac, char **av)
{
    if (ac > 2) {
        std::cout
                << std::overflow_error("Too much arguments.\nUsage: [./avm - reads commands from standart input | ./avm <filename> reads commands from file").what()
                << std::endl;
        std::exit(1);
    }
    Parse parse;
    if (ac == 2) {
        std::string file(av[1]);
        parse.read_file(file);
    }
    else
        parse.read_cin();
    return 0;
}