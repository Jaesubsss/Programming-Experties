/*
1 (1 point): Extend your application so that as a C++ class and so that it can handle more than 1
filename at the same time given on the terminal. Hint: better handle multiple files in main, not
within the function/method!
2) (3 points): Implement the summary function so that it prints out for all sequence ids the sequence
lengths like this:
$ FastaParser3 --summary sars-cov1.fasta sars-cov2.fasta
sp|P0C6U8|R1A_CVHSA 4479
sp|P0C6X7|R1AB_CVHSA 7173
...
sp|P0DTC1|R1A_SARS2 4522
sp|P0DTC2|SPIKE_SARS2 1391
sp|P0DTC3|AP3A_SARS2 388 ...
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

class Kim14{

public:
    Kim14() {}

    std::vector<std::tuple<std::string, std::string, bool>> searchSequence(const std::string& filename, const std::string& pattern) {
        std::vector<std::tuple<std::string, std::string, bool>> results;
        std::string line;
        std::string id;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "\033[1;31mo\033[0m" << " Error: Unable to open file " << filename << std::endl;
            return {};
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

    std::vector<std::tuple<std::string, int>> summarySequence(const std::string& filename){
        std::string line;
        std::string id;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "\033[1;31mo\033[0m" << " Error: Unable to open file " << filename << std::endl;
            return {};
        }

        std::string lastline;
        int count=0;
        std::vector<std::tuple<std::string, int>> results;

        while(std::getline(file,line)) {
            if (line.empty()) continue;

            if(line.find(">") != std::string::npos){
                if (!id.empty()){ 
                    results.emplace_back(id, (count-1)*60+lastline.length());
                }
                id = line.substr(1, line.find(" ") - 1);
                count = 0;
            } else {
                count ++;
            }
            //count = count++;
            lastline = line;
            
        }
        // Store the last sequence ID and its result
        if (!id.empty()) {
            results.emplace_back(id, (count-1)*60+lastline.length());
        }
        file.close();

        return results;
    }

};

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
    if (argc < 2) {
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
    Kim14 kim14;
    std::vector<std::string> filenames = op.non_option_args();

    for (const auto& filename : filenames) {

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
    }
    

    if (search->is_set()) {
        std::string pattern = search->value();
        std::cout << YELLOW << " Executing search function with pattern: " << pattern << " and files: ";
        for (const auto& filename : filenames) {
            std::cout << filename << " ";
        }
        std::cout << std::endl;

        std::regex valid_pattern("[RHKDESTNQCUGPAVILMFYW]+");
        if (!std::regex_match(pattern, valid_pattern)) {
            std::cerr << RED << " Error: The pattern must contain only valid amino acids." << std::endl;
            return 1;
        }

        for (const auto& filename : filenames) {
            auto search_results = kim14.searchSequence(filename, pattern);
            std::cout << GREEN << " Search result in file: " << filename << 
            std::endl;
            for (const auto& result : search_results) {
                std::cout << std::get<0>(result) << " "       // id
                          << std::get<1>(result) << " ";      // pattern
                if (std::get<2>(result)) {
                    std::cout << "\033[1;36mtrue\033[0m" << std::endl;  // found
                } else {
                    std::cout << "\033[1;31mfalse\033[0m" << std::endl; // not found
                }
            }
        }
    }

    if (summary->is_set()) {
        std::cout << YELLOW << " Executing summary function with files: ";
        for (const auto& filename : filenames) {
            std::cout << filename << " ";
        }
        std::cout << std::endl;
        
        for (const auto& filename : filenames) {
            std::cout << GREEN << " Summary of file: " << filename << " is done." << std::endl;
            auto summary_results = kim14.summarySequence(filename);
            for (const auto& result : summary_results) {
                std::cout << std::get<0>(result) << " "     // id
                          << std::get<1>(result) << std::endl; // length
            }
        }
    }

    return 0;
}