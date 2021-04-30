#ifndef VIRUSHELPER_VIRUS_H
#define VIRUSHELPER_VIRUS_H

#include <cstdint>
#include <array>

#include "Symptom.hpp"

namespace VirusHelper
{
    const std::int8_t kNumSymptomsPerVirus = 6;

    struct Virus
    {
        std::array<size_t, kNumSymptomsPerVirus> symptoms;

        std::int8_t stealth;
        std::int8_t resistance;
        std::int8_t stage_speed;
        std::int8_t transmission;
    };
}

#endif //VIRUSHELPER_VIRUS_H