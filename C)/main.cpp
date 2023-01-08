#include <iostream>
#include <fstream>  
#include <queue>

struct Box{
    std::string name;
    std::queue<std::string> items;
    std::queue<Box> inside;

    Box() : name(""), items(), inside() {};
    Box(const std::string& name,  const std::queue<std::string> items, const std::queue<Box> inside) : name(name), items(items), inside(inside) {};
};

void doStuff(std::fstream& f){
    int b;
    f >> b;

    std::cout << b << std::endl;
    Box mainBox;

    std::string temp;
    int n;
    f >> temp;
    mainBox.name = temp;
    f >> n;
    for(std::size_t i = 0; i < n; ++i){
        f >> temp;
        mainBox.items.push(temp);
    }

    f >> n;
    for(std::size_t i = 0; i < n; ++i){
        f >> temp;
        Box newBox;
        newBox.name = temp;
        mainBox.inside.push(newBox);
    }


    while(!mainBox.items.empty()){
        std::cout << mainBox.items.front() << " ";
        mainBox.items.pop();
    }
    std::cout << std::endl;

    while(!mainBox.inside.empty()){
        std::cout << mainBox.inside.front().name << " ";
        mainBox.inside.pop();
    }
    std::cout << std::endl;


}

int main(){
    std::fstream file("boxesList.txt");
    doStuff(file);
    file.close();
}