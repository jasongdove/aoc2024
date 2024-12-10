#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <vector>

bool is_safe_2(std::vector<int> report);

bool is_safe(std::vector<int> report, bool dampener)
{
    bool safe = true;

    if (abs(report[0] - report[1]) > 3 || report[0] == report[1])
        return dampener && is_safe_2(report);

    int diff = (report[0] - report[1]) < 0 ? -1 : 1;
    for (int i=1; i<report.size()-1; i++)
    {
        int diff2 = report[i] - report[i+1];
        safe = safe && (diff == diff2 || diff * 2 == diff2 || diff * 3 == diff2);
        if (!safe && dampener)
            return is_safe_2(report);
    }

    return safe;
}

bool is_safe_2(std::vector<int> report)
{
    for (int j=0; j<report.size(); j++)
    {
        std::vector<int> copy = {};
        for (int k=0; k<report.size(); k++)
            if (k != j)
                copy.push_back(report[k]);

        if (is_safe(copy, false))
            return true;
    }

    return false;
}

int main()
{
    std::ifstream file("input/day02.txt");

    if (!file.is_open())
        return 1;

    std::regex reg("(\\d+)");

    int safeCount1 = 0;
    int safeCount2 = 0;

    std::string line;
    while (std::getline(file, line))
    {
        std::sregex_iterator begin(line.begin(), line.end(), reg);
        std::sregex_iterator end;

        std::vector<int> report;
        for (std::sregex_iterator i = begin; i != end; ++i)
        {
            std::smatch match = *i;
            report.push_back(std::stoi(match.str()));
        }

        if (is_safe(report, false))
            safeCount1++;

        if (is_safe(report, true))
            safeCount2++;
    }

    std::cout << safeCount1 << std::endl;
    std::cout << safeCount2 << std::endl;

    return 0;
}
