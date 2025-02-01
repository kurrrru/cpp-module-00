#ifndef EX01_PHONEBOOK_HPP_
#define EX01_PHONEBOOK_HPP_

#include <string>
#include "Contact.hpp"

class PhoneBook {
 private:
    static const std::size_t _contactSize = 8;
    static const std::size_t _printWidth = 10;
    static const std::size_t _indexWhenEOF = 0;
    Contact _contacts[_contactSize];
    std::size_t _lastId;
    std::size_t _getLastIndex() const;
    bool _isReplaceContact() const;
    bool _addContact();
    bool _searchContact() const;
    void _displayString(const std::string &str) const;
    std::size_t _getIndexFromInput() const;

 public:
    PhoneBook();
    PhoneBook(const PhoneBook &phoneBook);
    PhoneBook &operator=(const PhoneBook &phoneBook);
    ~PhoneBook();
    void startInteractivePrompt();
};

#endif  // EX01_PHONEBOOK_HPP_
