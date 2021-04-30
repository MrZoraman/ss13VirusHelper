#ifndef VIRUSHELPER_VIRUSLIST_H
#define VIRUSHELPER_VIRUSLIST_H

#include <array>
#include <memory>

#include "Virus.hpp"

namespace VirusHelper
{
    const size_t kNumViruses = 7059052; // 44 take 6

    std::unique_ptr<std::array<Virus, kNumViruses>> MakeVirusList();
}

#endif