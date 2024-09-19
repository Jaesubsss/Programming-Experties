#include <string>
#include "include/popl.hpp"

// compile with: 
// g++ -std=c++11 -o .\build\testexam12.exe .\kim14-testexam-12.cpp
// .\build\testexam12.exe --help

static const char HELP[] =
R"(
    PEX first test exam, part 2
    Filename: kim14-testexam-12.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-06-28
)";

const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

bool is_valid_metacyc_id(const std::string& metacyc_id) {
    return metacyc_id.find("RXN") != std::string::npos || metacyc_id.find("PWY") != std::string::npos;
}

// get metacyc function
std::vector<std::tuple<std::string, std::string, std::string, std::string>> get_metacyc_info(const std::string& metacyc_id, const std::string& obofile) {

    std::ifstream file(obofile);
    std::string line;
    std::string metacyc;
    std::string id;
    std::string name;
    std::string namespacee;
    // here vector is used to output partially matching results as well.
    // multiple output is here already implemented, but can be still improved in task 3 using regex.
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> results;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << obofile << std::endl;
        return results;
    }

    //int maxterms = 1000; // needs to be removed before submit

    bool found = false;
    while (std::getline(file, line)) { 
        if (line.find("[Term]") != std::string::npos) { // get info from every [Term]
            if (found) {
                results.emplace_back(id, name, namespacee, metacyc);
                found = false;
                //break;
            }

            

            id.clear();
            name.clear();
            namespacee.clear();
            metacyc.clear();

            //if (maxterms-- <= 0) { // also needs to be removed! limit search to first 1000 entries
            //    break;
            //}
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

        if (line.find("MetaCyc:" + metacyc_id) != std::string::npos) {
            found = true;
            metacyc = line.substr(6);
        }
    }

    // if it's the last one
    if (found) {
        results.emplace_back(id, name, namespacee, metacyc);
    }


    return results;
}

int main(int argc, char **argv) {
    popl::OptionParser app("\n\033[1;36mo\033[0m Usage: appname [--help,--get-metacyc [MetaCyc-ID],--tab-metacyc] OBOFILE\n\033[1;36mo\033[0m Options");
    auto help = app.add<popl::Switch>("h", "help", "produce help message");
    auto get_metacyc = app.add<popl::Value<std::string>>("g", "get-metacyc", "--get-metacyc [MetaCyc-ID] OBOFILE");
    auto tab_metacyc = app.add<popl::Switch>("t", "tab-metacyc", "--tab-metacyc OBOFILE");

    app.parse(argc, argv);
    int i = 0;

    // wrong option check
    for (const auto& unknown_option: app.unknown_options()) {
        std::cout << RED <<" Error: unknown option '" << unknown_option << "'!\n";
        std::cout << RED <<" Use --help to show valid options!\n" ;
        return(1);
    }

    // help?
    if (help -> is_set()){
        std::cout << HELP;
        std::cout << app << std::endl;
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
    
    // get_metacyc?
    if (get_metacyc->is_set()) {
        std::string metacyc_id = get_metacyc->value();
        if (!is_valid_metacyc_id(metacyc_id)) {
            std::cout << RED <<" Error: MetaCyc ID must contain 'RXN' or 'PWY'.\n";
            return 1;
        }
        std::cout << YELLOW <<" Executing \033[1;36mget_metacyc\033[0m function with MetaCyc-ID: " << metacyc_id << " and OBOFILE: " << obofile << std::endl;
        auto search_results = get_metacyc_info(metacyc_id, obofile);

        if (search_results.empty()) {
            std::cout << RED <<" No entries found for MetaCyc ID '\033[1;36m" << metacyc_id << "\033[0m' in file '\033[1;36m" << obofile << "\033[0m' .\n";
        } else {
            std::cout << GREEN <<" Results for MetaCyc ID '\033[1;36m" << metacyc_id << "\033[0m' in file '\033[1;36m" << obofile << "\033[0m' :\n";
            
            for (const auto& result : search_results) {
                std::cout << std::get<0>(result) << " "         // id
                          << std::get<1>(result) << " "         // name
                          << std::get<2>(result) << " "         // namespace
                          << std::get<3>(result) << std::endl;  // metacyc
            }

            /*
            // I think it looks better
            for (const auto& result : search_results) {
                std::cout << "------------------------------------------------";
                std::cout << std::get<0>(result) << std::endl // id
                          << std::get<1>(result) << std::endl // name
                          << std::get<2>(result) << std::endl // namespace
                          << std::get<3>(result) << std::endl // metacyc
                          << std::endl;
            }
            */
        }

        return 0;
    }

    // tab_metacyc?
    if (tab_metacyc->is_set()) {
        // tab metacyc code
        std::cout << YELLOW << " Executing \033[1;36mtab_metacyc\033[0m function with OBOFILE:  \033[1;36m" << obofile << "\033[0m" <<std::endl;
        return 0;
    }

    std::cout << RED <<" Error: No valid option provided.\n";
    std::cout << app << std::endl;
    return 1;

}