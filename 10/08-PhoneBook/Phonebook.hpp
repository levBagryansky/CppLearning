#include <iostream>
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

using namespace boost::multi_index;

struct Contact {
    int id;
    std::string name;
    std::string phone;

    Contact(int id, std::string name, std::string phone)
        : id(id), name(std::move(name)), phone(std::move(phone)) {}
};

struct by_id {};
struct by_name {};
struct by_phone {};

using phonebook_t = multi_index_container<
    Contact,
    indexed_by<
        ordered_unique<
            tag<by_id>,
            member<Contact, int, &Contact::id>
        >,
        ordered_non_unique<
            tag<by_name>,
            member<Contact, std::string, &Contact::name>
        >,
        hashed_unique<
            tag<by_phone>,
            member<Contact, std::string, &Contact::phone>
        >
    >
>;

class Phonebook {

public:
    void add_contact(const std::string& name, const std::string& phone) {
        contacts.insert(Contact(next_id++, name, phone));
    }

    void find_by_id(int id) {
        auto it = contacts.get<by_id>().find(id);
        std::cout << "ID: " << it->id << ", Name: " << it->name << ", Phone: " << it->phone << std::endl;
    }

    void find_by_name(const std::string& name) const {
        const auto& name_index = contacts.get<by_name>();
        auto range = name_index.equal_range(name);
        for (auto it = range.first; it != range.second; ++it) {
            std::cout << "ID: " << it->id << ", Name: " << it->name << ", Phone: " << it->phone << std::endl;
        }
    }

    void find_by_phone(const std::string& phone) const {
        const auto& phone_index = contacts.get<by_phone>();
        auto it = phone_index.find(phone);
        if (it != phone_index.end()) {
            std::cout << "Found: ID: " << it->id << ", Name: " << it->name << ", Phone: " << it->phone << std::endl;
        } else {
            std::cout << "Phone number not found.\n";
        }
    }

    void print_sorted() const {
        const auto& name_index = contacts.get<by_name>();
        for (const auto& contact : name_index) {
            std::cout << contact.name << " - " << contact.phone << std::endl;
        }
    }

    void remove_by_id(int id) {
        contacts.get<by_id>().erase(id);
    }

private:
    phonebook_t contacts;
    int next_id = 1;
};
