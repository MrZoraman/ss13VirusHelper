#ifndef VIRUSHELPER_SYMPTOM_H
#define VIRUSHELPER_SYMPTOM_H

#include <string>
#include <cstdint>

namespace VirusHelper
{
    struct Symptom
    {
        std::string name;
        std::int8_t stealth;
        std::int8_t resistance;
        std::int8_t stage_speed;
        std::int8_t transmission;
    };
}

#endif