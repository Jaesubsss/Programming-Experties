/*
2. Opening and searching in the GO-obo file (4 points):
Our program should work with any GO-obo file. Please don’t hardcode the filename in your
application, if you do, you get a minus point. Implement the two arguments; --get-slims
filename.obo on the command line, then the GO-obo file is parsed and the slim ids (they are
shown at the beginning of the obo file on subsetdef lines where slim names do not contain
underscores) should be displayed space separated on one line on the terminal. Your
function should return the data to the function caller, for instance as a vector, print the
result outside of the function, for instance in main.
*/

#include <string>
#include <regex>
#include <sstream>
#include "include/popl.hpp"

static const char HELP[] =
R"(
    PEX Exam 2024 1st try, part 2
    Obo-Parser - extract information from GO-Obo files.
    ---
    Filename: 2024examfirst2.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-09-20
)";

static const char PARA[] = 
"\033[1;36mo\033[0m Parameters:\n"
"    OBOFILE                    - one (or more) uncompressed Uniprot data file(s)\n";

const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

std::vector<std::string> get_slims(const std::string& filename){
    std::ifstream file(filename);
    std::string line;
    std::string slimname;
    std::vector<std::string> results;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return results;
    }

    while(std::getline(file, line)){
        if (line.empty()) continue;

        if (line.rfind("subsetdef: goslim_", 0) == 0) {
            // std::cout << line << std::endl;
            std::istringstream iss(line);   // parsing the line
            std::string token;              // first chunk, "subsetdef:"
            iss >> token;                   // we don't use it
            std::string chunk;              // second chunk, "goslim_(...)"
            iss >> chunk;
            slimname = chunk.substr(7);     // extract the slimname
            results.push_back(slimname); 
        }
        
        /*
        std::regex slim_regex ("^subsetdef: goslim_");
        std::smatch match;
        if (std::regex_search(line, match, slim_regex)){
            results.push_back(match[1]);
        }
        */
    }

    return results;

}

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

        auto slimnames = get_slims(filename);
        for (const auto& slimname : slimnames){
            std::cout << slimname << " ";
        }

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