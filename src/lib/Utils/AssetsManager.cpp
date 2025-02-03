//
// Created by piotr on 17.01.25.
//

#include "AssetsManager.h"
#include <filesystem>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <unistd.h>
#include <libgen.h>
#include <mach-o/dyld.h>
#elif __linux__
#include <unistd.h>
#endif


std::filesystem::path get_executable_path() {
    char result[1024];

    // Dla Windows
#ifdef _WIN32
    GetModuleFileNameA(NULL, result, sizeof(result));
    std::cout << "Ścieżka pliku wykonywalnego (Windows): " << result << std::endl;
    return std::filesystem::path(result).parent_path();

    // Dla macOS
#elif __APPLE__
    uint32_t size = sizeof(result);
    if (_NSGetExecutablePath(result, &size) == 0) {
        return std::filesystem::path(result).parent_path();
    } else {
        std::cerr << "Błąd podczas pobierania ścieżki pliku wykonywalnego na macOS" << std::endl;
    }

    // Dla Linux
#elif __linux__
    ssize_t count = readlink("/proc/self/exe", result, sizeof(result) - 1);
    if (count != -1) {
        result[count] = '\0'; // Dodaj null-terminator
        std::cout << "Ścieżka pliku wykonywalnego (Linux): " << result << std::endl;
        return std::filesystem::path(result).parent_path();
    }
#endif

    return {};
}

std::string AssetsManager::GetAssetsPath() {
    // std::filesystem::path path = std::filesystem::current_path();
    // std::cout << path << std::endl;
    std::filesystem::path path = get_executable_path();
    // std::string path = "/Users/piotr/Development/C++/minecraft/src/assets";
    // std::string path = "/home/piotr/Development/C++/minecraft/src/assets";
    return path;
}
