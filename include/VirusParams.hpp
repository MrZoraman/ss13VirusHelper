#ifndef VIRUSHELPER_VIRUSPARAMS_H
#define VIRUSHELPER_VIRUSPARAMS_H

#include <cstdint>
#include <array>

#include "Virus.hpp"
#include "VirusList.hpp"

namespace VirusHelper
{

    class VirusParams
    {

        VirusSymptomList symptoms_{-1, -1, -1, -1, -1, -1};

        std::int32_t stealth_ = 1;
        std::int32_t resistance_ = 1;
        std::int32_t stage_speed_ = 1;
        std::int32_t transmission_ = 1;

        std::int32_t min_stealth_ = -1;
        std::int32_t min_resistance_ = -1;
        std::int32_t min_stage_speed_ = -1;
        std::int32_t min_transmission_ = -1;

        std::int32_t blacklist_symptom_ = -1;

        bool stealth_block_ = false;

        std::int32_t GetScore(const Virus& v) const;

    public:
        void PrintSymptoms() const;
        void PrintWeights() const;
        void PrintThresholds() const;
        bool IsStealthBlocked() const;

        [[nodiscard]] std::int32_t FindVirus(const std::array<Virus, kNumViruses>& viruses) const;

        void SetSymptom(std::int32_t virus_symptom_index, std::int32_t symptom_index);

        void set_stealth(std::int32_t stealth);
        void set_resistance(std::int32_t resistance);
        void set_stage_speed(std::int32_t stage_speed);
        void set_transmission(std::int32_t transmission);

        void set_min_stealth(std::int32_t min_stealth);
        void set_min_resistance(std::int32_t min_resistance);
        void set_min_stage_speed(std::int32_t min_stage_speed);
        void set_min_transmission(std::int32_t min_transmission);

        void set_blacklist_symptom(std::int32_t virus_symptom_index);

        void ToggleStealthBlock();
    };
}

#endif