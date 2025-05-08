#include <gtest/gtest.h>
#include <fstream>

#include "remove.hpp"

namespace fs = std::filesystem;

class DeleteOldsTest : public ::testing::Test
{
protected:
    fs::path temp_dir;

    void SetUp() override
    {
        temp_dir = fs::temp_directory_path() / "delete_olds_test_dir";
        fs::create_directory(temp_dir);

        createFile(temp_dir / "old_file.txt", true);   // old
        createFile(temp_dir / "new_file.txt", false);  // new
    }

    void TearDown() override
    {
        if (fs::exists(temp_dir))
        {
            fs::remove_all(temp_dir);
        }
    }

    void createFile(const fs::path& filepath, bool make_old)
    {
        std::ofstream ofs(filepath);
        ofs << "test" << std::endl;
        ofs.close();

        if (make_old)
        {
            fs::last_write_time(filepath, fs::file_time_type::clock::now() - std::chrono::hours(24 * 365));
        }
    }
};

TEST_F(DeleteOldsTest, DeletesOnlyOldFiles)
{
    auto threshold = std::chrono::system_clock::now() - std::chrono::hours(24 * 30); // 30 days ago

    deleteOlds(temp_dir, threshold);

    EXPECT_FALSE(fs::exists(temp_dir / "old_file.txt")) << "Old file should be deleted.";
    EXPECT_TRUE(fs::exists(temp_dir / "new_file.txt")) << "New file should NOT be deleted.";
}
