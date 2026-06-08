
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

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
    std::string str;
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::smatch m;
    unsigned long long some = 0;
    
    while (infile >> str) {
        auto words_begin = std::sregex_iterator(str.begin(), str.end(), pattern);
        auto words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            m = *i;
            some += std::stoull(m[1]) * std::stoull(m[2]);
        }
    }

    std::cout << some << std::endl;
}


void part_two(std::fstream& infile)
{
    std::stringstream buff;
    buff << infile.rdbuf();
    std::string str = buff.str();
    std::regex pattern(R"((mul\((\d+),(\d+)\))|(do\(\))|(don't\(\)))");
    std::smatch m;
    unsigned long long some = 0;
    bool flag = true;

    const auto s = std::sregex_iterator(str.begin(), str.end(), pattern);
    const auto e = std::sregex_iterator();
    for (std::sregex_iterator i = s; i != e; ++i) {
        m = *i;
        if (m[5].str().find("don't()", 0) != std::string::npos) {
            flag = false;
            continue;
        } else if (m[4].str().find("do()", 0) != std::string::npos) {
            flag = true;
        }
        if (flag && m[1].str().find("mul", 0) != std::string::npos) {
            some += std::stoull(m[2].str()) * std::stoull(m[3].str());
        }
    }

    std::cout << some << std::endl;
}