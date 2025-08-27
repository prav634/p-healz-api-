cmake_minimum_required(VERSION 3.15)
project(p-healz-api)

set(CMAKE_CXX_STANDARD 17)

# Enable vcpkg integration if available
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()

# Add source files
add_executable(p-healz-api src/main.cpp)

# Find dependencies
find_package(Drogon CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)

# Link dependencies
target_link_libraries(p-healz-api
    PRIVATE Drogon::Drogon
    PRIVATE spdlog::spdlog
    PRIVATE nlohmann_json::nlohmann_json
    PRIVATE SQLite::SQLite3
)
