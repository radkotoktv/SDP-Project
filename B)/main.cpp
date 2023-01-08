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

    friend bool operator < (const Pair& first, const Pair& second);
};

bool operator < (const Pair& first, const Pair& second) {
    return first.index < second.index;
}

struct Edge{
    Pair from;
    Pair to;
    int time;

    friend bool operator < (const Edge& first, const Edge& second);
    friend bool operator != (const Edge& first, const Edge& second);
};

bool operator < (const Edge& first, const Edge& second) {
    return first.time < second.time;
}

bool operator != (const Edge& first, const Edge& second){
    return first.time != second.time;
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

void Dijkstra(std::vector<Edge>* graph, int k, Pair from, Pair to){ // k - the number of nodes in the graph;
    int* shortestPath = new int[k];

    shortestPath[from.index] = 0;
    for(std::size_t i = 1; i < k; ++i){
        shortestPath[i] = 99999;
    }

    std::priority_queue<Edge> pq;
    while (!graph[from.index].empty()) {
        pq.push(graph[from.index].back());
        graph[from.index].pop_back();
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

    for(std::size_t i = 0; i < k; ++i){
        std::cout << i << " " << shortestPath[i] << std::endl;
    }

    delete[] shortestPath;
}

Node<std::string>* algorithm(std::fstream& f){
    if (!f.is_open()){
        std::cout << "Problem while opening the file" << std::endl;
        return nullptr;
    }

    int k, r;
    f >> k >> r;

    std::vector<Edge>* graph = new std::vector<Edge>[k];
    std::vector<Edge>* tempGraph = new std::vector<Edge>[k];

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

    while(!froms.empty()){
        graph[froms.front().index].push_back({froms.front(), tos.front(), times.front()});
        graph[tos.front().index].push_back({tos.front() ,froms.front(), times.front()});
        
        tempGraph[froms.front().index].push_back({froms.front(), tos.front(), times.front()});
        tempGraph[tos.front().index].push_back({tos.front() ,froms.front(), times.front()});
        
        froms.pop();
        tos.pop();
        times.pop();
    }

    int minutes;
    f >> minutes;


    //Dijkstra to calculate the shortest path from "Railstation"(always with index 0) to every other node in the graph;
    int* shortestPath = new int[k]; // an array where we keep the times needed to reach the respective nodes;

    shortestPath[0] = 0;
    for(std::size_t i = 1; i < k; ++i){
        shortestPath[i] = 99999;
    }

    std::priority_queue<Edge> pq;  // a priority queue where we store the paths we can take from every node for the Dijkstra algorithm;
    while (!tempGraph[0].empty()) {
        pq.push(tempGraph[0].back());
        tempGraph[0].pop_back();
    }

    while(!pq.empty()){
        Edge c = pq.top();
        pq.pop();

        if(shortestPath[c.to.index] > shortestPath[c.from.index] + c.time){
            shortestPath[c.to.index] = shortestPath[c.from.index] + c.time;
            while (!tempGraph[c.to.index].empty()) {
                pq.push(tempGraph[c.to.index].back());
                tempGraph[c.to.index].pop_back();
            }            
        }
    }

    //the "shortestPath" array tells us the amount of time we need to get to every node from the start node;
    //ex. shortestPath[3] is the amount of time we need to get from node with index 0 to node with index 3;
    //in "Sofia.txt" that would be from "Railstation" to "DzhumayaSquare";

    std::priority_queue<Edge> paths;
    Node<std::string>* start = new Node<std::string>(locations[0].monument); // the start node should always be "Railstation", no matter the other destinations in the city;
    Node<std::string>* current = start;

    int i = 0;
    int currentPath = 0;
    Edge lastVisited;
    while(currentPath + shortestPath[i] <= minutes){
        int numberOfElements = 0;
        for(std::size_t j = 0; j < graph[i].size(); ++j){
            if(graph[i][j] != lastVisited){ // shouldn't go back the way it came, as that won't add to the amount of visited nodes in the graph;
                paths.push(graph[i][j]);
                numberOfElements++;
            }
        }

        while(numberOfElements > 1){ // leaves just the last element of the priority queue (a.k.a the smallest element in the queue);
            paths.pop();
            numberOfElements--;
        }

        if(currentPath + shortestPath[i] + paths.top().time <= minutes){ // checks if it can come back to "Railstation" after the next step;
            current->next = new Node<std::string>(locations[paths.top().to.index].monument);
            current = current->next;
            i = paths.top().to.index; // moves "i" to the next node;
            currentPath += paths.top().time;
            lastVisited = paths.top(); // saves the last visited node;
            paths.pop(); // empties the queue 
        }
        else break; // if it can't come back, it exits the loop at the current node;
    }


    delete[] shortestPath;
    delete[] graph;
    delete[] locations;

    return start;
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
    Node<std::string>* list = algorithm(file);
    file.close();
    printList(list);
    deleteList(list);
}