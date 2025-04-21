#include <iomanip>
#include <iostream>
#include <string>
#include "Contact.hpp"

Contact::Contact() {
    _info[FIRST_NAME] = "";
    _info[LAST_NAME] = "";
    _info[NICKNAME] = "";
    _info[PHONE_NUMBER] = "";
    _info[DARKEST_SECRET] = "";
}

Contact::Contact(const Contact &contact) {
    for (int i = 0; i < _infoSize; i++) {
        _info[i] = contact._info[i];
    }
}

Contact &Contact::operator=(const Contact &contact) {
    if (this == &contact)
        return *this;
    for (int i = 0; i < _infoSize; i++) {
        _info[i] = contact._info[i];
    }
    return *this;
}

Contact::~Contact() {}

bool Contact::_isInvalidPhoneNumber(const std::string &phoneNumber) {
    for (std::size_t i = 0; i < phoneNumber.length(); i++) {
        if (std::isdigit(phoneNumber[i]))
            return false;
    }
	std::cout << "The phone number must contain at least one digit." << std::endl;
    return true;
}

void Contact::_displayPrompt(InfoType type) const {
    const std::string infoNames[] = {
        "First name",
        "Last name",
        "Nickname",
        "Phone number",
        "Darkest secret"
    };
    std::cout << std::setw(_printWidth) << infoNames[type] << ": ";
}

bool Contact::setInfo(InfoType type, const std::string &info) {
    if (info.empty())
        return false;
    switch (type) {
        case PHONE_NUMBER:
            if (_isInvalidPhoneNumber(info))
                return false;
            break;
        default:
            break;
    }
    _info[type] = info;
    return true;
}

bool Contact::setInfoWithPrompt(InfoType type) {
    while (true) {
        _displayPrompt(type);
        std::string info;
        if (!std::getline(std::cin, info))
            return false;
        if (setInfo(type, info))
            return true;
        std::cout << "Invalid input. Please try again." << std::endl;
    }
}

std::string Contact::getInfo(InfoType type) const {
    return _info[type];
}

void Contact::displayInfo() const {
    const std::string infoNames[] = {
        "First name",
        "Last name",
        "Nickname",
        "Phone number",
        "Darkest secret"
    };
    for (int i = 0; i < _infoSize; i++) {
        std::cout << std::setw(_printWidth) << infoNames[i]
            << ": " << _info[i] << std::endl;
    }
}
