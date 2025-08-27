#pragma once
#include <drogon/HttpController.h>

using namespace drogon;

class HelloController : public drogon::HttpController<HelloController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HelloController::hello, "/hello", Get); // GET /hello
    METHOD_LIST_END

    void hello(const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Hello from P-Healz API 🚀");
        callback(resp);
    }
};
