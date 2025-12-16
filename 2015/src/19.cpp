/**
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <limits>


void part1(std::map<std::string, std::vector<std::string>>& dict, std::string& line);
void part2(std::map<std::string, std::vector<std::string>>& dict, std::string& line);
std::size_t search(std::map<std::string, std::vector<std::string>>& dict, std::string& line, std::size_t len, std::size_t min);


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./19.out <path/to/puzzle.txt> <part>" << std::endl;
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

    std::string l, r, line;
    std::map<std::string, std::vector<std::string>> dict;
    int arrow;
    while (std::getline(infile, line))
    {
        if (line.empty()) break;
        arrow = line.find(" => ");
        l = line.substr(0, arrow);
        r = line.substr(arrow + 4);

        if (dict.count(l)) dict[l].emplace_back(r);
        else
        {
            std::vector<std::string> s;
            s.emplace_back(r);
            dict[l] = s;
        }
    }

    std::getline(infile, line);
    infile.close();

    if (part == 1) part1(dict, line);
    else part2(dict, line);

    return 0;
}


void part1(std::map<std::string, std::vector<std::string>>& dict, std::string& line)
{
    std::set<std::string> seen;
    for (const auto& kv : dict)
    {
        std::size_t idx = line.find(kv.first);
        while (idx != std::string::npos)
        {
            for (std::string s : kv.second)
            {
                line.replace(idx, kv.first.length(), s);
                seen.insert(line);
                line.replace(idx, s.length(), kv.first);
            }
            idx = line.find(kv.first, idx+1);
        }
    }

    std::cout << seen.size() << std::endl;
}


void part2(std::map<std::string, std::vector<std::string>>& dict, std::string& line)
{
    std::size_t min = std::numeric_limits<std::size_t>::max();
    for (const auto& kv : dict)
    {
        std::cout << kv.first << std::endl;
        for (std::string s : dict[kv.first])
        {
            std::size_t idx = line.find(s);
            while (idx != std::string::npos)
            {
                line.replace(idx, s.length(), kv.first);
                std::cout << line << std::endl;
                min = std::min(min, search(dict, line, 1, min));
                line.replace(idx, kv.first.length(), s);

                idx = line.find(s, idx+1);
            }
        }
    }

    std::cout << min << std::endl;
}


std::size_t search(std::map<std::string, std::vector<std::string>>& dict, std::string& curr, std::size_t len, std::size_t min)
{
    if (len >= min) return len;
    if (curr == "e" || curr.length() == 1) return len;
    std::size_t l = std::numeric_limits<std::size_t>::max();
    for (const auto& kv : dict)
    {
        for (std::string s : dict[kv.first])
        {
            std::size_t idx = curr.find(s);
            while (idx != std::string::npos)
            {
                curr.replace(idx, s.length(), kv.first);
                std::cout << curr << std::endl;
                l = std::min(l, search(dict, curr, len+1, min));
                curr.replace(idx, kv.first.length(), s);

                idx = curr.find(s, idx+1);
            }
        }
    }
    return l;
}