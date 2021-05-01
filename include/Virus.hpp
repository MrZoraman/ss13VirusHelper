#ifndef VIRUSHELPER_VIRUS_H
#define VIRUSHELPER_VIRUS_H

#include <cstdint>
#include <array>

#include "Symptom.hpp"

namespace VirusHelper
{
    const std::int8_t kNumSymptomsPerVirus = 6;

    typedef std::array<int32_t, kNumSymptomsPerVirus> VirusSymptomList;

    struct Virus
    {
        VirusSymptomList symptoms{ -1, -1, -1, -1, -1, -1};

        std::int8_t stealth = 0;
        std::int8_t resistance = 0;
        std::int8_t stage_speed = 0;
        std::int8_t transmission = 0;

        void CalculateStats();
    };
}

#endif //VIRUSHELPER_VIRUS_H