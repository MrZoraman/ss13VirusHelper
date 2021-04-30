#include <iostream>
#include <cstdlib>

#include "VirusList.hpp"
#include "Virus.hpp"

using namespace VirusHelper;

int main()
{
    auto list = MakeVirusList();
    for (auto& it : *list)
    {
        it.CalculateStats();
    }

    std::cout << "All possible viruses have been calculated!\n";

    return EXIT_SUCCESS;
}