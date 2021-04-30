#include "Virus.hpp"

#include "SymptomList.hpp"

namespace VirusHelper
{
    void Virus::CalculateStats()
    {
        stealth = 0;
        resistance = 0;
        stage_speed = 0;
        transmission = 0;

        for (auto symptom_index : symptoms)
        {
            stealth += SymptomList[symptom_index].stealth;
            resistance += SymptomList[symptom_index].resistance;
            stage_speed += SymptomList[symptom_index].stage_speed;
            transmission += SymptomList[symptom_index].transmission;
        }
    }

}