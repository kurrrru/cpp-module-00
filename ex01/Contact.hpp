#pragma once

#include <string>

class Contact {
 public:
    enum InfoType {
        FIRST_NAME,
        LAST_NAME,
        NICKNAME,
        PHONE_NUMBER,
        DARKEST_SECRET
    };

 private:
    static const int _infoSize = 5;
    static const int _printWidth = 15;
    std::string _info[_infoSize];
    bool _isInvalidPhoneNumber(const std::string &phoneNumber);
    void _displayPrompt(InfoType type) const;

 public:
    Contact();
    Contact(const Contact &contact);
    Contact &operator=(const Contact &contact);
    ~Contact();
    bool setInfo(InfoType type, const std::string &info);
    bool setInfoWithPrompt(InfoType type);
    std::string getInfo(InfoType type) const;
    void displayInfo() const;
};
