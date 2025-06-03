#include "overlay.hpp"
#include "imgui.h"
#include "global.hpp"

void Overlay() {
    // Draw a simple ImGui window with debug info or crosshair

    if (global.debug_crosshair) {
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::Begin("DebugCrosshair", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                               ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove |
                                               ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
                                               ImGuiWindowFlags_NoNav);

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 center = ImGui::GetIO().DisplaySize;
        center.x /= 2; center.y /= 2;

        draw_list->AddLine(ImVec2(center.x - 10, center.y), ImVec2(center.x + 10, center.y), IM_COL32(255, 0, 0, 255), 2.0f);
        draw_list->AddLine(ImVec2(center.x, center.y - 10), ImVec2(center.x, center.y + 10), IM_COL32(255, 0, 0, 255), 2.0f);

        ImGui::End();
    }

    // Draw FOV circle
    if (global.show_fov_circle) {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        ImVec2 center = ImGui::GetIO().DisplaySize;
        center.x /= 2; center.y /= 2;

        draw_list->AddCircle(center, global.fov_size, IM_COL32(0, 255, 0, 128), 64, 2.0f);
    }
}
