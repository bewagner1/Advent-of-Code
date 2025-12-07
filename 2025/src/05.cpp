/**
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>


std::vector<std::pair<long,long>> merge_ranges(std::vector<std::pair<long,long>> ranges);


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./05.out <path/to/puzzle.txt> <part>" << std::endl;
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

    std::vector<std::pair<long, long>> ranges;
    std::string line;
    long dash, l, r;
    while (std::getline(infile, line))
    {
        if (line.empty()) break;
        dash = line.find('-');
        l = std::stol(line.substr(0, dash));
        r = std::stol(line.substr(dash + 1));

        ranges.emplace_back(l, r);
    }

    if (part == 1)
    {
        long id;
        size_t count = 0;
        while (std::getline(infile, line))
        {
            if (line.empty()) continue;
            id = std::stol(line);
            for (const std::pair<long, long>& p : ranges)
            {
                if (id >= p.first && id <= p.second) 
                {
                    count++;
                    break;
                }
            }
        }
        std::cout << "There are " << count << " fresh IDs" << std::endl;
    }
    infile.close();
    if (part == 1) return 0;

    std::vector<std::pair<long, long>> updated = merge_ranges(ranges);
    long total = 0;
    for (size_t i=0; i<updated.size(); i++) 
    {
        std::pair<long,long> curr = updated.at(i);
        total = total + 1 + curr.second - curr.first;
    }

    std::cout << "There are " << total << " possible fresh IDs" << std::endl;
    
    return 0;
}


std::vector<std::pair<long,long>> merge_ranges(std::vector<std::pair<long,long>> ranges)
{
    std::sort(ranges.begin(), ranges.end(), [](std::pair<long,long>& a, std::pair<long,long>& b) {return a.first < b.first;});
    std::vector<std::pair<long,long>> merged;
    merged.push_back(ranges.at(0));

    for (size_t i = 1; i < ranges.size(); i++) {

        std::pair<long,long>& last = merged.back();
        std::pair<long,long>& curr = ranges.at(i);

        if (curr.first <= last.second)
        {
            last.second = std::max(last.second, curr.second);
        } else {
            merged.push_back(curr);
        }
    }

    return merged;
}