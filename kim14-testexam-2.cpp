/*
2. Opening and searching in the GO-obo file (4 points): Our program should
work with any GO-obo file. Please don’t hardcode the filename in your application, if
you do, you get a minus point. Implement the --get-metacyc function for a specific
MetaCyc id. If the user gives, for example, the three arguments: --get-metacyc BETALACTAMASE-RXN filename.obo on the command line, then the GO-obo file is parsed
and the id, the name, the namespace and and the entry itself should displayed on the
terminal. Your functiomn has to return the data to the function caller, for instance as
a vector of tuples, print the result outside of the function, for instance in main.
Hint: If your code is very slow use limit your search to the first 1000 entries first to
save your programming time during development. You should un-comment this in
your final program. Here is a possible example invocation with output result:

$ appname --get-metacyc BETA-LACTAMASE-RXN gene_ontology-2022-01.obo
GO:0008800 beta-lactamase activity molecular_function MetaCyc:BETA-LACTAMASE-RXN
GO:0033250 penicillinase activity molecular_function MetaCyc:BETA-LACTAMASE-RXN
GO:0033251 cephalosporinase activity molecular_function MetaCyc:BETA-LACTAMASE-RXN
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "include/popl.hpp"

/*
static const char HELP[] =
R"(
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
)";
*/

bool is_valid_metacyc_id(const std::string& metacyc_id) {
    return metacyc_id.find("RXN") != std::string::npos || metacyc_id.find("PWY") != std::string::npos;
}

std::string get_metacyc_info(const std::string& metacyc_id, const std::string& obofile) {
    std::ifstream file(obofile);
    std::string line;
    std::string entry;
    std::string id;
    std::string name;
    std::string namespacee;
    std::string result;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << obofile << std::endl;
        return result;
    }

    bool found = false;
    while (std::getline(file, line)) {
        if (line.find("[Term]") != std::string::npos) {
            if (found) {
                break;
            }
            entry = "";
            id = "";
            name = "";
            namespacee = "";
        }
        if (line.find("id: ") != std::string::npos) {
            id = line.substr(4);
        }
        if (line.find("name: ") != std::string::npos) {
            name = line.substr(6);
        }
        if (line.find("namespace: ") != std::string::npos) {
            namespacee = line.substr(11);
        }
        if (line.find("MetaCyc:" + metacyc_id) != std::string::npos) {
            found = true;
            result = id + " " + name + " " + namespacee + " " + line;
        }
    }
    return result;
}

int main(int argc, char **argv) {
    popl::OptionParser app("kim14 PEX testexam Application\nUsage: appname [--help,--get-metacyc [MetaCyc-ID],--tab-metacyc] OBOFILE\nOptions");
    auto help = app.add<popl::Switch>("h", "help", "produce help message");
    auto get_metacyc = app.add<popl::Value<std::string>>("g", "get-metacyc", "--get-metacyc [MetaCyc-ID] OBOFILE");
    auto tab_metacyc = app.add<popl::Switch>("t", "tab-metacyc", "--tab-metacyc OBOFILE");

    app.parse(argc, argv);
    int i = 0;

    // wrong option check
    for (const auto& unknown_option: app.unknown_options()) {
        std::cout << "Error: unknown option '" << unknown_option << "'!\n";
        std::cout << "Use --help to show valid options!\n" ;
        return(1);
    }
    // filename given?
    if (app.non_option_args().empty()) {
        std::cout << "Error: OBOFILE argument is required.\n";
        std::cout << app << std::endl;
        //std::cout << HELP << std::endl;
        return 1;
    }

    std::string obofile = app.non_option_args()[0];

    if (help -> is_set()){
        std::cout << app << std::endl;
        //std::cout << HELP << std::endl;
        return(0);
    }

    
    if (get_metacyc->is_set()) {
        std::string metacyc_id = get_metacyc->value();
        if (!is_valid_metacyc_id(metacyc_id)) {
            std::cout << "Error: MetaCyc ID must contain 'RXN' or 'PWY'.\n";
            return 1;
        }
        std::cout << "Executing get_metacyc function with MetaCyc-ID: " << metacyc_id << " and OBOFILE: " << obofile << std::endl;
        auto search_results = get_metacyc_info(metacyc_id, obofile);

        if (search_results.empty()) {
            std::cout << "No entries found for MetaCyc ID '" << metacyc_id << "' in file '" << obofile << "'.\n";
        } else {
            std::cout << "Results for MetaCyc ID '" << metacyc_id << "' in file '" << obofile << "':\n";
            for (const auto& entry : search_results) {
                std::cout << entry.id << " " << entry.name << " " << entry.namespace_ << " " << entry.entry << "\n";
            }
        }

        return 0;
    }

    if (tab_metacyc->is_set()) {
        // tab metacyc code
        std::cout << "Executing tab_metacyc function with OBOFILE: " << obofile << std::endl;
        return 0;
    }

    std::cout << "Error: No valid option provided.\n";
    std::cout << app << std::endl;
    return 1;

}