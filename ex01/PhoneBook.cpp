#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _lastId(0) {}

PhoneBook::PhoneBook(const PhoneBook &phoneBook) {
    _lastId = phoneBook._lastId;
    for (std::size_t i = 0; i < _contactSize; i++) {
        _contacts[i] = phoneBook._contacts[i];
    }
}

PhoneBook &PhoneBook::operator=(const PhoneBook &phoneBook) {
    if (this == &phoneBook)
        return *this;
    _lastId = phoneBook._lastId;
    for (std::size_t i = 0; i < _contactSize; i++) {
        _contacts[i] = phoneBook._contacts[i];
    }
    return *this;
}

PhoneBook::~PhoneBook() {}

std::size_t PhoneBook::_getLastIndex() const {
    return (_lastId - 1) % _contactSize;
}

bool PhoneBook::_isReplaceContact() const {
    return _lastId > _contactSize;
}

void PhoneBook::_displayString(const std::string &str) const {
    std::string strCopy;
    if (str.length() > _printWidth)
        strCopy = str.substr(0, _printWidth - 1) + ".";
    else
        strCopy = str;
    std::cout << std::setw(_printWidth) << strCopy;
}

bool PhoneBook::_addContact() {
    _lastId++;
    if (_isReplaceContact())
        std::cout << \
        "Phone book is full. The oldest contact will be replaced." << std::endl;
    Contact contact;
    if (!contact.setInfoWithPrompt(Contact::FIRST_NAME))
        return false;
    if (!contact.setInfoWithPrompt(Contact::LAST_NAME))
        return false;
    if (!contact.setInfoWithPrompt(Contact::NICKNAME))
        return false;
    if (!contact.setInfoWithPrompt(Contact::PHONE_NUMBER))
        return false;
    if (!contact.setInfoWithPrompt(Contact::DARKEST_SECRET))
        return false;
    _contacts[_getLastIndex()] = contact;
    return true;
}

std::size_t PhoneBook::_getIndexFromInput() const {
    std::size_t index;
    while (true) {
        std::cout << "Enter the index of the contact: ";
        std::string indexStr;
        if (!std::getline(std::cin, indexStr))
            return _indexWhenEOF;
        if (indexStr.empty()) {
            std::cout << "Invalid index." << std::endl;
            continue;
        }
        std::stringstream ss(indexStr);
        ss >> index;
        if (ss.fail() || !ss.eof()) {
            std::cout << "Invalid index." << std::endl;
            continue;
        }
        if (index < 1 || index > _lastId) {
            std::cout << "Invalid index." << std::endl;
            continue;
        }
        return index;
    }
}

bool PhoneBook::_searchContact() const {
    if (_lastId == 0) {
        std::cout << "Phone book is empty." << std::endl;
        return false;
    }
    std::cout << std::setw(_printWidth) << "Index" << "|";
    std::cout << std::setw(_printWidth) << "First name" << "|";
    std::cout << std::setw(_printWidth) << "Last name" << "|";
    std::cout << std::setw(_printWidth) << "Nickname" << std::endl;
    for (std::size_t i = 0; i < _contactSize && i < _lastId; i++) {
        std::cout << std::setw(_printWidth) << i + 1 << "|";
        _displayString(_contacts[i].getInfo(Contact::FIRST_NAME));
        std::cout << "|";
        _displayString(_contacts[i].getInfo(Contact::LAST_NAME));
        std::cout << "|";
        _displayString(_contacts[i].getInfo(Contact::NICKNAME));
        std::cout << std::endl;
    }
    std::size_t index = _getIndexFromInput();
    if (index == _indexWhenEOF)
        return false;
    _contacts[index - 1].displayInfo();
    return true;
}

void PhoneBook::startInteractivePrompt() {
    std::string command;
    while (true) {
        std::cout << "Enter a command: ";
        if (!std::getline(std::cin, command)) {
            std::cout << std::endl;
            break;
        }
        if (command == "EXIT") {
            break;
        } else if (command == "ADD") {
            if (!_addContact()) {
                std::cout << std::endl;
                break;
            }
        } else if (command == "SEARCH") {
            if (!_searchContact()) {
                std::cout << std::endl;
                break;
            }
        } else {
            std::cout << "Invalid command." << std::endl;
        }
    }
}
