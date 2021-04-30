#ifndef VIRUSHELPER_SYMPTOMLIST_H
#define VIRUSHELPER_SYMPTOMLIST_H

#include <array>

#include "Symptom.hpp"

namespace VirusHelper
{
    const size_t kNumSymptoms = 44;

    extern const std::array<const Symptom, kNumSymptoms> SymptomList;
}

#endif