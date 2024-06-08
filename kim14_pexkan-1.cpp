#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class PexBan{
private:
	std::map<std::string,std::vector<std::string>> items;
	std::map<std::string, std::string> mymap;
public:	
	PexBan(){
		mymap["t"] = "TODO";
		mymap["p"] = "PROGRESS";
		mymap["d"] = "DONE";
		mymap["a"] = "ALL";
	};

	void box (std::string choice = "t", int size = 9) {

		if (mymap.count(choice) == 0) {
			//std::cout << "invalid choice '" << choice << "'\n";
		} else if (choice == "a") {
			std::cout << "        " << mymap["t"] << "                 " << mymap["p"] << "                 " << mymap["d"] << "\n";
			std::cout << " +-----------------+    +-----------------+    +-----------------+\n";
			for (int i = 0; i < size; i++)	{
				std::cout << " | " << i+1 << "               " << "|    "<< "| " << i+1 << "               " << "|    "<< "| " << i+1 << "               " << "|\n";
				
			}
			std::cout << " +-----------------+    +-----------------+    +-----------------+\n";
		}
		else {
			std::cout << "             " << mymap[choice] << "";
			std::cout << "\n +--------------------+\n";
			std::string currentItem = ""; // placeholder for current item
			
			for (int i = 0; i < size; i++)	{
				//std::cout << " | " << i+1 << "               " << "|\n";
				if (i < items[choice].size()) {
					currentItem = items[choice][i];
				} else {
					currentItem = "";
				}
				printf(" | %i %-16s |\n", i+1, currentItem.c_str()); // %-16s는 16자리를 확보하고 왼쪽 정렬하라는 뜻
				//std::cout << " | " << currentItem << "               " << "|\n";
			}
			std::cout << " +--------------------+\n";
		}

		
	}
	
	void deleteItem (std::string list, int index) {
		if (mymap.count(list) == 1) {
			if (index > 0 && index <= items[list].size()) {
				items[list].erase(items[list].begin() + index - 1);
			} else {
				std::cout << "invalid index '" << index << "'\n";
			}
		} else {
			std::cout << "invalid list '" << list << "'\n";
		}
	}

	void itemAdd (std::string list, std::string item) {
        std::cout << "list: '" << list << "' item: '" << item << "'" << std::endl;
		if (mymap.count(list) == 1){ // list는 t,p,d,a 중 하나임. 먼저 받는 것
			items[list].push_back(item);
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
			std::cout << "    \033[32md\033[0m: delete item\n";
			std::cout << "    \033[32ms\033[0m: set board size\n" ;
			std::cout << "\033[32mPlease enter your choice:\033[0m" ;
			
			std::cin >> choice;
			if (choice == "q")	{
				break;
			} else if (choice == "s") {
				std::cout << " \033[32mEnter board size:\033[0m ";
				std::cin >> size;
			} else if (choice == "ad") {
				std::cout << "Enter item (list-abbreviation item name): ";
                std::string in; // 사용자의 입력을 저장할 스트링 in을 선언
                std::cin.ignore(); // 이미 들어가있떤 입력을 지우고
                std::getline(std::cin,in); // 사용자의 입력을 받아서 in에 저장
                std::cout << in; // 사용자의 입력을 출력
                itemAdd(in.substr(0,1),in.substr(2)); // 사용자의 입력을 itemAdd 함수에 넣어서 실행
			} else if (choice == "d") {
				std::cout << "Enter list and index (list-abbreviation index): ";
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


int main(int argc, char **argv) {
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