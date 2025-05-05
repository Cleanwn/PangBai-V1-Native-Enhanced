#pragma once
#include "nlohmann/json.hpp"
#include <fstream>
#include <imgui.h>

namespace MdayS
{
    template <typename T>
    static bool save_json(const std::string& path, const std::string& key, const T& value)
    {
        nlohmann::json j;
        std::ifstream file(path);
        if (file.good()) {
            file >> j;
        }
        j[key] = value;
        file.close();

        std::ofstream out_file(path);
        out_file << std::setw(4) << j;
        out_file.close();

        return true;
    }

    static bool save_json_color(const std::string& path, const std::string& key, const ImColor color)
    {
        nlohmann::json j;
        std::ifstream file(path);
        if (file.good()) {
            file >> j;
        }

        j[key]["R"] = color.Value.x;
        j[key]["G"] = color.Value.y;
        j[key]["B"] = color.Value.z;
        j[key]["A"] = color.Value.w;
        file.close();

        std::ofstream out_file(path);
        out_file << std::setw(4) << j;
        out_file.close();

        return true;
    }

    static bool load_json_color(const std::string& path, const std::string& key, ImColor& color) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return false;
        }

        nlohmann::json j;
        file >> j;

        if (!j.contains(key)) {
            return false;
        }

        if (!j[key].contains("R") || !j[key].contains("G") || !j[key].contains("B") || !j[key].contains("A")) {
            return false;
        }

        color = ImColor(
            j[key]["R"].get<float>(),
            j[key]["G"].get<float>(),
            j[key]["B"].get<float>(),
            j[key]["A"].get<float>()
        );

        file.close();
        return true;
    }

    template <typename T>
    static bool load_json(const std::string& path, const std::string& key, T& value)
    {
        nlohmann::json j;
        std::ifstream file(path);

        if (!file.is_open()) {
            return false;
        }

        file >> j;
        if (j.contains(key)) {
            value = j[key].get<T>();
            return true;
        }
        else {
            return false;
        }
    }

    static bool save_json(const std::string& path, const std::map<std::string, std::string>& data)
    {
        nlohmann::json j;
        std::ifstream file(path);
        if (file.good()) {
            file >> j;
        }

        for (const auto& kv : data) {
            j[std::string(kv.first)] = kv.second;
        }
        file.close();

        std::ofstream out_file(path);
        out_file << std::setw(4) << j;
        out_file.close();

        return true;
    }

    static bool save_json(const std::string& path, const std::map<std::string, uint64_t>& data)
    {
        nlohmann::json j;
        std::ifstream file(path);
        if (file.good()) {
            file >> j;
        }

        for (const auto& kv : data) {
            j[std::string(kv.first)] = kv.second;
        }
        file.close();

        std::ofstream out_file(path);
        out_file << std::setw(4) << j;
        out_file.close();

        return true;
    }

    static bool load_json(const std::string& path, std::map<std::string, std::string>& data)
    {
        data.clear();

        nlohmann::json j;
        std::ifstream file(path);

        if (!file.is_open()) {
            return false;
        }

        file >> j;
        for (auto it = j.begin(); it != j.end(); ++it) {
            if (!it.key().empty() && it.value().is_string()) {
                std::string key = it.key();
                std::string value = it.value();
                data.insert({ key, value });
            }
        }

        return true;
    }

    static bool load_json(const std::string& path, std::map<std::string, uint64_t>& data)
    {
        data.clear();

        nlohmann::json j;
        std::ifstream file(path);

        if (!file.is_open()) {
            return false;
        }

        file >> j;
        for (auto it = j.begin(); it != j.end(); ++it) {
            if (!it.key().empty() && it.value().is_string()) {
                std::string key = it.key();
                uint64_t value = it.value();
                data.insert({ key, value });
            }
        }

        return true;
    }

    static bool does_key_exist_in_json(const std::string& path, std::string key)
    {
        nlohmann::json j;
        std::ifstream file(path);

        if (!file.is_open()) {
            return false;
        }

        file >> j;
        if (j.contains(key)) {
            return true;
        }

        return false;
    }

    template <typename T>
    static bool load_json_str(const std::string& json_str, const std::string& key, T& value)
    {
        // 解析 JSON 字符串
        nlohmann::json j = nlohmann::json::parse(json_str, nullptr, false);  // 使用 `false` 禁用异常处理

        if (j.is_discarded()) {
            return false; // 如果 JSON 解析失败，返回 false
        }

        // 查找 key 并赋值
        if (j.contains(key)) {
            value = j[key].get<T>();
            return true;
        }
        else {
            return false;
        }
    }

#define SAVE_JSON(KEY, VALUE) save_json(path, xorstr(#KEY), VALUE)
}
