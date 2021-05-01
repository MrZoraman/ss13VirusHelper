#include <iostream>
#include <cstdlib>
#include <cstdint>

#include "VirusList.hpp"
#include "Virus.hpp"
#include "VirusParams.hpp"
#include "SymptomList.hpp"

using namespace VirusHelper;

enum class TopMenuChoice
{
    Exit,
    ViewVirus,
    ListSymptoms,
    SelectSymptom
};

TopMenuChoice PrintTopMenu()
{
    std::cout << "0 - Exit\n";
    std::cout << "1 - View Selected Symptoms\n";
    std::cout << "2 - List All Available Symptoms\n";
    std::cout << "3 - Select Symptom\n";

    std::cout << "> ";
    std::int32_t choice = 0;
    std::cin >> choice;

    switch (choice)
    {
    case 0:
        return TopMenuChoice::Exit;
    case 1:
        return TopMenuChoice::ViewVirus;
    case 2:
        return TopMenuChoice::ListSymptoms;
    case 3:
        return TopMenuChoice::SelectSymptom;
    default:
        std::cout << "Unknown choice!\n";
        return PrintTopMenu();
    }
}

void SelectSymptom(VirusParams& params)
{
    std::int32_t virus_symptom_index = -1;
    while (virus_symptom_index < 0 || virus_symptom_index >= kNumSymptomsPerVirus)
    {
        std::cout << "Select a symptom index between 0 and " << +kNumSymptomsPerVirus << " inclusive:\n";
        std::cout << "> ";
        std::cin >> virus_symptom_index;
        if (virus_symptom_index < 0 || virus_symptom_index >= kNumSymptomsPerVirus)
        {
            std::cout << "Symptom index out of range!\n";
        }
    }
    
    while (true)
    {
        std::cout << "Select a symptom (by index), or -1 to clear:\n";
        std::cout << "> ";
        std::int32_t symptom_index;
        std::cin >> symptom_index;
        
        if (symptom_index >= static_cast<std::int32_t>(kNumSymptoms))
        {
            std::cout << "Symptom index too high!\n";
            continue;
        }

        params.SetSymptom(virus_symptom_index, symptom_index);
        break;
    }
}

int main()
{
    auto list = MakeVirusList();
    for (auto& it : *list)
    {
        it.CalculateStats();
    }

    std::cout << "All possible viruses have been calculated!\n";

    VirusParams params;

    auto exit = false;
    while (!exit)
    {
        auto choice = PrintTopMenu();
        switch (choice)
        {
            case TopMenuChoice::Exit:
            {
                exit = true;
                break;
            }
            case TopMenuChoice::ViewVirus:
            {
                params.PrintSymptoms();
                break;
            }
            case TopMenuChoice::ListSymptoms:
            {
                for (auto ii = 0; ii < SymptomList.size(); ++ii)
                {
                    std::cout << "[" << ii << "] " << SymptomList[ii].name << "\n";
                }
                break;
            }
            case TopMenuChoice::SelectSymptom:
            {
                SelectSymptom(params);
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}