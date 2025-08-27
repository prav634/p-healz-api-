cmake_minimum_required(VERSION 3.10)
project(PHealzAPI)

set(CMAKE_CXX_STANDARD 17)

# Add all source files here
add_executable(phealz
    main.cpp
    models/Customer.cpp
    models/Order.cpp
    services/CustomerService.cpp
    services/OrderService.cpp
)

