#include "VirusParams.hpp"

#include <cstdint>
#include <iostream>

#include "SymptomList.hpp"
#include "VirusList.hpp"

namespace VirusHelper
{
    void VirusParams::PrintSymptoms() const
    {
        std::cout << "Symptoms:\n";
        for (auto ii = 0; ii < symptoms_.size(); ++ii)
        {
            std::int32_t symptom_index = symptoms_[ii];

            std::cout << "  [" << ii << "] ";

            if (symptom_index < 0)
            {
                std::cout << "\n";
                continue;
            }

            std::cout << SymptomList[symptom_index].name << "\n";
        }
    }

    void VirusParams::PrintWeights() const
    {
        std::cout << "Weights:\n";
        std::cout << "  Stealth:      " << +stealth_ << "\n";
        std::cout << "  Resistance:   " << +resistance_ << "\n";
        std::cout << "  Stage Speed:  " << +stage_speed_ << "\n";
        std::cout << "  Transmission: " << +transmission_ << "\n";
    }

    void VirusParams::PrintThresholds() const
    {
        std::cout << "Min Thresholds:\n";
        std::cout << "  Min Stealth:      " << +min_stealth_ << "\n";
        std::cout << "  Min Resistance:   " << +min_resistance_ << "\n";
        std::cout << "  Min Stage Speed:  " << +min_stage_speed_ << "\n";
        std::cout << "  Min Transmission: " << +min_transmission_ << "\n";
    }

    std::int32_t VirusParams::GetScore(const Virus& v) const
    {
        if (stealth_block_ && v.stealth > 1)
        {
            return -1;
        }

        if (min_stealth_ >= 0 && v.stealth < min_stealth_)
        {
            return -1;
        }

        if (min_resistance_ >= 0 && v.resistance < min_resistance_)
        {
            return -1;
        }

        if (min_stage_speed_ >= 0 && v.stage_speed < min_stage_speed_)
        {
            return -1;
        }

        if (min_transmission_ >= 0 && v.transmission < min_transmission_)
        {
            return -1;
        }

        if(blacklist_symptom_ >= 0 && v.Contains(blacklist_symptom_))
        {
            return -1;
        }

        for (auto symptom : symptoms_)
        {
            if (symptom >= 0 && !v.Contains(symptom))
            {
                return -1;
            }
        }

        std::int32_t score = 0;
        for (auto symptom_index : v.symptoms)
        {
            auto symptom = SymptomList[symptom_index];
            std::int32_t value = 0;

            value = symptom.stealth * stealth_;
            if (value > 0)
            {
                score += value;
            }

            value = symptom.resistance * resistance_;
            if (value > 0)
            {
                score += value;
            }

            value = symptom.stage_speed * stage_speed_;
            if (value > 0)
            {
                score += value;
            }

            value = symptom.transmission * transmission_;
            if (value > 0)
            {
                score += value;
            }
        }

        return score;
    }

    std::int32_t VirusParams::FindVirus(const std::array<Virus, kNumViruses>& viruses) const
    {
        std::int32_t best_candidate = -1;
        std::int32_t best_score = -1;
        std::int32_t equalScoresFound = 0;
        for (auto ii = 0; ii < viruses.size(); ++ii)
        {
            auto score = GetScore(viruses[ii]);
            if (score > best_score)
            {
                best_candidate = ii;
                equalScoresFound = 0;
                best_score = score;
            }

            if (score == best_score)
            {
                ++equalScoresFound;
            }
        }

        if (best_candidate > 0)
        {
            std::cout << "Candidate found! Also found " << equalScoresFound << " equal candidates.\n";
        }

        return best_candidate;
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

    bool VirusParams::IsStealthBlocked() const
    {
        return stealth_block_;
    }

    void VirusParams::set_stealth(std::int32_t stealth)
    {
        stealth_ = stealth;
    }

    void VirusParams::set_resistance(std::int32_t resistance)
    {
        resistance_ = resistance;
    }

    void VirusParams::set_stage_speed(std::int32_t stage_speed)
    {
        stage_speed_ = stage_speed;
    }

    void VirusParams::set_transmission(std::int32_t transmission)
    {
        transmission_ = transmission;
    }

    void VirusParams::set_min_stealth(std::int32_t min_stealth)
    {
        min_stealth_ = min_stealth;
    }

    void VirusParams::set_min_resistance(std::int32_t min_resistance)
    {
        min_resistance_ = min_resistance;
    }

    void VirusParams::set_min_stage_speed(std::int32_t min_stage_speed)
    {
        min_stage_speed_ = min_stage_speed;
    }

    void VirusParams::set_min_transmission(std::int32_t min_transmission)
    {
        min_transmission_ = min_transmission;
    }

    void VirusParams::ToggleStealthBlock()
    {
        stealth_block_ = !stealth_block_;
    }

    void VirusParams::set_blacklist_symptom(std::int32_t virus_symptom_index)
    {
        blacklist_symptom_ = virus_symptom_index;
    }
}