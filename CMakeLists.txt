cmake_minimum_required(VERSION 3.18.0)

project(limitOrderBook VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")


set(Headers
    ./limitOrderBook/Book.hpp
    ./limitOrderBook/Limit.hpp
    ./limitOrderBook/Order.hpp
    ./processOrders/orderPipeline.hpp
    ./generateOrders/generateOrders.hpp
)
set(Sources
    ./limitOrderBook/Book.cpp
    ./limitOrderBook/Limit.cpp
    ./limitOrderBook/Order.cpp
    ./processOrders/orderPipeline.cpp
    ./generateOrders/generateOrders.cpp
)

# Define the library target
add_library(${PROJECT_NAME}_lib STATIC ${Sources} ${Headers})

# Define the executable target
add_executable(${PROJECT_NAME} main.cpp)

# Link the executable with the library
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
