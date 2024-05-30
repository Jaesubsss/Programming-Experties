#include <iostream>
#include <map>
// nhello.cpp - compile with: "g++ -o nhello nhello.cpp"

// task 1

int looper(int size){
    for (int i = 0; i < size; i++) {
        std::cout << "Hello, World!" << std::endl;
    }
    return 0;
}

void task1(){
    using namespace std;
    int n = 10;
    cout << "Enter the number of times you want to print Hello, World! : ";
    cin >> n;
    looper(n);
}

// task 4
#include <map>

void box(std::string choice = "t", int size = 9){
    std::map<std::string, std::string> mymap;
    mymap["t"] = "TODO";
    mymap["p"] = "PROGRESS";
    mymap["d"] = "DONE";
    if (mymap.count(choice) == 0){
        std::cout << "Invalid choice" << std::endl;
        return;
    }
    std::cout << "       " << mymap[choice] << "\n";
    std::cout << "+--------------------+\n";
    for (int i = 0; i < size   ; i++) {
        std::cout << "|" << i+1 << "                   |" << std::endl;
    }
    std::cout << "+--------------------+\n";

}

void quit(){
    using namespace std;
    cout << "Goodbye!" << endl;
    exit(0);
}

void drawKanban(){
    using namespace std;
    cout << "To Do" << endl;
    box();
    for (int i = 0; i < 9   ; i++) {
        cout << "|" << i+1 << "                   |" << endl;
    }
    box();
}

void menu(){
    using namespace std;
    int size = 9;
    cout << "Menu" << endl;
    string choice = "";
    while(true){
        cout << "q - Quit            " << endl;
        cout << "a - Add task        " << endl;
        cout << "d - Delete task     " << endl;
        cout << "m - Move task       " << endl;
        cout << "s - Show kanban     " << endl;
        cin >> choice;
    }   
    if (choice == "q"){
        quit();
    }
    else if (choice == "s") {
        cin >> size;
    }
    

}


void toDo(){
    using namespace std;
}

int main() {
    drawKanban();
    menu();
    return 0;
}