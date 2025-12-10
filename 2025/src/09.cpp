/**
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./09.out <path/to/puzzle.txt> <part>" << std::endl;
        std::cout << "       <path/to/puzzle>: path from cwd to puzzle" << std::endl;
        std::cout << "       <part>: 1 or 2" << std::endl;
        exit(1);
    }

    int part = std::stoi(argv[2]);
    if (!(part == 1 || part == 2))
    {
        std::cerr << "Invalid part: " << part << std::endl;
        exit(1);
    }

    std::fstream infile(argv[1]);
    if (!infile)
    {
        std::cerr << "Error: unable to read source file: " << argv[1] << std::endl;
        exit(1);
    }

    std::vector<std::pair<long,long>> points;
    std::pair<long,long> p;
    long x,y;
    char comma;
    while (infile >> x >> comma >> y)
    {
        p = {x,y};
        points.emplace_back(p);
    }

    if (part == 1)
    {
        long max_area = 0;
        long area;
        for (int i=0; i<points.size()-1; ++i)
        {
            for (int j=i+1; j<points.size(); ++j)
            {
                area = (points[i].first - points[j].first + 1) * (points[i].second - points[j].second + 1);
                if (abs(area) > max_area) max_area = abs(area);
            }
        }

        std::cout << "The maximum area is " << max_area << std::endl;
    }

    return 0;
}