//
// Created by Matt Falcone on 12/24/21.
//


#include "dps.hpp"

#include <spdlog/spdlog.h>

int main()
{
    spdlog::info("{}", dps::version());

    return 0;
}

