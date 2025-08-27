#include "UserController.h"
#include "../models/User.h"
#include <drogon/HttpResponse.h>
#include <drogon/orm/DbClient.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>

using namespace drogon;
using namespace drogon::orm;

void UserController::signup(const HttpRequestPtr &req,
                            std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    if (!json || !json->isMember("name") || !json->isMember("email") || !json->isMember("password"))
    {
        auto resp = HttpResponse::newHttpJsonResponse(Json::Value("Invalid input"));
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto dbClient = app().getDbClient();
    *dbClient << "INSERT INTO users (name, email, password) VALUES($1,$2,$3)"
              << (*json)["name"].asString()
              << (*json)["email"].asString()
              << (*json)["password"].asString()
              >> [callback](const Result &r) {
                     Json::Value res;
                     res["message"] = "User registered successfully";
                     auto resp = HttpResponse::newHttpJsonResponse(res);
                     callback(resp);
                 }
              >> [callback](const DrogonDbException &e) {
                     LOG_ERROR << e.base().what();
                     auto resp = HttpResponse::newHttpJsonResponse(Json::Value("Database error"));
                     resp->setStatusCode(k500InternalServerError);
                     callback(resp);
                 };
}

void UserController::login(const HttpRequestPtr &req,
                           std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    if (!json || !json->isMember("email") || !json->isMember("password"))
    {
        auto resp = HttpResponse::newHttpJsonResponse(Json::Value("Invalid input"));
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto dbClient = app().getDbClient();
    *dbClient << "SELECT id, name, email FROM users WHERE email=$1 AND password=$2"
              << (*json)["email"].asString()
              << (*json)["password"].asString()
              >> [callback](const Result &r) {
                     if (r.size() == 0)
                     {
                         auto resp = HttpResponse::newHttpJsonResponse(Json::Value("Invalid credentials"));
                         resp->setStatusCode(k401Unauthorized);
                         callback(resp);
                         return;
                     }
                     Json::Value user;
                     user["id"] = r[0]["id"].as<int>();
                     user["name"] = r[0]["name"].as<std::string>();
                     user["email"] = r[0]["email"].as<std::string>();
                     auto resp = HttpResponse::newHttpJsonResponse(user);
                     callback(resp);
                 }
              >> [callback](const DrogonDbException &e) {
                     LOG_ERROR << e.base().what();
                     auto resp = HttpResponse::newHttpJsonResponse(Json::Value("Database error"));
                     resp->setStatusCode(k500InternalServerError);
                     callback(resp);
                 };
}
