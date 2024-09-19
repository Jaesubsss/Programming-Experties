/*
1. Layout of console application and utilizing command line arguments (2 points):
Create the basic outline of a console application with main function, help function and usage of
command line arguments. The application should take one or more arguments where the first
argument is either --help, --go-count or --go-search which gets one argument and the last argument
should be one UniProt filename.
If no arguments are given show an single usage line, if explicitly the --help argument is given, call
the help function with more descriptions of the application names, the authorname and of the
options and arguments and thereafter exit the application. Check if the first argument is one of the
three double dash switches shown above. If not give a warning.
The arguments --go-count and --go-search gets a GO-id as an argument. A GO-id starts with the
prefix ‘GO:’ followed by 7 digits, check that the given id is valid. Check further if the last argument
is a valid filename for a Uniprot formatted data file ending either with the extension .dat. Do a
check if the given Uniprot filename exists and warn the user if the file do not exists or if it does not
have the right filename extension. The database files should be downloaded from the Moodle page:

 uniprot-corona-virus-data-2022-02.dat
 uniprot-microsporidian-data-2022-02.dat
*/

#include <string>
#include <regex>
#include "include/popl.hpp"

// compile with:
// g++ -std=c++11 -o .\build\testexam31.exe .\kim14-testexam-31.cpp
// .\build\testexam31.exe --help

static const char HELP[] =
R"(
    PEX first test exam 3, part 1
    Filename: kim14-testexam-31.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-09-19

    Extract information from Uniprot data files.
-----------------------------------------------
)";

static const char MAND[] = 
"\033[1;36mo\033[0m Mandatory arguments are:\n"
"    FILE - one (or more) uncompressed Uniprot data file(s)\n";

const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

int main(int argc, char **argv){
    popl::OptionParser op("\n\033[1;36mo\033[0m Usage: appname [--help|--go-search|--go-count] [FILE] ?[FILE] ...?\n\033[1;36mo\033[0m Options");
    auto help = op.add<popl::Switch>("h", "help", "- display this help page");
    auto search = op.add<popl::Value<std::string>>("s", "go-search", "- count how often a GO id is in the uniprot file");
    auto count = op.add<popl::Value<std::string>>("m", "go-count", "- search Uniprot IDs for the given annotation");

    op.parse(argc, argv);

    // wrong argument number check
    if (argc < 2 ) {
        std::cerr << RED << " Error: No arguments are given!" << std::endl;
        std::cout << HELP << std::endl;
        std::cout << op << std::endl;
        std::cout << MAND << std::endl;
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
        std::cout << MAND << std::endl;
        return 1;
    }

    // get list of filename
    std::vector<std::string> filenames = op.non_option_args(); 

    // File given?
    if (op.non_option_args().empty()) {
        std::cerr << RED << " Error: Invalid Argument! check your pattern or filename if it's right." << std::endl;
        std::cout << op << std::endl;
        return 1;
    }

    for (const auto& filename : filenames) {

        // Check if the file exists
        std::ifstream file(filename);
        if (!file.good()) {
            std::cerr << "Error: The file '" << filename << "' does not exist." << std::endl;
            continue;  // 다음 파일로 넘어가기
        }

        // Check if the file has a .dat extension
        if (!std::regex_match(filename, std::regex(".*\\.dat$"))) {
            std::cerr << "Error: The file '" << filename << "' must have a .dat extension." << std::endl;
            continue;  // 다음 파일로 넘어가기
        }

        // 유효한 파일 처리 (여기서 파일 내용을 처리하는 코드 추가 가능)

        if (search -> is_set()){
            std::string pattern = search -> value();
            std::cout << YELLOW << " Executing go-search function with GO-id: " << pattern << " and file: " << filename << std::endl;
            std::regex valid_pattern ("GO:\\d{7}");

            if (!std::regex_match(pattern, valid_pattern)) {
                std::cerr << RED << " Error: Invalid GO-id." << std::endl;
                std::cerr << RED << " A GO-id starts with the prefix 'GO:' followed by 7 digits" << std::endl;
                return 1;
            }

            std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
        }

        if (count -> is_set()){
            std::cout << YELLOW << " Executing go-count function with file: " << filename << std::endl;
            std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
        }

        std::cout << YELLOW << "Processing file: " << filename << std::endl;
    }

    return 0;

}