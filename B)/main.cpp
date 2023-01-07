#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T& data, Node* next = nullptr) : data(data), next(next) {};
};

struct Pair{
    std::string monument;
    int index;
};

struct Edge{
    Pair from;
    Pair to;
    int time;

    friend bool operator < (const Edge& first, const Edge& second);
};

bool operator < (const Edge& first, const Edge& second) {
    return first.time < second.time;
}

void printGraph(std::vector<Edge>* graph, int vertices){
	for(std::size_t i = 0; i < vertices; ++i){
		std::cout << "Vertex " << i << " has edges to: ";
		for(const Edge& e: graph[i]){
			std::cout << e.to.monument << " (" << e.time << " minutes) ";
		}
		std::cout << std::endl;
	}
}

void printQueue(std::queue<Pair> queue){
    while(!queue.empty()){
        std::cout << queue.front().monument << "|" << queue.front().index << std::endl;
        queue.pop();
    }
    std::cout << std::endl;
}

void printQueue(std::queue<int> queue){
    while(!queue.empty()){
        std::cout << queue.front() << std::endl;
        queue.pop();
    }
    std::cout << std::endl;
}

bool isContained(Pair* arr, int arr_size, std::string elem){
    for(std::size_t i = 0; i < arr_size; ++i){
        if(arr[i].monument == elem) return true;
    }
    return false;
}

Node<std::string>* algorithm(std::fstream& f){
    if (!f.is_open()){
        std::cout << "Problem while opening the file" << std::endl;
        return nullptr;
    }

    int k, r;
    f >> k >> r;

    std::vector<Edge>* graph = new std::vector<Edge>[k];

    std::queue<Pair> froms;
    std::queue<Pair> tos;
    std::queue<int> times;
    Pair* locations = new Pair[k];

    int counter = 0;
    std::string first, second;
    int temp;
    for(std::size_t i = 0; i < r; ++i){
        f >> first >> second >> temp;
        if(!isContained(locations, k, first)){
            locations[counter] = {first, counter};
            counter++;
        }
        if(!isContained(locations, k, second)){
            locations[counter] = {second, counter};
            counter++;
        }
        for(int j = 0; j < k; ++j){
            if(locations[j].monument == first)
                froms.push({first, j});

            if(locations[j].monument == second)
                tos.push({second, j});
        }
        times.push(temp);

    }

    for(std::size_t i = 0; i < k; ++i){
        std::cout << locations[i].monument << "|" << locations[i].index << std::endl;
    }

    while(!froms.empty()){
        graph[froms.front().index].push_back({froms.front(), tos.front(), times.front()});
        graph[tos.front().index].push_back({tos.front() ,froms.front(), times.front()});
        froms.pop();
        tos.pop();
        times.pop();
    }

    //printGraph(graph, k);

    int minutes;
    f >> minutes;


    //Dijkstra moment;
    int* shortestPath = new int[k];
    
    shortestPath[0] = 0;
    for(std::size_t i = 1; i < k; ++i){
        shortestPath[i] = 99999;
    }

    std::priority_queue<Edge> pq;

    while (!graph[0].empty()) { // adds all connected to "Railstation" nodes to "pq";
        pq.push(graph[0].back());
        graph[0].pop_back();
    }

    while(!pq.empty()){
        Edge c = pq.top();
        pq.pop();

        if(shortestPath[c.to.index] > shortestPath[c.from.index] + c.time){
            shortestPath[c.to.index] = shortestPath[c.from.index] + c.time;
            while (!graph[c.to.index].empty()) {
                pq.push(graph[c.to.index].back());
                graph[c.to.index].pop_back();
            }            
        }
    }

    for (int i = 0; i < k ; ++i) {
        std::cout << i << " " << shortestPath[i] << std::endl;
    }


    delete[] shortestPath;
    delete[] graph;
    delete[] locations;

}

void printList(Node<std::string>* head){
    while(head->next){
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << head->data;
}

void deleteList(Node<std::string>* head){
    while(head->next){
        Node<std::string>* toDelete = head;
        head = head->next;
        delete toDelete;
    }
    delete head;
}

int main (){
    std::fstream file("Sofia.txt"); 
    algorithm(file);
    file.close();
}