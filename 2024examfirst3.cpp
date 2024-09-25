/*
3. Advanced Terminal Application (4 points):

A (1 point): Extend your application as a C++ class and so that only the two functions
returning the slim-names (--get-slims called) and returning the slim-table (--tab-slim called),
task C) are public.

B (1 point): check as well that the given slim-name in case of calling the --tab-slim is a valid
one – create a method like getSlimTable which uses the function from task 2, do not open
the file again, use the return values from the task 2 function. Using a slim-name which is not
in the file like giving --tab-slim dummy should produce an error message.

C (2 points) Implement the --tab-slim SLIMNAME option so that it displays the following
lines on the terminal:
*/

#include <string>
#include <regex>
#include <sstream>
#include "include/popl.hpp"

static const char HELP[] =
R"(
    PEX Exam 2024 1st try, part 3
    Obo-Parser - extract information from GO-Obo files.
    ---
    Filename: 2024examfirst3.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-09-20
)";

static const char PARA[] = 
"\033[1;36mo\033[0m Parameters:\n"
"    OBOFILE                    - one (or more) uncompressed Uniprot data file(s)\n";


class Kim14{

public:
    Kim14() {}

std::vector<std::string> slim_names(const std::string& filename){
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

std::vector<std::tuple<std::string, std::string, std::string, std::string>> slim_table(const std::string& filename, const std::string& slimname){
    std::string line;
    std::string current_slimname;
    //std::vector<std::string> slimnames;
    std::string id;
    std::string namesp;
    std::string name;
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> results;
    std::vector<std::string> slimtable = slim_names(filename);


    if (std::find(slimtable.begin(), slimtable.end(), slimname) == slimtable.end()) {
        std::cerr << "'" << slimname << "' is not a valid slim-name, possible slim-names are for instance 'plant' or 'yeast' use the '--get-slims' argument to show all available slims!" << std::endl;
        return results; 
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return results;
    }

    bool found = false;
    while (std::getline(file, line) ) {
        if (line.empty()) continue;

        if (line.rfind("id:", 0) == 0) { // line starts with "ID"
            
            if (!id.empty()) {
                if (found) {
                    results.emplace_back(slimname, id, namesp, name);
                }
            }
            //slimnames.clear();
            id.clear();  
            found = false;
            id = line.substr(4);
        }

        if (line.rfind("name:",0) == 0) {
            name = line.substr(6);
        }

        if (line.rfind("namespace:",0) == 0) {
            namesp = line.substr(11);
        }

        if (line.rfind("subset: goslim_",0) == 0) {
            //slimnames.emplace_back(line.substr(11));
            current_slimname = line.substr(15);
            if (current_slimname == slimname) {
                found = true;
            }
            //Debugging...
            //std::cout << id <<"\t"<< current_slimname << "\t" << slimname << "\t" << found <<std::endl;
        }
    }

    if (!id.empty() && found) {
        results.emplace_back(slimname, id, namesp, name);
    }

    file.close();
    return results;

}
};

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

    Kim14 kim14;

    if (slims -> is_set()){
        std::cout << YELLOW << " Executing get-slims function " << std::endl;

        auto slimnames = kim14.slim_names(filename);
        std::cout << GREEN << " Slimnames found in the file '" << filename << "':" << std::endl;
        for (const auto& slimname : slimnames){
            std::cout << slimname << " ";
        }

        return 0;
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
        auto results = kim14.slim_table(filename, slimname);
        if (results.empty()){
            std::cout << RED << " No results found for slimname '" << slimname << "'." << std::endl;
        } else{
            std::cout << GREEN << " Results for slimname '" << slimname << "':" << std::endl;

            for (const auto& result : results){
            std::cout << std::get<0>(result) << "\t" // slimname
            << std::get<1>(result) << "\t"           // id
            << std::get<2>(result) << "\t"           // namespace
            << std::get<3>(result) << std::endl;    // name
            }
        }

        
       // return 0;
    }

}