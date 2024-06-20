#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>

class PexBan{
private:

	std::map<std::string,std::vector<std::string>> t_items;
	std::map<std::string,std::vector<std::string>> p_items;
	std::map<std::string,std::vector<std::string>> d_items;
	std::map<std::string, std::string> mymap;

public:	
	PexBan(){
		mymap["t"] = "TODO";
		mymap["p"] = "PROGRESS";
		mymap["d"] = "DONE";
		mymap["a"] = "ALL";
	};

	void box (std::string choice = "t", int size = 9) {

		std::string T_currentItem = ""; // placeholder for TODO 
		std::string P_currentItem = ""; // placeholder for PROGRESS
		std::string D_currentItem = ""; // placeholder for DONE

		if (mymap.count(choice) == 0) {
		} else if (choice == "a") {
			std::cout << "        " << mymap["t"] << "                 " << mymap["p"] << "                 " << mymap["d"] << "\n";
			std::cout << " +--------------------+ +--------------------  +--------------------+\n";
			
			for (int i = 0; i < size; i++) {

				//std::string T_currentItem = (i < t_items[choice].size()) ? t_items[choice][i] : "";
				//std::string P_currentItem = (i < p_items[choice].size()) ? p_items[choice][i] : "";
				//std::string D_currentItem = (i < d_items[choice].size()) ? d_items[choice][i] : "";

				if (i < t_items["t"].size()) {
					T_currentItem = t_items["t"][i];
				} else {
					T_currentItem = "";
				}

				if (i < p_items["p"].size()) {
					P_currentItem = p_items["p"][i];
				} else {
					P_currentItem = "";
				}

				if (i < d_items["d"].size()) {
					D_currentItem = d_items["d"][i];
				} else {
					D_currentItem = "";
				}

				printf(" | %i %-16s |", i+1, T_currentItem.c_str()); // TODO
				printf(" | %i %-16s |", i+1, P_currentItem.c_str()); // PROGRESS
				printf(" | %i %-16s |\n", i+1, D_currentItem.c_str()); // DONE
			}
			std::cout << " +--------------------+ +--------------------+ +--------------------+\n";
		}

		else {
			std::cout << "         " << mymap[choice] << "";
			std::cout << "\n +--------------------+\n";
			
			for (int i = 0; i < size; i++)	{
				if (choice == "t" && i < t_items[choice].size()) { 	// if choice is t, and i is less than the size of t_items[choice]
					T_currentItem = t_items[choice][i]; 			// then T_currentItem is equal to t_items[choice][i], it's same for others
				} else if (choice == "p" && i < p_items[choice].size()) {
					P_currentItem = p_items[choice][i];
				} else if (choice == "d" && i < d_items[choice].size()) {
					D_currentItem = d_items[choice][i];
				} else {
					T_currentItem = P_currentItem = D_currentItem = "";
				}
				
				if (choice == "t") {
					printf(" | %i %-16s |\n", i+1, T_currentItem.c_str()); // %-16s는 16자리를 확보하고 왼쪽 정렬하라는 뜻
				} else if (choice == "p") {
					printf(" | %i %-16s |\n", i+1, P_currentItem.c_str());  
				} else if (choice == "d") {
					printf(" | %i %-16s |\n", i+1, D_currentItem.c_str()); 
				}

				// printf(" | %i %-16s |\n", i + 1, (choice == "t" ? T_currentItem.c_str() : (choice == "p" ? P_currentItem.c_str() : D_currentItem.c_str())));
			}
			std::cout << " +--------------------+\n";
		}

		
	}
	
	void deleteItem (std::string list, int index) {
		if (mymap.count(list) == 1) {
			if (list == "t") {
				t_items[list].erase(t_items[list].begin() + index - 1);
			} else if (list == "p") {
				p_items[list].erase(p_items[list].begin() + index - 1);
			} else if (list == "d") {
				d_items[list].erase(d_items[list].begin() + index - 1);
			}
		} else {
			std::cout << "invalid list '" << list << "'\n";
		}
	}

	void itemAdd (std::string list, std::string item) {
        std::cout << "\nlist: '" << list << "' item: '" << item << "'" << std::endl;
		if(list == "t"){
			t_items[list].push_back(item);
		}else if (list == "p"){
			p_items[list].push_back(item);
		}else if (list == "d"){
			d_items[list].push_back(item);
		}
		else{
			std::cout << "invalid list '" << list << "'\n";
		}
	}
	

	void menu () {	
		std::string choice = "";
		int size = 9;
		while (true) {
			std::cout << "    \033[32mq\033[0m: quit application\n" ;
			std::cout << "    \033[32mt\033[0m: display TODO\n" ;
			std::cout << "    \033[32mp\033[0m: display PROGRESS\n" ;
			std::cout << "    \033[32md\033[0m: display DONE\n" ;
			std::cout << "    \033[32ma\033[0m: display full kanban\n";
			std::cout << "    \033[32mad\033[0m: enter item\n";
			std::cout << "    \033[32mde\033[0m: delete item\n";
			std::cout << "    \033[32ms\033[0m: set board size\n" ;
			std::cout << "\033[32mPlease enter your choice:\033[0m" ;
			
			std::cin >> choice;
			if (choice == "q")	{
				break;

			} else if (choice == "s") {
				std::cout << " \033[32mEnter board size:\033[0m ";
				std::cin >> size;

			} else if (choice == "ad") {
				std::cout << "Enter list and item: \n";
				std::cout << "ex) t first item\n";
                std::string in; 				// 사용자의 입력을 저장할 스트링 in을 선언
                std::cin.ignore(); 				// 이미 들어가있떤 입력을 지우고
                std::getline(std::cin,in); 		// 사용자의 입력을 받아서 in에 저장
                itemAdd(in.substr(0,1),in.substr(2)); // 사용자의 입력을 itemAdd 함수에 넣어서 실행

			} else if (choice == "de") {
				std::cout << "Enter list and index (list-abbreviation index): \n";
				std::cout << "ex) t first item\n";
				std::string in;
				std::cin.ignore();
				std::getline(std::cin,in);
				deleteItem(in.substr(0,1),std::stoi(in.substr(2)));
			} else {
				box(choice,size);
			}
		}	
		
	}
};

namespace pex {
	
    std::string get_home_directory() {
        // get home directory Unix
        const char* homeDir = getenv("HOME");
        // Get home directory on Windows (untested)
        const char* userProfile = getenv("USERPROFILE");
        std::string result = "";
        if (homeDir != nullptr) {
            result = homeDir;
        } else if (userProfile != nullptr) {
            result = userProfile;
        }
        return(result);
    }
};


int main(int argc, char **argv) {
	std::cout << "PEX Home: " << pex::get_home_directory() << std::endl;
	auto kanban = PexBan();
	kanban.itemAdd("t","first item");
	kanban.menu();

	return 0;
}

// compiling:
// g++ pexban.cpp -o pexban
// recording animated gif
// byzanz-record --duration=10 --x=10 --y=40 --width=400 \
//  height=400 out.gif & ./pexband

