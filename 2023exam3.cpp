/*
3. Advanced terminal application (3+1 points)

3.1.(1 point): Extend your application as a C++ class (1 extra point)

3.2.(1 point): Extend your application with the --get-table-ec option so that an additional
column for EC identifiers is added to the end of the columns, in this case you should only
show the entries-lines which have an EC entry (you can assume one EC entry per id.

3.3 (2 points) Implement the --new-ids option so that only entry lines are shown which were
added in the second file but are not in the first file. If you just show the ids on the terminal -
one point, two points if you show the full entry lines like in the tasks before, here is an
example output for getting two points:

app-name --new-ids go-2020-01.obo go-2022-01.obo
*/

#include <string>
#include <regex>
#include "include/popl.hpp"

static const char HELP[] =
R"(
    PEX Exam 2023, part 1
    Filename: 2023exam1.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-09-19
)";

class Kim14{
    public:
    Kim14() {}

std::vector<std::tuple<std::string, std::string, std::string, bool>> tabulate(const std::string& filename){
    std::ifstream file(filename);
    std::string line;
    std::string id;
    std::string name;
    std::string namesp;
    bool is_obsolete;
    std::vector<std::tuple<std::string, std::string, std::string, bool>> results;

    //int c;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return results;
    }



    while (std::getline(file, line) ) {
        if (line.empty()) continue;

        if (line.rfind("id:", 0) == 0) { // line starts with "id"
            id.clear();
            /*
            std::istringstream iss(line);
            iss >> id;
            iss >> id; // second field is id
            */
            id = line.substr(4);
        }

        if (line.rfind("name:", 0) == 0) { // line starts with "name"
            name.clear();
            name = line.substr(6);
        }
        
        if (line.rfind("namespace:", 0) == 0) { // line starts with "namespace"
            namesp.clear();
            namesp = line.substr(11);
        }

        if (line.rfind("is_obsolete:", 0) == 0) { // line starts with "is_obsolete"
            is_obsolete = true;
        } 

        if (line == "[Term]") {
            results.emplace_back(id, namesp, name, is_obsolete);
            is_obsolete = false;
            //c++;
        }
    }

    // 마지막 ID에 대해서도 결과를 추가
    if (!id.empty()) {
        results.emplace_back(id, namesp, name, is_obsolete);
    }

    file.close();
    return results;

}

std::vector<std::tuple<std::string, std::string, std::string, bool, std::string>> tabulate_ec(const std::string& filename){
    std::ifstream file(filename);
    std::string line;
    std::string id;
    std::string name;
    std::string namesp;
    std::string ec;
    bool is_obsolete;
    std::vector<std::tuple<std::string, std::string, std::string, bool, std::string>> results;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return results;
    }

    bool ec_found = false;

    while (std::getline(file, line) ) {
        if (line.empty()) continue;

        if (line.rfind("id:", 0) == 0) { // line starts with "id"
            id.clear();
            /*
            std::istringstream iss(line);
            iss >> id;
            iss >> id; // second field is id
            */
            id = line.substr(4);
        }

        if (line.rfind("name:", 0) == 0) { // line starts with "name"
            name.clear();
            name = line.substr(6);
        }
        
        if (line.rfind("namespace:", 0) == 0) { // line starts with "namespace"
            namesp.clear();
            namesp = line.substr(11);
        }

        if (line.rfind("is_obsolete:", 0) == 0) { // line starts with "is_obsolete"
            is_obsolete = true;
        } 

        if (line.rfind("xref: EC:",0) == 0) { // != std::string::npos
            ec_found = true;
            ec.clear();
            ec = line.substr(6);
        }

        if (line == "[Term]") {
            if (ec_found) {
                results.emplace_back(id, namesp, name, is_obsolete, ec);
            } else{
                results.emplace_back(id, namesp, name, is_obsolete, "");
            }
            is_obsolete = false;
            ec_found = false;

            //c++;
        }
    }

    // 마지막 ID에 대해서도 결과를 추가
    if (!id.empty()) {
        if (ec_found) {
            results.emplace_back(id, namesp, name, is_obsolete, ec);
        } else{
            results.emplace_back(id, namesp, name, is_obsolete, "");
        }
    }

    file.close();
    return results;

}

std::vector<std::tuple<std::string, std::string, std::string, bool>> new_ids(const std::string& filename1, const std::string& filename2){
    std::vector<std::tuple<std::string, std::string, std::string, bool>> result1 = tabulate(filename1);
    std::vector<std::tuple<std::string, std::string, std::string, bool>> result2 = tabulate(filename2);

    std::vector<std::tuple<std::string, std::string, std::string, bool>> diff;
    int count = 0;

    for (const auto& entry2 : result2) {
        bool found = false;
        for (const auto& entry1 : result1) {
            if (std::get<0>(entry2) == std::get<0>(entry1)) { // ID가 같으면
                found = true;
                break;
            }
        }
        if (!found) {
            diff.push_back(entry2); // result1에 없는 항목을 diff에 추가
            count++;
        }
    }
    return diff;

}
};

