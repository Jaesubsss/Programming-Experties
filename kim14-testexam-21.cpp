/*
1. Layout of console application and utilizing command line arguments (2 points):
Create the basic outline of a console application with main and help function which explains the
purpose of the application and the usage of command line arguments. Save the possible command
line arguments in up to three variables. If the required arguments are not given, call the help
function and exit the application. You can use just the argv array or an command line parser like
popl or argparse. The arguments should be a option like `--search` or `--summary`, a filename for a
FASTA sequence file and an optional sequence pattern for the `--search` option. Do a check if the
given filename exists and warn the user if it does not exists on the users file system. Check if the
options are either --help, --summary or –search. Provide an useful help message if the arguments
are not correctly given using the help function. The help message should contain, program name,
author name and an usage line like this as well as a short explanation of the arguments thereafter:
Detlef’s FastaParser1 search FASTA files
Author: Detlef Groth, University of Potsdam, 2024
Usage: FastaParser1 --search|--summary|--help ?PATTERN? file.fasta 
*/

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

#include "include/popl.hpp"


static const char HELP[] =
R"(
    PEX first test exam 2, part 1
    Filename: kim14-testexam-21.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-07-04
)";

const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

int main(int argc, char **argv){
    popl::OptionParser op("\n\033[1;36mo\033[0m Usage: appname [--search|--summary|--help] ?PATTERN? file.fasta\n\033[1;36mo\033[0m Options");
    auto search = op.add<popl::Value<std::string>>("s", "search", "--search [PATTERN] file.fasta");
    auto summary = op.add<popl::Switch>("m", "summary", "--summary file.fasta");
    auto help = op.add<popl::Switch>("h", "help", "help message");

    op.parse(argc, argv);

    // wrong argument number check
    if (argc < 2 || argc > 4) {
        std::cerr << RED << " Error: Incorrect number of arguments!" << std::endl;
        std::cout << HELP << std::endl;
        std::cout << op << std::endl;
        return 1;
    }

    // wrong option check
    for (const auto& unknown_option: op.unknown_options()) {
        std::cout << RED <<"  Error: unknown option '" << unknown_option << "'!\n";
        std::cout << RED <<" Use --help to show valid options!\n" ;
        return 1;
    }

    // help?
    if (help -> is_set()){
        std::cout << HELP;
        std::cout << op << std::endl;
        return 1;
    } 

    
    // -----------------------------------------------------------------------

    // File given?
    if (op.non_option_args().empty()) {
        std::cerr << RED << " Error: Invalid Argument! check your pattern or filename if it's right." << std::endl;
        std::cout << op << std::endl;
        return 1;
    }

    // get filename, if exist!
    std::string filename = op.non_option_args().back();

    if (!std::regex_match(filename, std::regex(".*\\.fasta$"))) {
        std::cerr << RED << " Error: The file must have a .fasta extension." << std::endl;
        return 1;
    }

    // Check if file exists
    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << RED << " Error: The file " << filename << " does not exist." << std::endl;
        return 1;
    }
    

    if (search -> is_set()){
        std::string pattern = search -> value();
        std::cout << YELLOW << " Executing search function with pattern: " << pattern << " and file: " << filename << std::endl;
        std::regex valid_pattern ("[RHKDESTNQCUGPAVILMFYW]+");

        if (!std::regex_match(pattern, valid_pattern)) {
            std::cerr << RED << " Error: The pattern must contain only valid amino acids." << std::endl;
            return 1;
        }
    }

    if (summary -> is_set()){
        std::cout << YELLOW << " Executing summary function with file: " << filename << std::endl;
    }

    return 0;
}