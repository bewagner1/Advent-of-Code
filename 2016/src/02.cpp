
#include <iostream>
#include <fstream>
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
    const int numpad[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<int> code = {};
    int row = 1;
    int col = 1;
    char dir;

    while (infile.get(dir)) {
        if (dir == '\n') {
            code.emplace_back(numpad[row][col]);
            continue;
        }

        if      (dir == 'U' && row != 0) row--;
        else if (dir == 'L' && col != 0) col--;
        else if (dir == 'R' && col != 2) col++;
        else if (dir == 'D' && row != 2) row++;
    }
    code.emplace_back(numpad[row][col]);

    for (const auto& d : code) std::cout << d;
    std::cout << std::endl;
}


void part_two(std::fstream& infile)
{
    const char numpad[5][5] = { {'_', '_', '1', '_', '_'},
                                {'_', '2', '3', '4', '_'},
                                {'5', '6', '7', '8', '9'},
                                {'_', 'A', 'B', 'C', '_'},
                                {'_', '_', 'D', '_', '_'}
                              };
    std::vector<char> code = {};
    int row = 2;
    int col = 0;
    char dir;

    while (infile.get(dir)) {
        if (dir == '\n') {
            code.emplace_back(numpad[row][col]);
            continue;
        }

        if      (dir == 'U' && row != 0 && numpad[row - 1][col] != '_') row--;
        else if (dir == 'L' && col != 0 && numpad[row][col - 1] != '_') col--;
        else if (dir == 'R' && col != 4 && numpad[row][col + 1] != '_') col++;
        else if (dir == 'D' && row != 4 && numpad[row + 1][col] != '_') row++;

    }
    code.emplace_back(numpad[row][col]);

    for (const auto& d : code) std::cout << d;
    std::cout << std::endl;
}