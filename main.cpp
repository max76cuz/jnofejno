#include <thread>
#include <chrono>
#include <cstdio>
#include <windows.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "global.hpp"
#include "driver.hpp"
#include "utils.hpp"
#include "recoil_controller.hpp"
#include "overlay.hpp"

static const char* recoil_weapons[]{ "AK-47", "M249", "LR-300", "MP5", "Custom SMG", "Thompson" };

void RenderMenu()
{
    ImGui::Begin("Recoil Control");
    ImGui::TextColored(ImVec4(0.8f, 1.f, 0.f, 1.f), "Recoil Control System");
    ImGui::Checkbox("Enabled", &global.recoil_enabled);
    ImGui::Checkbox("Auto Detect Weapon", &global.auto_detect_weapon);

    if (!global.auto_detect_weapon) {
        ImGui::Combo("Weapon", &global.selected_weapon, recoil_weapons, IM_ARRAYSIZE(recoil_weapons));
    }

    ImGui::SliderFloat("Recoil Strength", &global.recoil_strength, 0.f, 1.f);
    ImGui::SliderFloat("Humanization", &global.humanization_amount, 0.f, 1.f);
    ImGui::SliderFloat("Randomness", &global.randomness, 0.f, 1.f);
    ImGui::SliderFloat("Shot Delay (ms)", &global.shot_delay, 0.f, 100.f);

    ImGui::Checkbox("Compensate Vertical", &global.recoil_vertical);
    ImGui::Checkbox("Compensate Horizontal", &global.recoil_horizontal);

    ImGui::Checkbox("Show Debug Crosshair", &global.debug_crosshair);
    ImGui::Checkbox("Show FOV Circle", &global.show_fov_circle);
    if (global.show_fov_circle) {
        ImGui::SliderFloat("FOV Size", &global.fov_size, 0.f, 500.f);
    }

    ImGui::End();
}

// Stub functions for cheat threads
void UpdateLists() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Logic here
    }
}
void UpdatePositions() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Logic here
    }
}
void Aimbot() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Logic here
    }
}
void Misc() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Logic here
    }
}

int main(int, char**)
{
    // 1. Wait for Rust window
    while (!FindWindowA("UnityWndClass", "Rust")) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    system("cls");

    // 2. Check file system
    Utils::CheckFileSystem();
    printf("[+] Found Rust!\n");
    printf("[+] Checked File System\n");

    // 3. Driver initialization (stubbed)
    if (!driver.initialize()) {
        printf("[!] hypervisor is not loaded\n");
        return 1;
    }
    if (!driver.attach("RustClient.exe")) {
        printf("[!] failed to attach to RustClient.exe\n");
        return 1;
    }
    global.unity_player = driver.mod(L"UnityPlayer.dll");
    global.game_assembly = driver.mod(L"GameAssembly.dll");
    printf("[+] Found UnityPlayer.dll -> %p\n", global.unity_player);
    printf("[+] Found GameAssembly.dll -> %p\n", global.game_assembly);

    // BlockCommands stub (just ignore here)
    // reinterpret_cast<Movement*>(0)->BlockCommands();

    // 4. Launch cheat threads
    std::thread(UpdateLists).detach();
    std::thread(UpdatePositions).detach();
    std::thread(Aimbot).detach();
    std::thread(Misc).detach();

    printf("[+] Threads started\n");

    // 5. Setup GLFW and ImGui
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Rust Recoil Control", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    RecoilController recoil_controller;

    // 6. Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderMenu();

        recoil_controller.CompensateRecoil();

        Overlay();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 7. Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
