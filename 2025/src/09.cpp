/**
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>


int isOnOrInsidePolygon(const std::vector<std::pair<long,long>>& polygon, const std::pair<long,long>& p);
int isRectangleFullyInOrOnPolygon(const std::vector<std::pair<long,long>>& polygon, const std::vector<std::pair<long,long>>& rectangle);


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
    points.reserve(1000);
    long x, y;
    char comma;
    while (infile >> x >> comma >> y)
    {
        points.emplace_back(x, y);
    }
    
    long max_area = 0;
    size_t n = points.size();
    
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            long width = std::abs(points[i].first - points[j].first) + 1;
            long height = std::abs(points[i].second - points[j].second) + 1;
            long area = width * height;
            
            if (area <= max_area) continue;
            if (part == 2) {
                std::vector<std::pair<long,long>> rectangle = {
                    points[i], 
                    points[j], 
                    {points[i].first, points[j].second}, 
                    {points[j].first, points[i].second}
                };
                
                if (!isRectangleFullyInOrOnPolygon(points, rectangle)) {
                    continue;
                }
            }
            
            max_area = area;
        }
    }

    std::cout << "The maximum area is " << max_area << std::endl;

    return 0;
}

int isOnOrInsidePolygon(const std::vector<std::pair<long,long>>& polygon, const std::pair<long,long>& p) {
    int n = polygon.size();
    
    for (int i = 0; i < n; i++) {
        const std::pair<long,long>& p1 = polygon[i];
        const std::pair<long,long>& p2 = polygon[(i + 1) % n];
        
        if (p1.second == p2.second && p1.second == p.second) {
            if (p.first >= std::min(p1.first, p2.first) && 
                p.first <= std::max(p1.first, p2.first)) {
                return true;
            }
        }
        
        if (p1.first == p2.first && p1.first == p.first) {
            if (p.second >= std::min(p1.second, p2.second) && 
                p.second <= std::max(p1.second, p2.second)) {
                return true;
            }
        }
    }
    
    int crossings = 0;
    for (int i = 0; i < n; i++) {
        const std::pair<long,long>& p1 = polygon[i];
        const std::pair<long,long>& p2 = polygon[(i + 1) % n];
        
        if (p1.first == p2.first) {

            if (p1.first > p.first) {
                long minY = std::min(p1.second, p2.second);
                long maxY = std::max(p1.second, p2.second);
                
                if (p.second >= minY && p.second < maxY) crossings++;
            }
        }
    }
    
    return crossings % 2;
}


int isRectangleFullyInOrOnPolygon(const std::vector<std::pair<long,long>>& polygon, const std::vector<std::pair<long,long>>& rectangle) {
    
    long minX = rectangle[0].first, maxX = rectangle[0].first;
    long minY = rectangle[0].second, maxY = rectangle[0].second;
    
    for (const std::pair<long,long>& p : rectangle) {
        minX = std::min(minX, p.first);
        maxX = std::max(maxX, p.first);
        minY = std::min(minY, p.second);
        maxY = std::max(maxY, p.second);
    }
    

    if (!isOnOrInsidePolygon(polygon, {minX, minY})) return false;
    if (!isOnOrInsidePolygon(polygon, {maxX, minY})) return false;
    if (!isOnOrInsidePolygon(polygon, {minX, maxY})) return false;
    if (!isOnOrInsidePolygon(polygon, {maxX, maxY})) return false;
    
    for (long x = minX + 1; x < maxX; x++) {
        if (!isOnOrInsidePolygon(polygon, {x, minY})) return false;
        if (!isOnOrInsidePolygon(polygon, {x, maxY})) return false;
    }
    for (long y = minY + 1; y < maxY; y++) {
        if (!isOnOrInsidePolygon(polygon, {minX, y})) return false;
        if (!isOnOrInsidePolygon(polygon, {maxX, y})) return false;
    }
    
    return true;
}