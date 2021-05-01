#include "VirusList.hpp"

#include <array>
#include <iostream>
#include <memory>
#include <cstdint>

#include "Virus.hpp"
#include "SymptomList.hpp"

namespace VirusHelper
{
    void PopulateVirusList(std::array<Virus, kNumViruses>& viruses, VirusSymptomList& symptoms, size_t virus_symptom_index, size_t symptom_list_index, size_t& virus_index)
    {
        if (virus_symptom_index >= kNumSymptomsPerVirus)
        {
            viruses[virus_index].symptoms = symptoms;
            ++virus_index;
            return;
        }

        for (auto ii = symptom_list_index; ii < kNumSymptoms; ++ii)
        {
            symptoms[virus_symptom_index] = ii;
            PopulateVirusList(viruses, symptoms, virus_symptom_index + 1, ii + 1, virus_index);
        }
    }

    std::unique_ptr<std::array<Virus, kNumViruses>> MakeVirusList()
    {
        auto viruses = std::make_unique<std::array<Virus, kNumViruses>>();
        VirusSymptomList symptoms{-1, -1, -1, -1, -1, -1};
        size_t virus_index = 0;
        PopulateVirusList(*viruses, symptoms, 0, 0, virus_index);
        std::cout << "Made " << virus_index << " viruses!\n";
        return viruses;
    }

    // const std::array<Virus, kNumViruses> VirusList = MakeVirusList();
}