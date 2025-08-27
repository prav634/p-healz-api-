cmake_minimum_required(VERSION 3.5)
project(p_healz_api)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Find Drogon
find_package(Drogon REQUIRED)

# Find SQLite
find_package(SQLite3 REQUIRED)

# Source files
add_executable(${PROJECT_NAME}
    main.cpp
    controllers/UserController.cpp
    models/User.cpp
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    Drogon::Drogon
    SQLite::SQLite3
)
