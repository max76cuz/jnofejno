#pragma once
#include <random>
#include <chrono>
#include <cstdio>
#include "global.hpp"

class RecoilController {
    std::chrono::steady_clock::time_point last_shot_time;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;

public:
    RecoilController() : distribution(-1.f, 1.f) {
        last_shot_time = std::chrono::steady_clock::now();
    }

    void CompensateRecoil() {
        if (!global.recoil_enabled)
            return;

        auto now = std::chrono::steady_clock::now();
        float elapsed_ms = std::chrono::duration<float, std::milli>(now - last_shot_time).count();

        if (elapsed_ms < global.shot_delay)
            return;

        last_shot_time = now;

        float vertical_recoil = 1.0f * global.recoil_strength;
        float horizontal_recoil = 0.5f * global.recoil_strength;

        vertical_recoil += vertical_recoil * global.humanization_amount * distribution(generator);
        horizontal_recoil += horizontal_recoil * global.humanization_amount * distribution(generator);

        vertical_recoil += vertical_recoil * global.randomness * distribution(generator);
        horizontal_recoil += horizontal_recoil * global.randomness * distribution(generator);

        if (!global.recoil_vertical) vertical_recoil = 0.f;
        if (!global.recoil_horizontal) horizontal_recoil = 0.f;

        printf("Compensate Recoil: Vertical=%.3f, Horizontal=%.3f\n", vertical_recoil, horizontal_recoil);
    }
};
