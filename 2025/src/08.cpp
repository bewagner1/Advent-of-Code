/**
 * 
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>


bool intersects(const std::set<int>& a, const std::set<int>& b);
std::vector<std::set<int>> consolidate(std::vector<std::set<int>> v);


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./08.out <path/to/puzzle.txt> <part>" << std::endl;
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

    std::vector<std::vector<long>> points;
    std::vector<long> p(3);
    long x,y,z;
    char comma;
    while (infile >> x >> comma >> y >> comma >> z)
    {
        p = {x, y, z};
        points.emplace_back(p);
    }
    infile.close();

    std::vector<std::vector<double>> dists(points.size(), std::vector<double>(points.size()));
    double xsq, ysq, zsq;
    for (int i=0; i<points.size()-1; ++i)
    {
        for (int j=i+1; j<points.size(); ++j)
        {
            xsq = points[i][0] - points[j][0];
            ysq = points[i][1] - points[j][1];
            zsq = points[i][2] - points[j][2];

            xsq = xsq * xsq;
            ysq = ysq * ysq;
            zsq = zsq * zsq;

            dists[i][j] = sqrt(xsq + ysq + zsq);
        }
    }

    std::priority_queue<double, std::vector<double>, std::greater<double>> heap;
    for (int i=0; i<points.size()-1; ++i)
    {
        for (int j=i+1; j<points.size(); ++j)
        {
            heap.push(dists[i][j]);
        }
    }

    std::vector<std::set<int>> circuits;
    int max_connections = strstr(argv[1], "example") ? 10 : 1000;
    int n_connections = 0;
    int r,c,flag;
    while (n_connections < max_connections)
    {
        flag = 0;
        for (int i=0; i<points.size()-1; ++i)
        {
            for (int j=i+1; j<points.size(); ++j)
            {
                if (dists[i][j] == heap.top())
                {
                    r = i;
                    c = j;
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }

        for (int i=0; i<circuits.size(); ++i)
        {
            if (circuits[i].count(r) || circuits[i].count(c))
            {
                circuits[i].emplace(r);
                circuits[i].emplace(c);
                n_connections++;
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            std::set<int> s = {r, c};
            circuits.emplace_back(s);
            n_connections++;
        }

        circuits = consolidate(circuits);
        heap.pop();
    }

    if (part == 1)
    {
        std::priority_queue<double, std::vector<double>, std::greater<double>> sizes;
        for (std::set<int> s : circuits)
        {
            if (sizes.size() < 3)
            {
                sizes.push(s.size());
            }
            else if (s.size() > sizes.top())
            {
                sizes.pop();
                sizes.push(s.size());
            }
        }

        long total = 1;
        while (!sizes.empty())
        {
            total = total * sizes.top();
            sizes.pop();
        }
        std::cout << "The product of the sizes of the largest 3 circuits is " << total << std::endl;
    }
    else if (part == 2)
    {
        while (circuits[0].size() < points.size())
        {
            if (heap.empty()) {std::cout << "Trying to make too many connections!" << std::endl; exit(1);}
            flag = 0;
            for (int i=0; i<points.size()-1; ++i)
            {
                for (int j=i+1; j<points.size(); ++j)
                {
                    if (dists[i][j] == heap.top())
                    {
                        r = i;
                        c = j;
                        flag = 1;
                        break;
                    }
                }
                if (flag) break;
            }

            for (int i=0; i<circuits.size(); ++i)
            {
                if (circuits[i].count(r) || circuits[i].count(c))
                {
                    circuits[i].emplace(r);
                    circuits[i].emplace(c);
                    n_connections++;
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                std::set<int> s = {r, c};
                circuits.emplace_back(s);
                n_connections++;
            }

            circuits = consolidate(circuits);
            heap.pop();
        }
        std::cout << circuits[0].size() << std::endl;
        std::cout << points[r][0] * points[c][0] << std::endl;
    }

    return 0;
}


bool intersects(const std::set<int>& a, const std::set<int>& b) {
    for (int x : a)
        if (b.count(x)) return true;
    return false;
}


std::vector<std::set<int>> consolidate(std::vector<std::set<int>> v) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < (int)v.size() && !changed; i++) {
            for (int j = i+1; j < (int)v.size() && !changed; j++) {
                if (intersects(v[i], v[j])) {
                    v[i].insert(v[j].begin(), v[j].end());
                    v.erase(v.begin() + j);
                    changed = true;
                }
            }
        }
    }
    return v;
}