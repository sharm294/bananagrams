#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace bananas {

/**
 * @brief Given some relative path in this repository, return the absolute path
 * Taken from: https://stackoverflow.com/a/42772814
 * 
 * @param relative_path a relative path in this repository
 * @return std::string 
 */
inline std::string resolvePath(const std::string &relative_path){
    auto base_dir = fs::current_path();
    while (base_dir.has_parent_path()){
        auto combinePath = base_dir / relative_path;
        if (fs::exists(combinePath)){
            return combinePath.string();
        }
        base_dir = base_dir.parent_path();
    }
    throw std::runtime_error("File not found!");
}

} // namespace bananas