const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

int main(int argc, char **argv){
    popl::OptionParser op("\n\033[1;36mo\033[0m Usage: appname [-helpl--get-tablel--get-table-ecl--get-table-metacycl--new-ids] ?obofile? ?obofile? \n\033[1;36mo\033[0m Options");
    auto help = op.add<popl::Switch>("h", "help", "- display this help page");
    auto table = op.add<popl::Switch>("t", "get-table", "- get table");
    auto table_ec = op.add<popl::Switch>("e", "get-table-ec", "- get table ec");
    auto table_metacyc = op.add<popl::Switch>("m", "get-table-metacyc", "- get table metacyc");
    auto new_ids = op.add<popl::Switch>("n", "new-ids", "- new ids");

    op.parse(argc, argv);

    // wrong argument number check
    if (argc < 2 ) {
        std::cerr << RED << " Error: No arguments are given!" << std::endl;
        std::cout << HELP << std::endl;
        std::cout << op << std::endl;
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
        return 1;
    }


    // new_ids ------

    if (new_ids -> is_set()) {
        // 2 filenames given?
        std::vector<std::string> filenames = op.non_option_args(); 

        if (filenames.size() != 2){
            std::cerr << RED << " Error: Invalid Argument! Input must be 2 files." << std::endl;
            std::cout << op << std::endl;
            return 1;
        }

        for (const auto& filename : filenames) {

            // Check if the file exists
            std::ifstream file(filename);
            if (!file.good()) {
                std::cerr << RED << " Error: The file '" << filename << "' does not exist." << std::endl;
                continue;  // 다음 파일로 넘어가기
            }

            if (!std::regex_match(filename, std::regex(".*obo.*"))) {
                std::cerr << RED << " Error: The file must be goobo file." << std::endl;
                return 1;
            }

        }

        std::cout << YELLOW << " Executing new-ids function  " << std::endl;

        Kim14 kim14;

        auto results = kim14.new_ids(filenames[0], filenames[1]);

        for (const auto& result : results) {
            std::cout << std::get<0>(result) << " "         // id
                    << std::get<1>(result) << " "         // namespace
                    << std::get<2>(result) << " ";         // name
            if (std::get<3>(result)) {
                std::cout << "\033[1;36mtrue\033[0m" << std::endl;   // is_obsolete
            } else {
                std::cout << "\033[1;31mfalse\033[0m" << std::endl;  // not found
            }
        }

        return 0;
    }
    // ---------------

    // File given?
    if (op.non_option_args().empty()) {
        std::cerr << RED << " Error: No file. Please enter the file." << std::endl;
        std::cout << op << std::endl;
        return 1;
    }

    // get filename
    std::string filename = op.non_option_args().back();

    // Check if file exists
    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << RED << " Error: The file " << filename << " does not exist." << std::endl;
        return 1;
    }

    if (!std::regex_match(filename, std::regex(".*obo.*"))) {
        std::cerr << RED << " Error: The file must be goobo file." << std::endl;
        return 1;
    }

    Kim14 kim14;

    if (table -> is_set()){
            std::cout << YELLOW << " Executing get-table function with file: " << filename << std::endl;
            
            auto results = kim14.tabulate(filename);
            for (const auto& result : results) {
                std::cout << std::get<0>(result) << " "         // id
                        << std::get<1>(result) << " "         // namespace
                        << std::get<2>(result) << " ";         // name
                if (std::get<3>(result)) {
                    std::cout << "\033[1;36mtrue\033[0m" << std::endl;   // is_obsolete
                } else {
                    std::cout << "\033[1;31mfalse\033[0m" << std::endl;  // not found
                }
            }
    }

    if (table_ec -> is_set()){
            std::cout << YELLOW << " Executing get-table-ec function with file: " << filename << std::endl;

            auto results = kim14.tabulate_ec(filename);

            for (const auto& result : results) {
                std::cout << std::get<0>(result) << " "         // id
                        << std::get<1>(result) << " "         // namespace
                        << std::get<2>(result) << " ";         // name
                if (std::get<3>(result)) {
                    std::cout << "\033[1;36mtrue\033[0m" << " ";   // is_obsolete
                } else {
                    std::cout << "\033[1;31mfalse\033[0m" << " ";  // not found
                }
                std::cout << std::get<4>(result) << std::endl;         // ec
            }
    }

    if (table_metacyc -> is_set()){
            std::cout << YELLOW << " Executing get-table-metacyc function with file: " << filename << std::endl;
            std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
            return 1;
    }

}