#include <string>
#include "include/popl.hpp"


static const char HELP[] =
R"(
    PEX first test exam, part 1
    Filename: kim14-testexam-11.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-06-28
)";

bool is_valid_metacyc_id(const std::string& id) {
    return id.find("RXN") != std::string::npos || id.find("PWY") != std::string::npos;
}

int main(int argc, char **argv) {
    popl::OptionParser app("\nUsage: appname [--help,--get-metacyc [MetaCyc-ID],--tab-metacyc] OBOFILE\nOptions");
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
        std::cout << HELP;
        std::cout << app << std::endl;
        return(0);
    }

    
    if (get_metacyc->is_set()) {
        std::string metacyc_id = get_metacyc->value();
        if (!is_valid_metacyc_id(metacyc_id)) {
            std::cout << "Error: MetaCyc ID must contain 'RXN' or 'PWY'.\n";
            return 1;
        }
        std::cout << "Executing get_metacyc function with MetaCyc-ID: " << metacyc_id << " and OBOFILE: " << obofile << std::endl;
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