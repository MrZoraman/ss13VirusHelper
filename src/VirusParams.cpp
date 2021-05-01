#include "VirusParams.hpp"

#include <cstdint>
#include <iostream>

#include "SymptomList.hpp"

namespace VirusHelper
{
    void VirusParams::PrintSymptoms() const
    {
        for (auto ii = 0; ii < symptoms_.size(); ++ii)
        {
            std::int32_t symptom_index = symptoms_[ii];

            std::cout << "[" << ii << "] ";

            if (symptom_index < 0)
            {
                std::cout << "\n";
                continue;
            }

            std::cout << SymptomList[symptom_index].name << "\n";
        }
    }

    void VirusParams::SetSymptom(std::int32_t virus_symptom_index, std::int32_t symptom_index)
    {
        if (virus_symptom_index < 0 || virus_symptom_index >= symptoms_.size())
        {
            std::cout << "Virus symptom index out of range!\n";
            return;
        }

        if (symptom_index >= static_cast<std::int32_t>(SymptomList.size()))
        {
            std::cout << "Symptom list index out of range!\n";
            return;
        }

        symptoms_[virus_symptom_index] = symptom_index;
    }


}