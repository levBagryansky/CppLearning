#pragma once

#include <filesystem>
#include <chrono>
#include <iostream>

namespace fs = std::filesystem;

void deleteOlds(const fs::path& directory, const std::chrono::system_clock::time_point& time_point)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        try
        {
            auto ftime = fs::last_write_time(entry);

            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
            );

            if (sctp < time_point)
            {
                if (fs::is_directory(entry))
                    fs::remove_all(entry.path());
                else
                    fs::remove(entry.path());

                std::cout << "Deleted: " << entry.path() << "\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error processing " << entry.path() << " : " << e.what() << "\n";
        }
    }
}
