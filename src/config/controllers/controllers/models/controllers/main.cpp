#include <drogon/drogon.h>

int main()
{
    // Set server port
    drogon::app().addListener("0.0.0.0", 8080);

    // Load configuration (from config.json if present)
    drogon::app().loadConfigFile("config.json");

    // Start the server
    drogon::app().run();

    return 0;
}
