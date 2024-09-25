/*
1. Layout of console application and utilizing command line arguments (2 points):
Create the basic outline of a console application with main function, help function and
checking of command line arguments. Save the possible command line arguments in
variables or use a command line processor like popl.hpp or argparse.hpp. If the right
number of arguments was not given call the help function and exit the application. The two
arguments and the optional third should be a GO-obo input filename and a task-name like --
get-slims or --tab-slim with a slim identifier like plant or yeast for the --tab-slim parameter.
You find the Obofiles on Moodle. Check if the given filename points to a valid filename,
check if a valid argument was entered and check, if --tab-slim was provided, that as well an
slim id argument was given consisting out of only case letters like plant, yeast or drosophila
but not for instance dros0123.
*/

#include <string>
#include <regex>
#include "include/popl.hpp"

static const char HELP[] =
R"(
    PEX Exam 2024 1st try, part 1
    Obo-Parser - extract information from GO-Obo files.
    ---
    Filename: 2024examfirst1.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-09-20
)";

static const char PARA[] = 
"\033[1;36mo\033[0m Parameters:\n"
"    OBOFILE                    - one (or more) uncompressed Uniprot data file(s)\n";

const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

int main(int argc, char **argv){
    popl::OptionParser op("\n\033[1;36mo\033[0m Usage: appname [--help, --get-slims, --tab-slim SLIMNAME] OBOFILE \n\033[1;36mo\033[0m Options");
    auto help = op.add<popl::Switch>("h", "help", "- display this help page");
    auto slims = op.add<popl::Switch>("g", "get-slims", "- get all slim names");
    auto tabslim = op.add<popl::Value<std::string>>("t", "tab-slim", "- get a GO-id's, -names and namespaces for given slim", "SLIMNAME");
    

    op.parse(argc, argv);

    // wrong argument number check
    if (argc < 2 ) {
        //std::cerr << RED << " Error: No arguments are given!" << std::endl;
        std::cout << "\033[1;36mo\033[0m Usage: appname [--help, --get-slims, --tab-slim SLIMNAME] OBOFILE" << std::endl;
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
        std::cout << PARA << std::endl;
        return 1;
    }

    // File given?
    if (op.non_option_args().empty()) {
        std::cerr << RED << " Error: No file. Please enter the file." << std::endl;
        std::cout << op << std::endl;
        return 1;
    }

    // get filename
    std::string filename = op.non_option_args().back();

    // does file exist?
    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << "Error: The file '" << filename << "' does not exist!" << std::endl;
        return 1;
    }

    // is the file compressed?
    if (std::regex_match(filename, std::regex(".*\\.gz$"))) {
        std::cerr << "Error: The file '" << filename << "' must be uncompressed before usage." << std::endl;
        return 1;
    }

    if (slims -> is_set()){
        std::cout << YELLOW << " Executing get-slims function " << std::endl;
        std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
        return 1;
    }

    if(tabslim -> is_set()){
        std::string slimname = tabslim -> value();
        std::cout << YELLOW << " Executing tab-slim function with slimname: " << tabslim->value() << std::endl;
        std::regex valid_name ("^[a-z]+$");

        if (!std::regex_match(slimname, valid_name)) {
            std::cerr << RED << " Error: Invalid SLIMNAME." << std::endl;
            std::cerr << RED << " Slim name should consist only of lowercase letter!" << std::endl;
            return 1;
        }

        std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
        return 1;
    }

}