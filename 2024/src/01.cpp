
#include <iostream>
#include <fstream>
#include <set>

void part_one(std::fstream& infile);
void part_two(std::fstream& infile);


int main(int argc, char* argv[])
{
    std::fstream infile(argv[2]);
    if (!infile) exit(1);

    if (std::stoi(argv[1]) == 1) part_one(infile);
    else if (std::stoi(argv[1]) == 2) part_two(infile);
    else exit(2);

    infile.close();

    return 0;
}


void part_one(std::fstream& infile)
{
    std::multiset<int> left;
    std::multiset<int> right;

    int l, r;
    while (infile >> l >> r) {
        left.insert(l);
        right.insert(r);
    }

    int dist = 0;
    auto lit = left.begin();
    auto rit = right.begin();
    while (lit != left.end()) {

        dist = dist + abs(*lit - *rit);

        ++lit;
        ++rit;
    }

    std::cout << dist << std::endl;
}


void part_two(std::fstream& infile)
{
    std::multiset<int> left;
    std::multiset<int> right;

    int l, r;
    while (infile >> l >> r) {
        left.insert(l);
        right.insert(r);
    }

    int sim_score = 0;
    for (auto it = left.begin(); it != left.end(); ++it) {
        sim_score = sim_score + *it * right.count(*it);
    }

    std::cout << sim_score << std::endl;
}