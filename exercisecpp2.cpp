#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

void box (std::string choice = "t", int size = 9) {
	std::map<std::string, std::string> mymap;
	mymap["t"] = "TODO";
	mymap["p"] = "PROGRESS";
	mymap["d"] = "DONE";
    mymap["a"] = "ALL";

	if (mymap.count(choice) == 0) {
		std::cout << "invalid choice '" << choice << "'\n";
	} else if (choice == "a") {
        std::cout << "        " << mymap["t"] << "                 " << mymap["p"] << "                 " << mymap["d"] << "\n";
        std::cout << " +-----------------+    +-----------------+    +-----------------+\n";
        for (int i = 0; i < size; i++)	{
            std::cout << " | " << i+1 << "               " << "|    "<< "| " << i+1 << "               " << "|    "<< "| " << i+1 << "               " << "|\n";
        }
        std::cout << " +-----------------+    +-----------------+    +-----------------+\n";
    }
    else {
		std::cout << "     " << mymap[choice] << "";
		std::cout << "\n +-----------------+\n";
		for (int i = 0; i < size; i++)	{
			std::cout << " | " << i+1 << "               " << "|\n";
			
		}
		
		std::cout << " +-----------------+\n";
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
		std::cout << "    \033[32ms\033[0m: set board size\n" ;
        std::cout << "\033[32mPlease enter your choice:\033[0m" ;
		
		std::cin >> choice;
		if (choice == "q")	{
			break;
		} else if (choice == "s") {
			std::cout << " \033[32mEnter board size:\033[0m ";
			std::cin >> size;
		} else {
			box(choice,size);
		}
	}	
	
}
int main(int argc, char **argv) {
	
	menu();
	
	return 0;
}
