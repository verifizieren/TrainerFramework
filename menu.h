#pragma once
#include <string>
#include <vector>
#include <variant>
#include <iostream>
#include <windows.h>

class Menu2 {
private:
    std::vector<std::pair<std::string, std::variant<int*, float*, bool*, std::string*, DWORD*, HANDLE*, std::string>>> features;
    std::string gameName;
    std::string architecture;
    std::string version;
    DWORD procId;
    std::string closeKey;

    void Box(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        std::cout << "[";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        std::cout << "*";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        std::cout << "] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    void DisplayFeature(const std::string& featureName, const std::variant<int*, float*, bool*, std::string*, DWORD*, HANDLE*, std::string>& featureValue) {
        if (std::holds_alternative<std::string>(featureValue)) {
            Box(3);
            std::cout << std::get<std::string>(featureValue) << std::endl;
        }
        else {
            Box(3);
            std::cout << featureName << ": ";

            if (std::holds_alternative<bool*>(featureValue)) {
                int color = *std::get<bool*>(featureValue) ? 10 : 4;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
                std::cout << (*std::get<bool*>(featureValue) ? "Enabled" : "Disabled");
            }
            else if (std::holds_alternative<int*>(featureValue) || std::holds_alternative<float*>(featureValue)) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                if (std::holds_alternative<int*>(featureValue)) {
                    std::cout << *std::get<int*>(featureValue);
                }
                else {
                    std::cout << *std::get<float*>(featureValue);
                }
            }
            else if (std::holds_alternative<std::string*>(featureValue)) {
                std::cout << *std::get<std::string*>(featureValue);
            }
            else if (std::holds_alternative<DWORD*>(featureValue)) {
                std::cout << *std::get<DWORD*>(featureValue);
            }
            else if (std::holds_alternative<HANDLE*>(featureValue)) {
                std::cout << *std::get<HANDLE*>(featureValue);
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            std::cout << std::endl;
        }
    }

public:
    void Header(const std::string& header, const std::string& arch, const std::string& ver, DWORD pid) {
        gameName = header;
        architecture = arch;
        version = ver;
        procId = pid;
    }

    void AddFeature(const std::string& featureName, std::variant<int*, float*, bool*, std::string*, DWORD*, HANDLE*, std::string> featureValue) {
        features.push_back({ featureName, featureValue });
    }

    void UpdateFeature(const std::string& featureName, std::variant<int*, float*, bool*, std::string*, DWORD*, HANDLE*, std::string> featureValue) {
        for (auto& feature : features) {
            if (feature.first == featureName) {
                feature.second = featureValue;
                break;
            }
        }
    }

    void Display() {
        system("cls");
        std::cout << "| Game: " << gameName << std::endl;
        std::cout << "| Architecture: " << architecture << std::endl;
        std::cout << "| Version: " << version << std::endl;
        std::cout << "| Process ID: " << procId << std::endl << std::endl;
        for (const auto& feature : features) {
            DisplayFeature(feature.first, feature.second);
        }
        std::cout << std::endl;
        Box(3);
        std::cout << "Press " << closeKey << " to exit" << std::endl;
    }

    void TextItem(const std::string& text) {
        features.push_back({ text, text });
    }

    void setCloseKey(const std::string& key) {
        closeKey = key;
    }
};
