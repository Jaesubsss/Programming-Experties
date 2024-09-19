/*
2. Opening and searching in the FASTA file (4 points):
The input file we are working with is: uniprot-corona-virus-data-2022-02.dat. Our program should
however work with any other Uniprot file, for instance as well with the file uniprot-microsporidiandata-2022-02.dat and obviously as well with other uncompressed UniProt data files.

Implement a function to give a tabular output showing in the first column the Uniprot ID and in the
second column the matching GO ID which was searched for this protein ID. If a protein ID has no
matching GO it should be not shown. Before opening the file take care that if the file is gzipped or
not. Warn the user if the file is gzipped, that it must be uncompressed. Write methods search_go_id
and count_go_id where the latter has no functionality (might be required).

Hint: Don’t print the text inside of the function(s) but return the text or the Uniprot IDs for
instance as a vector to the function caller. Print it then outside of the function.
*/

#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include "include/popl.hpp"

// compile with:
// g++ -std=c++11 -o .\build\testexam32.exe .\kim14-testexam-32.cpp
// .\build\testexam32.exe --help

static const char HELP[] =
R"(
    PEX first test exam 3, part 2
    Filename: kim14-testexam-32.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-09-19

    Extract information from Uniprot data files.
-----------------------------------------------
)";

static const char MAND[] = 
"\033[1;36mo\033[0m Mandatory arguments are:\n"
"    FILE - one (or more) uncompressed Uniprot data file(s)\n";

std::vector<std::tuple<std::string, std::string>> goSearch(const std::string& filename, const std::string& GOid) {
    std::ifstream file(filename);
    std::string line;
    std::string id;
    std::vector<std::tuple<std::string, std::string>> results;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return results;
    }
    
    bool found = false;
    while (std::getline(file, line) ) {
        if (line.empty()) continue;

        if (line.rfind("ID", 0) == 0) { // line starts with "ID"
            // 만약 이전 ID가 있고, GO ID가 발견되었다면 결과에 추가
            if (!id.empty()) {
                if (found) {
                    results.emplace_back(id, GOid);
                }
            }
            
            id.clear();  // 새로운 ID가 발견되면 초기화
            found = false;

            // 새롭게 line을 istringstream에 넣어줌
            std::istringstream iss(line);
            
            // 첫 번째 필드("ID")를 건너뜁니다.
            std::string token;
            iss >> token; // "ID" 건너뜀

            // 두 번째 필드(Uniprot ID)를 추출
            iss >> id;
        }

        // GO ID가 존재하는지 찾기
        if (line.find(GOid) != std::string::npos) {
            found = true;
        }
    }

    // 마지막 ID에 대해서도 결과를 추가
    if (!id.empty() && found) {
        results.emplace_back(id, GOid);
    }

    file.close();
    return results;
}


const std::string RED = "\033[1;31mo\033[0m";
const std::string GREEN = "\033[1;32mo\033[0m";
const std::string YELLOW = "\033[1;33mo\033[0m";

int main(int argc, char **argv){
    popl::OptionParser op("\n\033[1;36mo\033[0m Usage: appname [--help|--go-search|--go-count] [FILE] ?[FILE] ...?\n\033[1;36mo\033[0m Options");
    auto help = op.add<popl::Switch>("h", "help", "- display this help page");
    auto search = op.add<popl::Value<std::string>>("s", "go-search", "- count how often a GO id is in the uniprot file");
    auto count = op.add<popl::Value<std::string>>("m", "go-count", "- search Uniprot IDs for the given annotation");

    op.parse(argc, argv);

    // wrong argument number check
    if (argc < 2 ) {
        std::cerr << RED << " Error: No arguments are given!" << std::endl;
        std::cout << HELP << std::endl;
        std::cout << op << std::endl;
        std::cout << MAND << std::endl;
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
        std::cout << MAND << std::endl;
        return 1;
    }

    // get list of filename
    std::vector<std::string> filenames = op.non_option_args(); 

    // File given?
    if (op.non_option_args().empty()) {
        std::cerr << RED << " Error: Invalid Argument! check your GOid or filename if it's right." << std::endl;
        std::cout << op << std::endl;
        return 1;
    }

    for (const auto& filename : filenames) {

        // Check if the file exists
        std::ifstream file(filename);
        if (!file.good()) {
            std::cerr << "Error: The file '" << filename << "' does not exist." << std::endl;
            continue;  
        }

        // Check if the file is uncompressed
        if (std::regex_match(filename, std::regex(".*\\.gz$"))) {
            std::cerr << "Error: Input file must be uncompressed." << std::endl;
            continue;  
        }

        // Check if the file has a .dat extension
        if (!std::regex_match(filename, std::regex(".*\\.dat$"))) {
            std::cerr << "Error: The file '" << filename << "' must have a .dat extension." << std::endl;
            continue;  
        }

        // 유효한 파일 처리 (여기서 파일 내용을 처리하는 코드 추가 가능)

        if (search -> is_set()){
            std::string GOid = search -> value();
            std::cout << GREEN << " Executing go-search function with GO-id: " << GOid << " and file: " << filename << std::endl;
            std::regex valid_GOid ("GO:\\d{7}");

            if (!std::regex_match(GOid, valid_GOid)) {
                std::cerr << RED << " Error: Invalid GO-id." << std::endl;
                std::cerr << RED << " A GO-id starts with the prefix 'GO:' followed by 7 digits" << std::endl;
                return 1;
            }

            auto search_results = goSearch(filename, GOid);
            for (const auto& result : search_results) {
                std::cout << std::get<0>(result) << " "         // id
                        << std::get<1>(result) << std::endl;         // GOid
            }
        }

        if (count -> is_set()){
            std::cout << GREEN << " Executing go-count function with file: " << filename << std::endl;
            std::cout << YELLOW << " All fine but no functionality yet ... " << std::endl;
        }

        //std::cout << YELLOW << " Processing file: " << filename << std::endl;
    }

    return 0;

}