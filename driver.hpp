#pragma once
#include <string>

class Driver {
public:
    bool initialize() { return true; }
    bool attach(const std::string& processName) { return true; }
    void* mod(const wchar_t* moduleName) { return (void*)0x1000; }
    bool driver_init() { return true; }
    int GetProcessID(const wchar_t* processName) { return 1234; }
    uintptr_t GetBaseAddress(const char* moduleName) { return 0x1000; }
    int pid;
};

extern Driver driver;
