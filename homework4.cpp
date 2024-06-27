/// usr/bin/g++ filename.cpp -o filename && exec ./filename
/*
 * cpp-app.cpp
 *
 * Copyright (c) 2024 Detlef Groth, University of Potsdam
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the 'Software'),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#ifdef __cpp_lib_filesystem
#include <filesystem>
namespace fs = std::filesystem;
#elif __cpp_lib_experimental_filesystem
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include "include/ghc/filesystem.hpp"
namespace fs = ghc::filesystem;
#endif

#include "pex.hpp"
#include "include/popl.hpp"

// PexBan 클래스 정의
class PexBan {
private:
    std::map<std::string, std::vector<std::string>> items; // 항목을 저장할 맵
    std::map<std::string, std::string> mymap; // 리스트 상태를 저장할 맵
    fs::path itemFile; // 항목 파일 경로
    const std::string ERROR = "\033[31m"; // 에러 메시지 색상
    const std::string RESET = "\033[0m"; // 색상 리셋
    bool verbose = false; // 상세 메시지 출력 여부

public:
    // PexBan 생성자
    PexBan(bool verbose = false, std::string itemsfile = "") {
        this->verbose = verbose; // 상세 메시지 여부 설정
        mymap["t"] = "TODO";
        mymap["p"] = "PROGRESS";
        mymap["d"] = "DONE";
        std::string home = pex::get_home_directory(); // 홈 디렉토리 가져오기
        fs::path homeDir(home);
        fs::path pexbanPath = homeDir / ".config" / "pexban"; // 설정 파일 경로
        fs::path itemFile;
        if (itemsfile != "") {
            itemFile = fs::path(itemsfile); // 사용자 정의 파일 경로 사용
        } else {
             itemFile =  pexbanPath / "items.txt"; // 기본 파일 경로 사용
        }
        if (verbose) {
            std::cout << itemFile << std::endl; // 경로 출력
        }
        if (!fs::is_directory(pexbanPath)) {
            fs::create_directory(pexbanPath); // 디렉토리 생성
        }
        this->itemFile = itemFile;
    }
    
    // ERROR 상수 접근 함수
    const std::string& getError() const {
        return ERROR;
    }

    // RESET 상수 접근 함수
    const std::string& getReset() const {
        return RESET;
    }
    
    // 항목 추가 함수
    void itemAdd(std::string list, std::string item) {
        if (mymap.count(list) == 1) {
            items[list].push_back(item); // 항목 추가
        }
        if (verbose) {
            std::cout << "list: '" << list << "' add item: '" << item << "'" << std::endl; // 메시지 출력
        }
    }

    // 항목 삭제 함수
    void itemDelete(std::string list, int itemIndex) {
        if (mymap.count(list) == 1) {
            //if (items[list].size() >= itemIndex) {
            if (items[list].size() >= static_cast<size_t>(itemIndex)) {
                items[list].erase(items[list].begin() + itemIndex - 1); // 항목 삭제
                if (verbose) {
                    std::cout << "List: '" << list << "' deleted item: '" << itemIndex << "'" << std::endl; // 메시지 출력
                }
            } else {
                std::cout << ERROR << "Error: List " << list << " only contains " << items[list].size() << " items!\n" << RESET; // 에러 메시지
            }
        } else {
            std::cout << ERROR << "Error: List " << list << " does not exists! There are only t, p or d lists!\n" << RESET; // 에러 메시지
        }
    }

    // 항목 저장 함수
    void itemSave () {
        std::ofstream fout;
        fout.open(itemFile);
        for (const auto& [key, its] : items) {
            for (auto item : its) {
                fout << key << " " << item << "\n"; // 파일에 항목 저장
            }
        }
        fout.close();
    }

    // 항목 불러오기 함수
    void itemLoad () {
        std::ifstream fin;
        std::string line;
        if (fs::exists(itemFile)) {
            fin.open(itemFile);
            while (std::getline(fin,line)) {
                if (verbose) {
                    std::cout << line << std::endl; // 파일에서 항목 읽기
                }
                if (line.find("t") == 0) {
                    items["t"].push_back(line.substr(2)); // TODO 항목 추가
                } else if (line.find("p") == 0) {
                    items["p"].push_back(line.substr(2)); // PROGRESS 항목 추가
                } else if (line.find("d") == 0) {
                    items["d"].push_back(line.substr(2)); // DONE 항목 추가
                }
            }
            fin.close();
        }
    }

    // 항목 이동 함수
    void itemMove (std::string from, std::string to, int itemIndex) {
        std::string selItem = items[from].at(itemIndex-1); // 항목 선택
        itemDelete(from, itemIndex); // 항목 삭제
        itemAdd(to, selItem); // 항목 추가
    }

    // 항목 강조 표시 함수
    void hilight (std::string choice, int i) {
        std::string currentItem = "";
        //if (items[choice].size() > i) {
        if (items[choice].size() >= static_cast<size_t>(i)) {
            currentItem = items[choice][i];
        }
        if (currentItem.find("+") != 0) {
            printf(" | %2i %-17s | ", i + 1, currentItem.c_str()); // 항목 출력
        } else {
            printf(" | %2i \033[31m%-17s\033[0m | ", i + 1, currentItem.substr(2).c_str()); // 강조된 항목 출력
        }
    }

    // Kanban 보드 표시 함수
    void box(std::string choice = "t", int size = 9) {
        std::string border = " +----------------------+ ";

        if (mymap.count(choice) == 0) {
            if (choice == "all" || choice == "a") {
                std::cout << "       \033[31mo\033[0m TODO                      ";
                std::cout << " \033[33mo\033[0m PROGRESS                   " "\033[32mo\033[0m DONE\n";
                std::cout << border << "  " << border << "  " << border << "\n";
                for (int i = 0; i < size; i++) {
                    hilight("t",i); // TODO 항목 표시
                    printf("  ");
                    hilight("p",i); // PROGRESS 항목 표시
                    printf("  ");
                    hilight("d",i); // DONE 항목 표시
                    printf("\n");
                }
                std::cout << border << "  " << border << "  " << border << "\n";
            } else {
                std::cout << ERROR << "Error: invalid choice '" << choice << "'\n" << RESET; // 에러 메시지
            }
        } else {
            std::cout << "        " << mymap[choice] << "\n";
            std::cout << border << "\n";
            for (int i = 0; i < size; i++) {
                hilight(choice,i); // 특정 리스트 항목 표시
                printf("\n");
            }
            std::cout << border << "\n";
        }
    }

    // 인터랙티브 메뉴 함수
    void menu() {
        std::string choice = "";
        int size = 9;
        while (true) {
            box("a", size); // Kanban 보드 표시
            std::cout << "\nSelect t, p, d, a for all, q to quit\n";
            std::cin >> choice;
            if (choice == "q") break;
            if (choice == "t" || choice == "p" || choice == "d") {
                std::cout << "Add item: ";
                std::string item = "";
                std::cin >> item;
                itemAdd(choice,item); // 항목 추가
            } else if (choice == "a") {
                std::string subchoice;
                std::cout << "Remove item from which list (t,p,d): ";
                std::cin >> subchoice;
                if (subchoice == "t" || subchoice == "p" || subchoice == "d") {
                    int itemIndex = 0;
                    std::cout << "Enter item number to remove: ";
                    std::cin >> itemIndex;
                    itemDelete(subchoice, itemIndex); // 항목 삭제
                } else {
                    std::cout << ERROR << "Invalid list selected!" << RESET; // 에러 메시지
                }
            }
        }
    }
};

int main(int argc, char* argv[]) {
    popl::OptionParser op("Allowed options");
    auto help_option = op.add<popl::Switch>("h", "help", "produce help message");
    auto verbose_option = op.add<popl::Switch>("v", "verbose", "print more details");
    auto menu_option = op.add<popl::Switch>("m", "menu", "interactive menu mode");
    auto file_option = op.add<popl::Value<std::string>>("f", "file", "items file");

    op.parse(argc, argv);
    if (help_option->is_set()) {
        std::cout << op << "\n";
        return 0;
    }

    bool verbose = verbose_option->is_set();
    bool menu = menu_option->is_set();
    std::string itemsfile = "";
    if (file_option->is_set()) {
        itemsfile = file_option->value();
    }

    PexBan pexban(verbose, itemsfile);

    pexban.itemLoad();

    if (menu) {
        pexban.menu();
    }

    std::vector<std::string> pos_args = op.non_option_args();
    if (pos_args.size() >= 1) {
        std::string subcmd = pos_args.at(0);
        if (subcmd == "add") {
            if (pos_args.size() >= 3) {
                std::string list = pos_args.at(1);
                std::string item = pos_args.at(2);
                pexban.itemAdd(list,item);
            } else {
                std::cout << pexban.getError() << "Error: missing list or item name\n" << pexban.getReset();
            }
        } else if (subcmd == "del") {
            if (pos_args.size() >= 3) {
                std::string list = pos_args.at(1);
                int itemIndex = std::stoi(pos_args.at(2));
                pexban.itemDelete(list,itemIndex);
            } else {
                std::cout << pexban.getError() << "Error: missing list or item index\n" << pexban.getReset();
            }
        } else if (subcmd == "move") {
            if (pos_args.size() >= 4) {
                std::string from = pos_args.at(1);
                std::string to = pos_args.at(2);
                int itemIndex = std::stoi(pos_args.at(3));
                pexban.itemMove(from,to,itemIndex);
            } else {
                std::cout << pexban.getError() << "Error: missing from, to or item index\n" << pexban.getReset();
            }
        } else if (subcmd == "list") {
            std::string choice = "t";
            if (pos_args.size() >= 2) {
                choice = pos_args.at(1);
            }
            pexban.box(choice);
        }
    }
    
    pexban.itemSave();
}
