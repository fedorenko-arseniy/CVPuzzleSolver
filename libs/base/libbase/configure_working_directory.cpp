#include "configure_working_directory.h"

#include <libbase/runtime_assert.h>

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void configureWorkingDirectory(const std::vector<std::string>& required_dirs)
{
    if (required_dirs.empty())
        return;

    const fs::path start = fs::current_path();
    fs::path cur = start;

    auto first_missing_dir = [&](const fs::path& base) -> std::string {
        std::error_code ec;
        for (const std::string& d : required_dirs)
        {
            const fs::path p = base / d;
            if (!fs::exists(p, ec) || !fs::is_directory(p, ec))
                return d;
        }
        return {};
    };

    while (true)
    {
        const std::string missing = first_missing_dir(cur);
        if (missing.empty())
        {
            // All required directories found in "cur"
            if (cur != start)
            {
                fs::current_path(cur);
                std::cout << "Working directory auto-changed to: "
                          << fs::current_path().string() << "\n";
            }
            return; // If already good at start: no output, no change.
        }

        if (cur == start) {
            std::cout << "Can't find " << missing
                      << " in current working directory: " << cur.string() << "\n";
        }

        const fs::path parent = cur.parent_path();
        if (parent == cur || parent.empty())
            break; // Reached filesystem root (or cannot go up further)

        cur = parent;
    }

    rassert(false, "Can't automatically find working directory!", start);
}
