#pragma once

#include <atomic>

struct GlobalData {
    bool recoil_enabled = true;
    bool auto_detect_weapon = true;
    int selected_weapon = 0;
    float recoil_strength = 0.5f;
    float humanization_amount = 0.3f;
    float randomness = 0.2f;
    float shot_delay = 50.f;
    bool recoil_vertical = true;
    bool recoil_horizontal = true;
    bool debug_crosshair = false;
    bool show_fov_circle = false;
    float fov_size = 250.f;

    void* unity_player = nullptr;
    void* game_assembly = nullptr;
};

extern GlobalData global;
