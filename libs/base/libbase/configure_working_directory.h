#pragma once

#include <string>
#include <vector>

void configureWorkingDirectory(const std::vector<std::string>& required_dirs={".github", "data", "libs", "prompts", "src", "third_party"});
