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
class PexBan {
private:
    std::map<std::string, std::vector<std::string>> items;
    std::map<std::string, std::string> mymap;
    fs::path itemFile;
    const std::string ERROR = "\033[31m";
    const std::string RESET = "\033[0m";
    bool verbose = false;

public:
    PexBan(bool verbose = false, std::string itemsfile = "") {
        this->verbose = verbose;
        mymap["t"] = "TODO";
        mymap["p"] = "PROGRESS";
        mymap["d"] = "DONE";
        std::string home = pex::get_home_directory();
        // Create the folder path
        fs::path homeDir(home);
        fs::path pexbanPath = homeDir / ".config" / "pexban";
        fs::path itemFile;
        if (itemsfile != "") {
            itemFile = fs::path(itemsfile);
        } else {
             itemFile =  pexbanPath / "items.txt";
        }
        if (verbose) {
            std::cout << itemFile << std::endl;
        }
        if (!fs::is_directory(pexbanPath)) {
            //std::cout << pexbanPath << std::endl;
            fs::create_directory(pexbanPath);
        }
        this->itemFile = itemFile;

    }
    void itemAdd(std::string list, std::string item) {
        if (mymap.count(list) == 1) {
            items[list].push_back(item);
        }
        if (verbose) {
            std::cout << "list: '" << list << "' add item: '" << item << "'"
                  << std::endl;
        }
    }
    void itemDelete(std::string list, int itemIndex) {
        if (mymap.count(list) == 1) {
            if (items[list].size() >= itemIndex) {

                items[list].erase(items[list].begin() + itemIndex - 1);
                if (verbose) {
                    std::cout << "List: '" << list << "' deleted item: '" << itemIndex << "'"
                          << std::endl;
                }

            } else {
                // errors should be shown:
                std::cout << ERROR << "Error: List " << list << " only contains " << items[list].size() << 
                      " items!\n" << RESET;
            }
        } else {
            // errors should be shown:
            std::cout << ERROR << "Error: List " << list << " does not exists! There are only t, p or d lists!\n" <<
                  RESET;
            
        }
    }
    void itemSave () {
        std::ofstream fout;
        fout.open(itemFile);
        // hw03
        // TODO: remove duplicates

        for (const auto& [key, its] : items) {
            for (auto item : its) {
                fout << key << " " << item << "\n";
            }
        }
        fout.close();
    }
    // hw03
    void itemLoad () {
        std::ifstream fin;
        std::string line;
        if (fs::exists(itemFile)) {
            fin.open(itemFile);
            while (std::getline(fin,line)) {
                if (verbose) {
                    std::cout << line << std::endl;
                }
                if (line.find("t") == 0) {
                    items["t"].push_back(line.substr(2));
                } else if (line.find("p") == 0) {
                    items["p"].push_back(line.substr(2));
                } else if (line.find("d") == 0) {
                    items["d"].push_back(line.substr(2));
                }
            }
            fin.close();
        }
    }
    void itemMove (std::string from, std::string to, int itemIndex) {
        std::string selItem = items[from].at(itemIndex-1);
        itemDelete(from, itemIndex);
        itemAdd(to,selItem);

    }
    void hilight (std::string choice, int i) {
        std::string currentItem = "";
        if (items[choice].size() > i) {
            currentItem = items[choice][i];
        }
        if (currentItem.find("+") != 0) {
            printf(" | %2i %-17s | ", i + 1, currentItem.c_str());
        } else {
            printf(" | %2i \033[31m%-17s\033[0m | ", i + 1, currentItem.substr(2).c_str());
        }

    }
    void box(std::string choice = "t", int size = 9) {
        std::string border = " +----------------------+ ";

        if (mymap.count(choice) == 0) {
            if (choice == "all" || choice == "a") {
                std::cout << "       \033[31mo\033[0m TODO                      ";
                std::cout << " \033[33mo\033[0m PROGRESS                   "
                          "\033[32mo\033[0m DONE\n";
                std::cout << border << "  " << border << "  " << border << "\n";
                for (int i = 0; i < size; i++) {
                    hilight("t",i); // TODO
                    printf("  ");
                    hilight("p",i); // PROGRESS
                    printf("  ");
                    hilight("d",i); // DONE
                    printf("\n");
                }
                std::cout << border << "  " << border << "  " << border << "\n";
            } else {
                std::cout << ERROR << "Error: invalid choice '" << choice << "'\n" << RESET;
            }
        } else {
            std::cout << "        " << mymap[choice] << "\n";
            std::cout << border << "\n";
            for (int i = 0; i < size; i++) {
                hilight(choice,i);
                printf("\n");
            }

            std::cout << border << "\n";
        }
    }
    void menu() {
        std::string choice = "";
        int size = 9;
        while (true) {
            std::cout << "\n\033[32mPlease select \033[0m ";
            std::cout << "\033[32mq\033[0m(uit), ";
            std::cout << "\033[32mt\033[0m(odo), ";
            std::cout << "\033[32mp\033[0m(progress), ";
            std::cout << "\033[32md\033[0m(one), ";
            std::cout << "\033[32ma\033[0m(ll), ";
            std::cout << "\033[32mad\033[0m(d items), ";
            std::cout << "\033[32mde\033[0m(l items), ";
            std::cout << "\033[32mm\033[0m(ove items), ";

            std::cout << "\033[32ms\033[0m(et size): ";

            std::cin >> choice;
            if (choice == "q") {
                break;
            } else if (choice == "s") {
                std::cout << " \033[32mEnter board size:\033[0m ";
                std::cin >> size;
            } else if (choice == "ad") {
                std::cout << "Enter item (list-abbreviation item-name): ";
                std::string in;
                std::cin.ignore();          // clear remaining chars
                std::getline(std::cin, in); // get line with spaces
                std::cout << in;
                itemAdd(in.substr(0, 1), in.substr(2));
            } else if (choice == "de") {
                std::cout << "Enter item (list-abbreviation item-index): ";
                std::string in;
                std::cin.ignore();          // clear remaining chars
                std::getline(std::cin, in); // get line with spaces
                std::cout << in;
                itemDelete(in.substr(0, 1), std::stoi(in.substr(2)));
            } else if (choice == "m") {
                std::cout << "Enter item (from-list to-list item-index): ";
                std::string in;
                std::cin.ignore();          // clear remaining chars
                std::getline(std::cin, in); // get line with spaces
                std::cout << in;
                std::string item = items[in.substr(0,1)].at(std::stoi(in.substr(4))-1);
                std::cout << "item is: " << item << " idx1 '" << in.substr(0, 1) << "'\n" ;
                itemMove(in.substr(0, 1),in.substr(2, 1), std::stoi(in.substr(4)));
            } else {
                box(choice, size);
            }
        }
    }
};

