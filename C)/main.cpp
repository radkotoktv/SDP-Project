#include <iostream>
#include <fstream>  
#include <vector>
#include <queue>

class Box{
private:
    std::string name;
    std::vector<std::string> items;
    std::vector<Box*> children;
    int numberOfChildren;

public:
    Box(std::string name) : name(name) {};

    void addChild(Box* child){
        this->children.push_back(child);
    }

    void addItem(std::string item){
        this->items.push_back(item);
    }

    const std::string getName() const {
        return this->name;
    }

    void setNumberOfChildren(int s){
        this->numberOfChildren = s;
    }

    std::vector<std::string> getItems() const{
        return this->items;
    }

    std::vector<Box*> getChildren() const{
        return this->children;
    }

    const int getNumberOfChildren() const{
        return this->numberOfChildren;
    }

};

void printTree(const Box& root){
    std::cout << root.getName() << std::endl;
    for(const Box* child : root.getChildren()){
        printTree(*child);
    }
}

void clean(Box* root){
    for(Box* child : root->getChildren()){
        clean(child);
    }
    delete root;
}

void doStuff(std::fstream& f){
    int b;
    f >> b;

    std::string temp;
    int n;

    std::vector<Box*> arr;

    for(std::size_t j = 0; j < b; ++j){ // makes all the boxes;
        f >> temp; // the name of the box;
        arr.push_back(new Box(temp));

        f >> n; // the amount of items in the box;
        for(std::size_t i = 0; i < n; ++i){ // adds the items in the box;
            f >> temp;
            arr.back()->addItem(temp);
        }

        f >> n; // the amount of other boxes in the box;
        arr.back()->setNumberOfChildren(n); // sets the current box's number of children (rofl explanation);
        for(std::size_t i = 0; i < n; ++i){ // skips the names of the inner boxes;
            f >> temp;
        }
    }


//print all boxes (for testing purposes);
    for(std::size_t asd = 0; asd < b; ++asd){
        std::cout << "Name: " << arr[asd]->getName() << std::endl;
        std::cout << "Items: ";
        for(std::size_t bcd = 0; bcd < arr[asd]->getItems().size(); ++bcd){
            std::cout << arr[asd]->getItems()[bcd] << " ";
        }
        std::cout << std::endl;
        std::cout << "Children: ";
        for(std::size_t bcd = 0; bcd < arr[asd]->getChildren().size(); ++bcd){
            std::cout << arr[asd]->getChildren()[bcd] << " ";
        }
        std::cout << std::endl;
        std::cout << "Amount of children: " << arr[asd]->getNumberOfChildren() << std::endl;
        std::cout << std::endl << "---------------------" << std::endl;
    }

}

int main(){
    std::fstream file("boxesList.txt");
    doStuff(file);
    file.close();
}