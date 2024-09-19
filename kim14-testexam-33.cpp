/*
3. Advanced Terminal Application (4 points):

    A (1 point): Extend your application as a C++ class.

    B) (1 point) Extend the application so that it can handle more than 1 filename at the same time
    given on the terminal. Hint: better handle multiple files in main, not within the function/method! 

    C) (2 points): Extra point: Implement the --go-count command for one or more files, it should as
    well the count how often a GO-ids is found, the GO-id and the filename to the terminal:

*/

#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include "include/popl.hpp"

// compile with:
// g++ -std=c++11 -o .\build\testexam33.exe .\kim14-testexam-33.cpp
// .\build\testexam33.exe --help

static const char HELP[] =
R"(
    PEX first test exam 3, part 3
    Filename: kim14-testexam-33.cpp
    Made by: Jaesub Kim, University of Potsdam, Germany (2024)
    Date: 2024-09-19

    Extract information from Uniprot data files.
-----------------------------------------------
)";

static const char MAND[] = 
"\033[1;36mo\033[0m Mandatory arguments are:\n"
"    FILE - one (or more) uncompressed Uniprot data file(s)\n";

class Kim14{

public:
    Kim14() {}

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

int goCount(const std::string& filename, const std::string& GOid) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return 1;
    }
    
    int count = 0;

    while (std::getline(file, line) ) {
        if (line.empty()) continue;

        // GO ID가 존재하는지 찾기
        if (line.find(GOid) != std::string::npos) {
            count++;
        }
    }

    file.close();
    return count;
}

};

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
        Kim14 kim14;    

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

            auto search_results = kim14.goSearch(filename, GOid);
            for (const auto& result : search_results) {
                std::cout << std::get<0>(result) << " "         // id
                        << std::get<1>(result) << std::endl;         // GOid
            }
        }

        if (count -> is_set()){
            std::string GOid = count -> value();
            std::regex valid_GOid ("GO:\\d{7}");

            if (!std::regex_match(GOid, valid_GOid)) {
                std::cerr << RED << " Error: Invalid GO-id." << std::endl;
                std::cerr << RED << " A GO-id starts with the prefix 'GO:' followed by 7 digits" << std::endl;
                return 1;
            }

            auto count_result = kim14.goCount(filename, GOid);
            std::cout << count_result << "\t"         // id
                    << GOid << "\t" 
                    << filename << std::endl;         // GOid
            
        }

        //std::cout << YELLOW << " Processing file: " << filename << std::endl;
    }

    return 0;

}