static const char HELP[] =
R"(Arguments:
   ITEMSFILE  - if not given, per default the file 
                ~/.config/pexban/items.txt is used

Author: Detlef Groth, University of Potsdam, Germany (2024)

Contact: dgroth(at)uni-potsdam(dot).de

License: MIT
)";

int main(int argc, char **argv) {
    popl::OptionParser pexapp("Pexban Kanban Application\nUsage: pexban [options] ?itemsfile?\nOptions");
    auto help   = pexapp.add<popl::Switch>("h", "help",
                                           "produce help message");
    auto interactive   = pexapp.add<popl::Switch>("i", "interactive",
                         "start interactive menu");
    auto verbose   = pexapp.add<popl::Switch>("v", "verbose",
                         "verbose mode with messaging");
    auto add = pexapp.add<popl::Value<std::string>>("a", "add",
               "add items to list --add 't|p|d item-name'","");
    auto del = pexapp.add<popl::Value<std::string>>("d", "delete",
               "add items to list --delete 't|p|d item-index'","");
    auto move = pexapp.add<popl::Value<std::string>>("m", "move",
               "add items to list --move 't|p|d(from) t|p|d(to) from-item-index'","");
    pexapp.parse(argc, argv);
    int i = 0;
    std::string itemsfile = "";
    // wrong option check
    for (const auto& unknown_option: pexapp.unknown_options()) {
        std::cout << "Error: unknown option '" << unknown_option << "'!\n";
        std::cout << "Use --help to show valid options!\n" ;
        return(0);
    }
    // filename given?
    for (const auto& non_option_arg: pexapp.non_option_args()) {
        if (i == 0) {
            if (std::regex_match(non_option_arg,std::regex(".+\\.txt"))) {
                std::cout << "non_option_args: " << non_option_arg << "\n";
                itemsfile = non_option_arg;
            } else {
                std::cout << "Error: Items file '" << non_option_arg << "' does not end with extension txt!\n";
            }
        }
        i=i+1;
    }
              
    if (help->is_set()) {
        std::cout << pexapp << "\n";
        std::cout << HELP;
        return(0);
    }
    bool v = false;
    if (verbose->is_set()) {
        v = true;
    }
        
    auto pex = PexBan(v,itemsfile);
    //pex.itemAdd("t", "PEX Homework");
    //pex.itemAdd("t", "MLB Quiz");
    pex.itemLoad();
    if (interactive->is_set()) {
        pex.menu();
        pex.itemSave();
    } else if (add->is_set()) {
        if (std::regex_match(add->value(),std::regex("[tpd] .+"))) {
            std::cout << "setting: " << add->value() << "\n";
            pex.itemAdd(add->value().substr(0,1),add->value().substr(2));
            pex.itemSave();
            pex.box("all");
        } else {
            std::cout << "Error: item add syntax should be: --add 't|p|d item-name'!\n";
        }
    } else if (del->is_set()) {
        if (std::regex_match(del->value(),std::regex("[tpd] [0-9]+"))) {
            std::cout << "deleting: " << del->value() << "\n";
            pex.itemDelete(del->value().substr(0,1),std::stoi(del->value().substr(2)));
            pex.itemSave();
            pex.box("all");
        } else {
            std::cout << "Error: item add syntax should be: --delete 't|p|d item-index'!\n";
        }
    } else if (move->is_set()) {
        if (std::regex_match(move->value(),std::regex("[tpd] [tpd] [0-9]+"))) {
            if (verbose) {
                std::cout << "moving: " << move->value() << "\n";
            }
            pex.itemMove(move->value().substr(0,1),
                         move->value().substr(2,1),
                         std::stoi(move->value().substr(4)));
            pex.itemSave();            
            pex.box("all");
        } else {
            std::cout << "Error: item move syntax should be: --move 'from to from-item-index'!\n";
            std::cout << "          Where from and to are either lists t, p or d!\n";
        }
    } else {
        pex.box("all");
        std::cout << "Run: " << argv[0] << " --help to see help!\n";
    }
    return 0;
}
