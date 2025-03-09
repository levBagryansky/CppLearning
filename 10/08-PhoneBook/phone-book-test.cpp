#include <gtest/gtest.h>

#include "Phonebook.hpp"

TEST(PhonebookTest, AddContact) {
    Phonebook pb;
    pb.add_contact("Ivanov", "12345");
    pb.add_contact("Petrov", "67890");


    testing::internal::CaptureStdout();
    pb.find_by_name("Ivanov");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Ivanov"), std::string::npos);

    testing::internal::CaptureStdout();
    pb.find_by_name("Petrov");
    output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Petrov"), std::string::npos);
}

TEST(PhonebookTest, FindByName) {
    Phonebook pb;
    pb.add_contact("Sidorov", "55555");
    pb.add_contact("Ivanov", "11111");
    pb.add_contact("Sidorov", "22222");

    testing::internal::CaptureStdout();
    pb.find_by_name("Sidorov");
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << output << std::endl;
    EXPECT_NE(output.find("Sidorov, Phone: 55555"), std::string::npos);
    EXPECT_NE(output.find("Sidorov, Phone: 55555"), std::string::npos);
}

TEST(PhonebookTest, FindByPhone) {
    Phonebook pb;
    pb.add_contact("Kuznetsov", "99999");

    testing::internal::CaptureStdout();
    pb.find_by_phone("99999");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Kuznetsov"), std::string::npos);
}

TEST(PhonebookTest, FindById) {
    Phonebook pb;
    pb.add_contact("Smith", "44444");

    const int search_id = 1;
    testing::internal::CaptureStdout();
    pb.find_by_id(search_id);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Smith"), std::string::npos);
}

TEST(PhonebookTest, SortedOutput) {
    Phonebook pb;
    pb.add_contact("Zorin", "77777");
    pb.add_contact("Andreev", "33333");
    pb.add_contact("Borisov", "66666");

    testing::internal::CaptureStdout();
    pb.print_sorted();
    std::string output = testing::internal::GetCapturedStdout();

    size_t pos1 = output.find("Andreev");
    size_t pos2 = output.find("Borisov");
    size_t pos3 = output.find("Zorin");

    EXPECT_LT(pos1, pos2);
    EXPECT_LT(pos2, pos3);
}

TEST(PhonebookTest, RemoveById) {
    Phonebook pb;
    pb.add_contact("Volkov", "88888");
    pb.add_contact("Stepanov", "77777");

    pb.remove_by_id(1);

    testing::internal::CaptureStdout();
    pb.print_sorted();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.find("Volkov"), std::string::npos);
    EXPECT_NE(output.find("Stepanov"), std::string::npos);
}
