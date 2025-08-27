#include <drogon/drogon.h>

int main() {
    // Create a simple GET endpoint
    drogon::app().registerHandler(
        "/hello",
        [](const drogon::HttpRequestPtr &req,
           std::function<void (const drogon::HttpResponsePtr &)> callback) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setBody("Hello, P-Healz API!");
            callback(resp);
        }
    );

    // Run the app on port 8080
    drogon::app().addListener("0.0.0.0", 8080).run();
    return 0;
}
