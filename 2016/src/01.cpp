
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

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
    int pos[] = {0, 0};
    char facing = 'n';
    char dir, c;
    int dist;

    while (infile >> dir >> dist) {

        if      (facing == 'n') dir == 'R' ? facing = 'e' : facing = 'w';
        else if (facing == 'e') dir == 'R' ? facing = 's' : facing = 'n';
        else if (facing == 's') dir == 'R' ? facing = 'w' : facing = 'e';
        else if (facing == 'w') dir == 'R' ? facing = 'n' : facing = 's';
        else    exit(3);

        if      (facing == 'n') pos[1] += dist;
        else if (facing == 'e') pos[0] += dist;
        else if (facing == 's') pos[1] -= dist;
        else if (facing == 'w') pos[0] -= dist;
        else    exit(4);

        infile >> c; // Skip over comma and space
    }

    std::cout << abs(pos[0]) + abs(pos[1]) << std::endl;
}


void part_two(std::fstream& infile)
{
    std::set<std::pair<int, int>> seen;
    std::pair<int, int> pos = {0, 0};
    seen.insert(pos);
    char facing = 'n';
    char dir, c;
    int dist;

    while (infile >> dir >> dist) {

        if      (facing == 'n') dir == 'R' ? facing = 'e' : facing = 'w';
        else if (facing == 'e') dir == 'R' ? facing = 's' : facing = 'n';
        else if (facing == 's') dir == 'R' ? facing = 'w' : facing = 'e';
        else if (facing == 'w') dir == 'R' ? facing = 'n' : facing = 's';
        else    exit(3);

        for (int i = 0; i < dist; ++i) {
            if      (facing == 'n') pos.second++;
            else if (facing == 'e') pos.first++;
            else if (facing == 's') pos.second--;
            else if (facing == 'w') pos.first--;
            else    exit(4);

            if (seen.count(pos)) {
            std::cout << abs(pos.first) + abs(pos.second) << std::endl;
            return;
            } else {
                seen.insert(pos);
            }
        }

        infile >> c; // Skip over comma and space
    }
}