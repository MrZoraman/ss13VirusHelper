#ifndef VIRUSHELPER_VIRUSPARAMS_H
#define VIRUSHELPER_VIRUSPARAMS_H

#include <cstdint>

#include "Virus.hpp"

namespace VirusHelper
{
    class VirusParams
    {
        VirusSymptomList symptoms_{-1, -1, -1, -1, -1, -1};

    public:
        void PrintSymptoms() const;

        void SetSymptom(std::int32_t virus_symptom_index, std::int32_t symptom_index);
    };
}

#endif