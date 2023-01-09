#include <iostream>
#include <fstream>  
#include <vector>
#include <queue>

class Box{
private:
    std::string name; // label of the box;
    std::vector<std::string> items; // items inside the box;
    std::vector<Box*> children; // other boxes inside the box;
    int numberOfChildren; // number of other boxes inside the box;

public:
    Box(std::string name) : name(name) {};

    void addChild(Box* child){
        this->children.push_back(child);
    }

    void addItem(std::string item){
        this->items.push_back(item);
    }

    void setNumberOfChildren(int s){
        this->numberOfChildren = s;
    }

    void removeChild(int index){
        std::queue<Box*> temp;
        int a = this->children.size() - index + 1;
        int b = a;
        while(a && !this->children.empty()){
            temp.push(this->children.back());
            this->children.pop_back();
            a--;
        }

        this->children.pop_back();

        while(b){
            this->children.push_back(temp.front());
            temp.pop();
            b--;
        }
    }

    const std::string getName() const {
        return this->name;
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

    friend void swap(Box& a, Box& b);
};

void clean(Box* root){ // deletes memory;
    for(Box* child : root->getChildren()){
        clean(child);
    }
    delete root;
}

void doStuff(std::fstream& f){
    int b;
    f >> b; // the total amount of boxes;

    std::string temp;
    int n;

    std::vector<Box*> arr; // a vector where we store the boxes completely separate of eachother;

    while(!f.eof()){
        f >> temp; // the name of the box;
        arr.push_back(new Box(temp));

        f >> n; // the amount of items in the box;
        for(std::size_t i = 0; i < n; ++i){ // adds the items in the box;
            f >> temp;
            arr.back()->addItem(temp);
        }

        f >> n; // the amount of other boxes in the box;
        arr.back()->setNumberOfChildren(n);

        for(std::size_t i = 0; i < n; ++i){ // skips the names of the inner boxes;
            f >> temp;
        }
    }

    int toAdd = 0;
    for(std::size_t i = 0; i < b; ++i){ // adds the smaller boxes into the bigger boxes;
        toAdd = i + 1; // the box is "arr[i + 1]" is always the first child that needs to be added to "arr[i]";
        for(std::size_t j = 0; j < arr[i]->getNumberOfChildren(); ++j){
            arr[i]->addChild(arr[toAdd]);
            toAdd += arr[i + 1]->getNumberOfChildren() + 1; // skips to the next box that needs to be added to "arr[i]";
        }
    }

    for(std::size_t i = 0; i < b; ++i){
        int temp = arr[i]->getChildren().size();
        for(std::size_t j = 0; j < temp; ++j){
            if(arr[i]->getChildren()[j]->getChildren().empty() && arr[i]->getChildren()[j]->getItems().empty()){ // removes an empty box with no boxes inside it;
                arr[i]->removeChild(j);
                arr[i]->setNumberOfChildren(arr[i]->getNumberOfChildren() - 1);
            }
            else if(arr[i]->getChildren()[j]->getChildren().size() == 1 && arr[i]->getChildren()[j]->getItems().empty()){
                arr[i]->addChild(arr[i]->getChildren()[j]->getChildren()[0]); // "0" because there if it's in the "if" statement there will be only 1 child; (a.k.a vnuka)
                arr[i]->removeChild(j);
            }
            
        }

    }

//print all boxes (for testing purposes);
//------------------------------------------------------------------------------------------------------------
    for(std::size_t asd = 0; asd < arr.size(); ++asd){
        std::cout << std::endl;
        std::cout << "Name: " << arr[asd]->getName() << std::endl;
        std::cout << "Items: ";
        for(std::size_t bcd = 0; bcd < arr[asd]->getItems().size(); ++bcd){
            std::cout << arr[asd]->getItems()[bcd] << " ";
        }
        std::cout << std::endl;
        std::cout << "Children: ";
        for(std::size_t bcd = 0; bcd < arr[asd]->getChildren().size(); ++bcd){
            std::cout << arr[asd]->getChildren()[bcd]->getName() << " ";
        }
        std::cout << std::endl;
        std::cout << "Amount of children: " << arr[asd]->getNumberOfChildren() << std::endl;
        std::cout << std::endl << "---------------------" << std::endl;
    }

//------------------------------------------------------------------------------------------------------------

    clean(arr[0]); // delete the memory;
}

int main(){
    std::fstream file("boxesList.txt");
    doStuff(file);
    file.close();
}