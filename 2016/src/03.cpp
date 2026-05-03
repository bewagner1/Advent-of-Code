
#include <iostream>
#include <fstream>
#include <cmath>

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
    int num_possible = 0;
    int s1, s2, s3, m;

    while (infile >> s1 >> s2 >> s3) {

        m = std::max(std::max(s1, s2), s3);
        if (m < (s1 + s2 + s3 - m)) num_possible++;

    }

    std::cout << num_possible << std::endl;
}


void part_two(std::fstream& infile)
{
    int num_possible = 0;
    int l1, l2, l3;
    int m1, m2, m3;
    int r1, r2, r3;
    int m;

    while (infile >> l1 >> m1 >> r1 >> l2 >> m2 >> r2 >> l3 >> m3 >> r3) {

        m = std::max(std::max(l1, l2), l3);
        if (m < (l1 + l2 + l3 - m)) num_possible++;

        m = std::max(std::max(m1, m2), m3);
        if (m < (m1 + m2 + m3 - m)) num_possible++;

        m = std::max(std::max(r1, r2), r3);
        if (m < (r1 + r2 + r3 - m)) num_possible++;

    }

    std::cout << num_possible << std::endl;
}