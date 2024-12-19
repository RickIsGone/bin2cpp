#pragma once

#include <string_view>
#include <filesystem>

namespace fs = std::filesystem;

void binToHeader(const fs::path& filePath);

void error(std::string_view err);