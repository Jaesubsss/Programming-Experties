/*
Opening and searching in the FASTA file (4 points): The input files we are working with are:
sars-cov1.fasta and sars-cov2.fasta from the Moodle course. Our program should however work
with any FASTA file. Implement a searchSequence function to display the sequence IDs which
contain the given sequence search pattern. Hint: you should use regular expressions for searching
in the file. The two arguments for this function should be the input filename and as second argument
the search pattern. You should return the output for instance as a vector of tuples, giving the
sequence ids, the pattern and if it hit does or does not matches the pattern and then print out the
result in the main function. You can ignore the line break problem in your search. Below is a
possible sample run of your program with parts of its tabular output:
$ FastaParser2 --search MAT sars-cov1.fasta
sp|P59637|VEMP_CVHSA MAT false
...
sp|P0C6X7|R1AB_CVHSA MAT true
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



std::vector<std::tuple<std::string, std::string, bool>> searchSequence(const std::string& filename, const std::string& pattern) {
    std::ifstream file(filename);
    std::string line;
    std::string id;
    std::vector<std::tuple<std::string, std::string, bool>> results;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return results;
    }

    bool found = false;
    while(std::getline(file,line)) {
        if (line.empty()) continue;

        if(line.find(">") != std::string::npos){
            if (!id.empty()){ 
                results.emplace_back(id, pattern, found);
                id.clear(); // initializing again
                found = false;
            }

            id = line.substr(1, line.find(" ") - 1);

        }

        if (line.find(pattern) != std::string::npos) {
            found = true;
        }
        
    }
    // Store the last sequence ID and its result
    if (!id.empty()) {
        results.emplace_back(id, pattern, found);
    }
    file.close();

    return results;
}


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

        auto search_results = searchSequence(filename, pattern);
        for (const auto& result : search_results) {
            std::cout << std::get<0>(result) << " "         // id
                      << std::get<1>(result) << " ";         // pattern
            if (std::get<2>(result)) {
                std::cout << "\033[1;36mtrue\033[0m" << std::endl;   // found
            } else {
                std::cout << "\033[1;31mfalse\033[0m" << std::endl;  // not found
            }
                      
        }
    }

    if (summary -> is_set()){
        std::cout << YELLOW << " Executing summary function with file: " << filename << std::endl;
    }

    return 0;
}