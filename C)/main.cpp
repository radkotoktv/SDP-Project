#include <iostream>
#include <fstream>  
#include <vector>

class Box{
    std::string name;
    std::vector<std::string> items;
    std::vector<Box> inside;

    Box(const std::string& name,  const std::vector<std::string> items, const std::vector<Box> inside) : name(name), items(items), inside(inside) {};
};

void doStuff(std::fstream& f){

}

int main(){
    std::fstream file("boxesList.txt");
    doStuff(file);
    file.close();
}