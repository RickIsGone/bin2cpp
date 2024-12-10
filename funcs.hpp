#pragma once

#include <string_view>
#include <filesystem>

namespace fs = std::filesystem;

void imgToHeader(const fs::path& filePath);

void error(std::string_view err);