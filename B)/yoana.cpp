#include <iostream>
#include <queue>

struct Path
{
    int from;
    int to;
    int price;
    Path(int from, int to, int price) :from(from), to(to),price(price)
    {

    }
    bool operator<(const Path& a) const
    {
        return this->price > a.price;
    }
};


void algorytm(int graf[4][4]) {
    int sum = 0;
    int current = 0;

    std::priority_queue<Path> minTree;


    int used[4] = {0, 0, 0, 0};
    used[current] = 1;


    for (int i = 0; i < 4; i++) {
        if (graf[current][i] != 0) {

            minTree.push(Path(current, i, graf[current][i]));

        }
    }


    while (!minTree.empty()) {
        Path temp = minTree.top();
        minTree.pop();

        if (used[temp.to] == 1) {
            continue;
        }
        std::cout << temp.from << " " << temp.to << " " << temp.price << " " << std::endl;
        used[temp.to] = 1;
        current = temp.to;
        sum += temp.price;
        for (int i = 0; i < 4; i++) {
            if (graf[current][i] != 0) {

                minTree.push(Path(current, i, graf[current][i]));

            }

        }
    }
    return sum;

}

int main()
{
    int graf[4][4] = { {0,2,10,17},{1,0,8,0},{0,4,0,7},{2,2,5,0} };
    std::cout << algorytm(graf);
    return 0;
}