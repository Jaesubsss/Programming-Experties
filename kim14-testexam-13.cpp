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

#include <string>
#include <regex>
#include "include/popl.hpp"

/*
static const char HELP[] =
R"(
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
)";
*/
class Kim14{
private: 
    std::string line;
    std::string metacyc;
    std::string id;
    std::string name;
    std::string namespacee;
    std::string EC;
    std::string RXN_metacyc;
    std::ifstream file;

public:
    // constructor
    Kim14(const std::string& obofile) : file(obofile) {
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << obofile << std::endl;
        }
    }

    bool is_valid_metacyc_id(const std::string& metacyc_id) {
        return metacyc_id.find("RXN") != std::string::npos || metacyc_id.find("PWY") != std::string::npos;
    }

    // get metacyc function
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> get_metacyc_info(const std::string& metacyc_id) {

        
        // here vector is used to output partially matching results as well.
        std::vector<std::tuple<std::string, std::string, std::string, std::string>> results;
        std::regex metacyc_regex(metacyc_id);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file" << std::endl;
            return results;
        }

        bool found = false;
        while (std::getline(file, line)) { 
            if (line.find("[Term]") != std::string::npos) { // get info from every [Term]
                if (found) {
                    results.emplace_back(id, name, namespacee, metacyc);
                    found = false;
                }

                

                id.clear();
                name.clear();
                namespacee.clear();
                metacyc.clear();

            }
            if (line.find("id: ") != std::string::npos) {
                id = line.substr(4);
                //std::cout << id << std::endl; // Debuging...
            }
            if (line.find("name: ") != std::string::npos) {
                name = line.substr(6);
                //std::cout << name << std::endl;
            }
            if (line.find("namespace: ") != std::string::npos) {
                namespacee = line.substr(11);
                //std::cout << namespacee << std::endl;
            }

            // extracting infos from every term even if it's not the one we're looking for
            // might be unefficient, but since metacyc is located at the end of the term, it's the easiest way

            if (line.find("MetaCyc:") != std::string::npos) { // divide the comparision procedure in two parts
                if (std::regex_search(line, metacyc_regex)){
                    found = true;
                    metacyc = line.substr(6);
                }
            }
        }

        // if it's the last one
        if (found) {
            results.emplace_back(id, name, namespacee, metacyc);
        }


        return results;
    }

    std::vector<std::tuple<std::string, std::string, std::string>> tab_metacyc_info() {
        std::vector<std::tuple<std::string, std::string, std::string>> results;
        std::regex rxn("RXN");

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file" << std::endl;
            return results;
        }

        bool found = false;
        std::string id, EC, RXN_metacyc;


        while (std::getline(file, line)) {
            if (line.find("[Term]") != std::string::npos) {
                if (found) {
                    results.emplace_back(id, EC, RXN_metacyc);
                    found = false;
                }

                id.clear();
                EC.clear();
                RXN_metacyc.clear();
            }

            if (line.find("id: ") == 0) {
                id = line.substr(4);
            }
            if (line.find("xref: EC:") == 0) {
                EC = line.substr(6);
            }

            if (line.find("xref: MetaCyc:") == 0) {
                if (!EC.empty() & std::regex_search(line, rxn)) {
                    found = true;
                    RXN_metacyc = line.substr(14);
                }
            }

            if (results.size() > 50) { // too many results, limit to 50
                break;                 // this code needs to be removed at the end 
            }
        }

        if (found) {
            results.emplace_back(id, EC, RXN_metacyc);
        }

        return results;
    }

};

const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

int main(int argc, char **argv) {
    popl::OptionParser app("\033[1;36mo\033[0m kim14 PEX testexam Application\n\033[1;36mo\033[0m Usage: appname [--help,--get-metacyc [MetaCyc-ID],--tab-metacyc] OBOFILE\n\033[1;36mo\033[0m Options");
    auto help = app.add<popl::Switch>("h", "help", "produce help message");
    auto get_metacyc = app.add<popl::Value<std::string>>("g", "get-metacyc", "--get-metacyc [MetaCyc-ID] OBOFILE");
    auto tab_metacyc = app.add<popl::Switch>("t", "tab-metacyc", "--tab-metacyc OBOFILE");

    app.parse(argc, argv);

    // wrong option check
    for (const auto& unknown_option: app.unknown_options()) {
        std::cout << RED <<" Error: unknown option '" << unknown_option << "'!\n";
        std::cout << RED <<" Use --help to show valid options!\n" ;
        return 1;
    }

    // help?
    if (help -> is_set()){
        std::cout << app << std::endl;
        //std::cout << HELP << std::endl;
        return 1;
    } 

    // OBOFILE given?
    if (app.non_option_args().empty()) {
        std::cout << RED <<" Error: OBOFILE argument is required.\n";
        std::cout << app << std::endl;
    // no file
        return 1;
    }
    // yes file
    std::string obofile = app.non_option_args()[0];
    Kim14 kim14(obofile); 
    
    // get_metacyc?
    if (get_metacyc->is_set()) {
        std::string metacyc_id = get_metacyc->value();
        if (!kim14.is_valid_metacyc_id(metacyc_id)) {
            std::cout << RED <<" Error: MetaCyc ID must contain 'RXN' or 'PWY'.\n";
            return 1;
        }
        std::cout << YELLOW <<" Executing \033[1;36mget_metacyc\033[0m function with MetaCyc-ID: " << metacyc_id << " and OBOFILE: " << obofile << std::endl;
        auto search_results = kim14.get_metacyc_info(metacyc_id);

        if (search_results.empty()) {
            std::cout << RED <<" No entries found for MetaCyc ID '\033[1;36m" << metacyc_id << "\033[0m' in file '\033[1;36m" << obofile << "\033[0m' .\n";
        } else {
            std::cout << GREEN <<" Results for MetaCyc ID '\033[1;36m" << metacyc_id << "\033[0m' in file '\033[1;36m" << obofile << "\033[0m' :\n";
            
            for (const auto& result : search_results) {
                std::cout << std::get<0>(result) << ", "         // id
                          << std::get<1>(result) << ", "         // name
                          << std::get<2>(result) << ", "         // namespace
                          << std::get<3>(result) << std::endl;  // metacyc
            }

        }

        return 0;
    }

    // tab_metacyc?
    if (tab_metacyc->is_set()) {
        std::cout << YELLOW <<" Executing \033[1;36mtab_metacyc\033[0m function with OBOFILE: \033[1;36m" << obofile << "\033[0m" << std::endl;
        auto search_results = kim14.tab_metacyc_info();

        std::cout << GREEN <<" tab-metacyc information in file '\033[1;36m" << obofile << "\033[0m':\n";
        std::cout << GREEN <<" GO: ID,\tEC: ID,\t\tRXN-MetaCyc Entries\n";
        std::cout << "----------------------------------------------------" << std::endl;
        for (const auto& result : search_results) {
            std::cout << std::get<0>(result) << ",\t"         // id
                      << std::get<1>(result) << ",\t"         // EC
                      << std::get<2>(result) << std::endl;   // RXN metacyc
        }

        return 0;
    }

    std::cout << RED <<" Error: No valid option provided.\n";
    std::cout << app << std::endl;
    return 1;

}