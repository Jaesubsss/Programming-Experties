#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <regex>
#include "include/popl.hpp"

class Kim14 {
private:
    std::ifstream file;
    std::string line;

public:
    Kim14(const std::string& obofile) : file(obofile) {
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << obofile << std::endl;
        }
    }

    bool is_valid_metacyc_id(const std::string& metacyc_id) {
        return metacyc_id.find("RXN") != std::string::npos || metacyc_id.find("PWY") != std::string::npos;
    }

    std::vector<std::tuple<std::string, std::string, std::string, std::string>> get_metacyc_info(const std::string& metacyc_id) {
        std::vector<std::tuple<std::string, std::string, std::string, std::string>> results;
        std::regex metacyc_regex(metacyc_id);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file" << std::endl;
            return results;
        }

        bool found = false;
        std::string id, name, namespacee, metacyc;

        while (std::getline(file, line)) {
            if (line.find("[Term]") != std::string::npos) {
                if (found) {
                    results.emplace_back(id, name, namespacee, metacyc);
                    found = false;
                }

                id.clear();
                name.clear();
                namespacee.clear();
                metacyc.clear();
            }

            if (line.find("id: ") == 0) {
                id = line.substr(4);
            }
            if (line.find("name: ") == 0) {
                name = line.substr(6);
            }
            if (line.find("namespace: ") == 0) {
                namespacee = line.substr(11);
            }

            if (line.find("xref: MetaCyc:") == 0) {
                if (std::regex_search(line, metacyc_regex)) {
                    found = true;
                    metacyc = line.substr(6);
                }
            }
        }

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

    for (const auto& unknown_option: app.unknown_options()) {
        std::cout << RED <<" Error: unknown option '" << unknown_option << "'!\n";
        std::cout << RED <<" Use --help to show valid options!\n";
        return 1;
    }

    if (help->is_set()) {
        std::cout << app << std::endl;
        return 1;
    }

    if (app.non_option_args().empty()) {
        std::cout << RED <<" Error: OBOFILE argument is required.\n";
        std::cout << app << std::endl;
        return 1;
    }

    std::string obofile = app.non_option_args()[0];
    Kim14 kim14(obofile);

    if (get_metacyc->is_set()) {
        std::string metacyc_id = get_metacyc->value();
        if (!kim14.is_valid_metacyc_id(metacyc_id)) {
            std::cout << RED <<" Error: MetaCyc ID must contain 'RXN' or 'PWY'.\n";
            return 1;
        }
        std::cout << YELLOW <<" Executing \033[1;36mget_metacyc\033[0m function with MetaCyc-ID: " << metacyc_id << " and OBOFILE: " << obofile << std::endl;
        auto search_results = kim14.get_metacyc_info(metacyc_id);

        if (search_results.empty()) {
            std::cout << RED <<" No entries found for MetaCyc ID '\033[1;36m" << metacyc_id << "\033[0m' in file '\033[1;36m" << obofile << "\033[0m'.\n";
        } else {
            std::cout << GREEN <<" Results for MetaCyc ID '\033[1;36m" << metacyc_id << "\033[0m' in file '\033[1;36m" << obofile << "\033[0m':\n";
            for (const auto& result : search_results) {
                std::cout << std::get<0>(result) << ", "         // id
                          << std::get<1>(result) << ", "         // name
                          << std::get<2>(result) << ", "         // namespace
                          << std::get<3>(result) << std::endl;   // metacyc
            }
        }

        return 0;
    }

    if (tab_metacyc->is_set()) {
        std::cout << YELLOW <<" Executing \033[1;36mtab_metacyc\033[0m function with OBOFILE: \033[1;36m" << obofile << "\033[0m" << std::endl;
        auto search_results = kim14.tab_metacyc_info();

        std::cout << GREEN <<" tab-metacyc information in file '\033[1;36m" << obofile << "\033[0m':\n";
        std::cout << GREEN <<" GO: ID,\tEC: ID,\t\tRXN-MetaCyc Entries\n";
        std::cout << "--------------------------------------------------" << std::endl;
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
