#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream file("input/day01.txt");

    if (!file.is_open())
        return 1;

    std::vector<int> left = {};
    std::vector<int> right = {};

    std::string line;
    while (std::getline(file, line))
    {
        int number;
        std::istringstream stream(line);

        stream >> number;
        left.push_back(number);

        stream >> number;
        right.push_back(number);
    }

    file.close();

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int dist = 0;
    for (int i=0; i<left.size(); i++)
        dist += abs(left[i] - right[i]);

    std::cout << dist << std::endl;

    auto freq = std::map<int, int>();
    for (auto const& i : right)
    {
        if (freq.contains(i))
            freq[i]++;
        else
            freq[i] = 1;
    }

    int score = 0;
    for (auto const& i : left)
        if (freq.contains(i))
            score += i * freq[i];

    std::cout << score << std::endl;

    return 0;
}

