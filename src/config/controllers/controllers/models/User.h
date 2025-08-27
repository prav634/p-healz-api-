#pragma once
#include <string>

class User
{
public:
    int id;
    std::string name;
    std::string email;
    std::string password;

    User() = default;

    User(int uid, const std::string &uname, const std::string &uemail, const std::string &upassword)
        : id(uid), name(uname), email(uemail), password(upassword) {}
};
