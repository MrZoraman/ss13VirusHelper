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
    ViewQuery,
    ListSymptoms,
    SelectSymptom,
    SetThreshold,
    SetWeight,
    Search
};

enum class VirusStat
{
    Stealth,
    Resistance,
    StageSpeed,
    Transmission,
    Unknown
};

TopMenuChoice PrintTopMenu()
{
    std::cout << "0 - Exit\n";
    std::cout << "1 - View Query\n";
    std::cout << "2 - List All Available Symptoms\n";
    std::cout << "3 - Select Symptom\n";
    std::cout << "4 - Set Threshold\n";
    std::cout << "5 - Set Weight\n";
    std::cout << "6 - Search\n";

    std::cout << "> ";
    std::int32_t choice = 0;
    std::cin >> choice;

    switch (choice)
    {
    case 0:
        return TopMenuChoice::Exit;
    case 1:
        return TopMenuChoice::ViewQuery;
    case 2:
        return TopMenuChoice::ListSymptoms;
    case 3:
        return TopMenuChoice::SelectSymptom;
    case 4:
        return TopMenuChoice::SetThreshold;
    case 5:
        return TopMenuChoice::SetWeight;
    case 6:
        return TopMenuChoice::Search;
    default:
        std::cout << "Unknown choice!\n";
        return PrintTopMenu();
    }
}

VirusStat ChooseStat()
{
    std::cout << "Choose a stat: \n";
    std::cout << "0 - Stealth\n";
    std::cout << "1 - Resistance\n";
    std::cout << "2 - Stage Speed\n";
    std::cout << "3 - Transmission\n";

    std::int32_t choice = -1;
    while (choice < 0 || choice > 4)
    {
        std::cout << "> ";
        std::cin >> choice;

        if (choice < 0 || choice > 4)
        {
            std::cout << "Choice out of range!\n";
        }
    }

    switch(choice)
    {
    case 0: return VirusStat::Stealth;
    case 1: return VirusStat::Resistance;
    case 2: return VirusStat::StageSpeed;
    case 3: return VirusStat::Transmission;
    default: return VirusStat::Unknown; // should be impossible
    }
}

void SetThreshold(VirusParams& params)
{
    VirusStat stat_choice = ChooseStat();
    std::int32_t threshold;
    std::cout << "Set threshold: \n";
    std::cout << "> ";
    std::cin >> threshold;

    if (stat_choice == VirusStat::Stealth)
    {
        params.set_min_stealth(threshold);
    }
    else if (stat_choice == VirusStat::Resistance)
    {
        params.set_min_resistance(threshold);
    }
    else if (stat_choice == VirusStat::StageSpeed)
    {
        params.set_min_stage_speed(threshold);
    }
    else if (stat_choice == VirusStat::Transmission)
    {
        params.set_min_transmission(threshold);
    }
}

void SetWeight(VirusParams& params)
{
    VirusStat stat_choice = ChooseStat();
    std::int32_t weight;
    std::cout << "Set weight: \n";
    std::cout << "> ";
    std::cin >> weight;

    if (stat_choice == VirusStat::Stealth)
    {
        params.set_stealth(weight);
    }
    else if (stat_choice == VirusStat::Resistance)
    {
        params.set_resistance(weight);
    }
    else if (stat_choice == VirusStat::StageSpeed)
    {
        params.set_stage_speed(weight);
    }
    else if (stat_choice == VirusStat::Transmission)
    {
        params.set_transmission(weight);
    }
}

void SelectSymptom(VirusParams& params)
{
    std::int32_t virus_symptom_index = -1;
    while (virus_symptom_index < 0 || virus_symptom_index >= kNumSymptomsPerVirus)
    {
        std::cout << "Select a symptom index between 0 and " << +kNumSymptomsPerVirus - 1 << " inclusive:\n";
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
    
    while (true)
    {
        auto choice = PrintTopMenu();
        if (choice == TopMenuChoice::Exit)
        {
            return EXIT_SUCCESS;
        }
        else if (choice == TopMenuChoice::ViewQuery)
        {
            params.PrintSymptoms();
            params.PrintWeights();
            params.PrintThresholds();
        }
        else if (choice == TopMenuChoice::ListSymptoms)
        {
            for (auto ii = 0; ii < SymptomList.size(); ++ii)
            {
                std::cout << "[" << ii << "] " << SymptomList[ii].name << "\n";
            }
        }
        else if (choice == TopMenuChoice::SelectSymptom)
        {
            SelectSymptom(params);
        }
        else if (choice == TopMenuChoice::SetThreshold)
        {
            SetThreshold(params);
        }
        else if (choice == TopMenuChoice::SetWeight)
        {
            SetWeight(params);
        }
        else if (choice == TopMenuChoice::Search)
        {
            auto candidate = params.FindVirus(*list);
            if (candidate >= 0)
            {
                auto& virus = (*list)[candidate];
                std::cout << "Stealth:      " << +virus.stealth << "\n";
                std::cout << "Resistance:   " << +virus.resistance << "\n";
                std::cout << "Stage Speed:  " << +virus.stage_speed << "\n";
                std::cout << "Transmission: " << +virus.transmission << "\n";
                std::cout << "Symptoms:\n";
                for (const auto& symptom_index : virus.symptoms)
                {
                    std::cout << "  - " << SymptomList[symptom_index].name << "\n";
                }
            }
        }
    }

    return EXIT_SUCCESS;
}