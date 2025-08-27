#pragma once
#include <drogon/HttpController.h>

using namespace drogon;

class UserController : public drogon::HttpController<UserController>
{
public:
    METHOD_LIST_BEGIN
    // Signup endpoint: POST /user/signup
    ADD_METHOD_TO(UserController::signup, "/user/signup", Post);

    // Login endpoint: POST /user/login
    ADD_METHOD_TO(UserController::login, "/user/login", Post);
    METHOD_LIST_END

    // Handle signup request
    void signup(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);

    // Handle login request
    void login(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback);
};
