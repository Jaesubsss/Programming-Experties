/*
1. Layout application, command line arguments (2 points)
The Gene Ontology is a curated vocabulary to annotate genes and their products. It
undergoes constant evaluation and fixing problematic terms. These entries get the line
is_obsolete: true and in many cases alternative GO ids are suggested using a consider line.
Create the basic outline of a console application with main function, help function and
checking of command line arguments. Save the possible command line arguments in
variables or use a command line processor like argparse. If the right number of arguments
was not given call the help function and exit the application. The arguments should be: an
option name like '--get-table', ‘--get-table-ec,’ ‘--get-table-metacyc’, or '--new-ids' and one or
two goobo input filenames. Check if the given filename(s) points to a valid filename, check if
the given command name is a valid one and that if the --new-ids argument is given that
there are two filenames given. The help message should explain the application use clearly.
*/

#include <string>
#include <regex>
#include "include/popl.hpp"

static const char HELP[] =
R"(
    PEX Exam 2023, part 1
    Filename: 2023exam1.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-09-19
)";

const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

int main(int argc, char **argv){
    popl::OptionParser op("\n\033[1;36mo\033[0m Usage: appname [-helpl--get-tablel--get-table-ecl--get-table-metacycl--new-ids] ?obofile? ?obofile? \n\033[1;36mo\033[0m Options");
    auto help = op.add<popl::Switch>("h", "help", "- display this help page");
    auto table = op.add<popl::Switch>("t", "get-table", "- get table");
    auto table_ec = op.add<popl::Switch>("e", "get-table-ec", "- get table ec");
    auto table_metacyc = op.add<popl::Switch>("m", "get-table-metacyc", "- get table metacyc");
    auto new_ids = op.add<popl::Switch>("n", "new-ids", "- new ids");

    op.parse(argc, argv);

    // wrong argument number check
    if (argc < 2 ) {
        std::cerr << RED << " Error: No arguments are given!" << std::endl;
        std::cout << HELP << std::endl;
        std::cout << op << std::endl;
        return 1;
    }

    // wrong option check
    for (const auto& unknown_option: op.unknown_options()) {
        std::cout << RED <<" Error: unknown option '" << unknown_option << "'!\n";
        std::cout << RED <<" Use --help to show valid options!\n" ;
        return 1;
    }

    // help?
    if (help -> is_set()){
        std::cout << HELP;
        std::cout << op << std::endl;
        return 1;
    }


    // new_ids ------

    if (new_ids -> is_set()) {
        // 2 filenames given?
        std::vector<std::string> filenames = op.non_option_args(); 

        if (filenames.size() != 2){
            std::cerr << RED << " Error: Invalid Argument! Input must be 2 files." << std::endl;
            std::cout << op << std::endl;
            return 1;
        }

        for (const auto& filename : filenames) {

            // Check if the file exists
            std::ifstream file(filename);
            if (!file.good()) {
                std::cerr << RED << " Error: The file '" << filename << "' does not exist." << std::endl;
                continue;  // 다음 파일로 넘어가기
            }

            if (!std::regex_match(filename, std::regex(".*obo.*"))) {
                std::cerr << RED << " Error: The file must be goobo file." << std::endl;
                return 1;
            }
        }

        std::cout << YELLOW << " Executing new-ids function  " << std::endl;
        std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;

        return 0;
    }
    // ---------------

    // File given?
    if (op.non_option_args().empty()) {
        std::cerr << RED << " Error: No file. Please enter the file." << std::endl;
        std::cout << op << std::endl;
        return 1;
    }

    // get filename
    std::string filename = op.non_option_args().back();

    // Check if file exists
    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << RED << " Error: The file " << filename << " does not exist." << std::endl;
        return 1;
    }

    if (!std::regex_match(filename, std::regex(".*obo.*"))) {
        std::cerr << RED << " Error: The file must be goobo file." << std::endl;
        return 1;
    }

    if (table -> is_set()){
            std::cout << YELLOW << " Executing get-table function with file: " << filename << std::endl;
            std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
            return 1;
    }

    if (table_ec -> is_set()){
            std::cout << YELLOW << " Executing get-table-ec function with file: " << filename << std::endl;
            std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
            return 1;
    }

    if (table_metacyc -> is_set()){
            std::cout << YELLOW << " Executing get-table-metacyc function with file: " << filename << std::endl;
            std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
            return 1;
    }

}