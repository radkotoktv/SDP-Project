#include <iostream>
#include <string>
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* skip;

    Node(const T& data, Node* next = nullptr, Node* skip = nullptr) : data(data), next(next), skip(skip) {}
};

Node<std::string>* toList(std::string* arr, std::size_t size) {
    if(!arr || !size)
        return nullptr;

    Node<std::string>* start = new Node<std::string>(arr[0]);
    Node<std::string>* current = start;

    for(std::size_t i = 1; i < size; ++i){
        current->next = new Node<std::string>(arr[i]);
        current = current->next;
    }

    return start;
}

void deleteList(Node<std::string>* lst) {
    while (lst) {
        Node<std::string>* toDelete = lst;
        lst = lst->next;
        delete toDelete;
    }
}

void makeSkips(Node<std::string>* head, std::string* arr1, std::string* arr2){
    if(!head || arr1 == nullptr || arr2 == nullptr)
        return;

    Node<std::string>* start = head;
    Node<std::string>* current = start;
    Node<std::string>* search = current;

    int i = 0;
    while(current->next){
        if(current->data == arr1[i]){
            while(search->data != arr2[i]){
                search = search->next;
            }
            current->skip = search;
            current = start;
            search = start;
            i++;
        }
        current = current->next;
    }
}

Node<std::string>* Journey(Node<std::string>* head, std::string* arr){
    if(!head)
        return nullptr;
    if(!arr)
        return head;


    Node<std::string>* search = head;
    Node<std::string>* current = head;

    Node<std::string>* newListHead = new Node<std::string>(head->data);
    Node<std::string>* newNode = newListHead;

    int i = 0;
    while(current->next){
        search = current;
        if(current->data == newListHead->data){
            i++;
            current = current->next;
        }
        else if(current->data == arr[i]){
            newNode->next = new Node<std::string>(current->data);
            i++;
            current = current->next;
            newNode = newNode->next;
        }
        else if(current->skip && current->skip->data == arr[i]){
            newNode->next = new Node<std::string>(current->skip->data);
            i++;
            current = current->skip;
            newNode = newNode->next;
        }
        else if(current->skip){
            while(search->data != arr[i] && search->data != current->skip->data){
                search = search->next;
            }
            if(search->data == current->skip->data){
                newNode->next = new Node<std::string>(current->skip->data);
                current = current->skip;
                newNode = newNode->next;
            }
            else {
                if(current->next->data == arr[i]){
                    i++;
                }
                newNode->next = new Node<std::string>(current->next->data);
                current = current->next;
                newNode = newNode->next;
            }
        }
        else {
            if(current->next->data == arr[i]){
                i++;
            }
            newNode->next = new Node<std::string>(current->next->data);
            current = current->next;
            newNode = newNode->next;
        }
    }
    if(current->data == arr[i]){
        newNode->next = new Node<std::string>(current->data);
    }

    return newListHead;
}

void printList(Node<std::string>* head) {
    while(head->next) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << head->data;
}

void printSkips(Node<std::string>* head){
    Node<std::string>* start = head;
    Node<std::string>* current = head;
    while(start->next){
        if(start->skip){
            std::cout << start->data << " ";
            std::cout << start->skip->data;
            std::cout << std::endl;
        }
        start = start->next;
    }
}

void printWholeList(Node<std::string>* head){
    Node<std::string>* start = head;
    Node<std::string>* current = start;
    while(start->next){
        current = start;
        std::cout << current->data << " ";
        while(current->skip){
            std::cout << current->skip->data << " ";
            current = current->skip;
        }
        std::cout << std::endl;
        start = start->next;
    }
    std::cout << start->data;
}
int main(){
    /*
    Sofia Plovdiv
    Plovdiv NovaZagora
    Dimitrovgrad NovaZagora
    StaraZagora Yambol
    NovaZagora Burgas
    */
    
    /*    //for actual use;
    int n;
    std::cout << "Please enter how many cities the train goes through: "; std::cin >> n;
    std::string* arr = new std::string[n];

    std::cout << "Please enter " << n << " cities: ";
    for(std::size_t i = 0; i < n; ++i){
        std::cin >> arr[i];
    }

    int k;
    std::cout << "Please enter the amount of cities that have a direct connection: "; std::cin >> k;
    std::string* first = new std::string[k];
    std::string* second = new std::string[k];

    std::cout << "Please enter " << k << " connections: ";
    for(std::size_t i = 0; i < k; ++i){
        std::cin >> first[i] >> second[i];
    }

    int j;
    std::cout << "Please enter the amount of cities that you have to visit: "; std::cin >> j;
    std::string* locations = new std::string[j];

    std::cout << "Please enter " << j << " cities: ";
    for(std::size_t i = 0; i < j; ++i){
        std::cin >> locations[i];
    }

    Node<std::string>* list = toList(arr, n);
    makeSkips(list, first, second);
    Node<std::string>* finalJourney = Journey(list, locations);

    std::cout << "The optimal route you can take is: ";
    printList(finalJourney);    

    delete[] arr;
    delete[] first;
    delete[] second;
    delete[] locations;
    deleteList(list);
    deleteList(finalJourney);
*/

    // for easier testing;
    std::string arr[9] = {"Sofia", "Pazardzhik", "Plovdiv", "Dimitrovgrad", "StaraZagora", "NovaZagora", "Yambol", "Karnobat", "Burgas"};
    std::string first[5] = {"Sofia", "Plovdiv", "Dimitrovgrad", "StaraZagora", "NovaZagora"};
    std::string second[5] = {"Plovdiv", "NovaZagora", "NovaZagora", "Yambol", "Burgas"};
    std::string locations[3] = {"Plovdiv", "StaraZagora", "Yambol"};
    Node<std::string>* list = toList(arr, 9);
    makeSkips(list, first, second);
    Node<std::string>* finalJourney = Journey(list, locations);
    printList(finalJourney);
    deleteList(list);
    deleteList(finalJourney);
}