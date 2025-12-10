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

    std::vector<std::vector<double>> dists(points.size(), std::vector<double>(points.size()));
    double xsq, ysq, zsq;
    for (int i=0; i<points.size()-1; ++i)
    {
        for (int j=i+1; j<points.size(); ++j)
        {
            xsq = points.at(i).at(0) - points.at(j).at(0);
            ysq = points.at(i).at(1) - points.at(j).at(1);
            zsq = points.at(i).at(2) - points.at(j).at(2);

            xsq = xsq * xsq;
            ysq = ysq * ysq;
            zsq = zsq * zsq;

            dists.at(i).at(j) = sqrt(xsq + ysq + zsq);
        }
    }

    if (part == 2)
    {
        std::vector<int> closest_p(points.size());
        double c;
        for (int p=0; p<points.size(); ++p)
        {
            c = std::numeric_limits<double>::infinity();
            for (int i=0; i<p; i++)
            {
                if (dists.at(i).at(p) < c)
                {
                    closest_p.at(p) = i;
                    c = dists.at(i).at(p);
                }
            }
            for (int i=p+1; i<points.size(); ++i)
            {
                if (dists.at(p).at(i) < c)
                {
                    closest_p.at(p) = i;
                    c = dists.at(p).at(i);
                }
            }
        }

        double mx = 0;
        long xmul;
        for (int p=0; p<points.size(); ++p)
        {
            std::cout << "(" << p << ", " << closest_p.at(p) << ")";
            if (dists.at(p).at(closest_p.at(p)) > mx)
            {
                mx = dists.at(p).at(closest_p.at(p));
                xmul = points.at(p).at(0) * points.at(closest_p.at(p)).at(0);
                std::cout << "*";
            }
            std::cout << std::endl;
        }

        std::cout << xmul << std::endl;

        return 0;
    }


    std::priority_queue<double> min_dists;
    int max_size = strstr(argv[1], "example") ? 10 : 1000;
    double d;
    for (int i=0; i<dists.size()-1; i++)
    {
        for (int j=i+1; j<dists.size(); j++)
        {
            d = dists.at(i).at(j);
            if (min_dists.empty()) { min_dists.push(d); continue; }
            if (d < min_dists.top() && min_dists.size() >= max_size)
            {
                min_dists.pop();
                min_dists.push(d);
            } else if (d < min_dists.top())
            {
                min_dists.push(d);
            }
        }
    }

    std::vector<std::pair<int, int>> connections(min_dists.size());
    std::cout << min_dists.size() << std::endl;
    int index = 0;
    int flag = 0;
    while (!min_dists.empty())
    {
        d = min_dists.top();
        for (int i=0; i<dists.size()-1; i++)
        {
            for (int j=i+1; j<dists.size(); j++)
            {
                if (d == dists.at(i).at(j))
                {
                    connections.at(index).first = i;
                    connections.at(index).second = j;
                    index++;
                    flag = 1;
                    break;
                }
                if (flag) break;
            }
        }
        min_dists.pop();
        flag = 0;
    }

    std::vector<std::set<int>> circuits;
    circuits.emplace_back(std::set<int>({connections.at(0).first, connections.at(0).second}));
    int l,r;
    for (int i=1; i<connections.size(); i++)
    {
        l = connections.at(i).first;
        r = connections.at(i).second;

        for (int j=0; j<circuits.size(); j++)
        {
            if (circuits.at(j).count(l) && circuits.at(j).count(r))
            {
                flag = 1;
                break;
            }
            else if (circuits.at(j).count(l) || circuits.at(j).count(r))
            {
                circuits.at(j).emplace(l);
                circuits.at(j).emplace(r);
                flag = 1;
                break;
            }
        }

        if (!flag) circuits.emplace_back(std::set<int>({l, r}));
        flag = 0;
    }
    circuits = consolidate(circuits);

    std::priority_queue<int> sizes;
    for (std::set<int> s : circuits) sizes.push(s.size());

    int total = 1;
    for (int i=0; i<3; i++)
    {
        total = total * sizes.top();
        sizes.pop();
    }

    std::cout << "Multiplying the largest three circuits yields " << total << std::endl;

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
