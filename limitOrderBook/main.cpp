#include "./generateOrders/generateOrders.hpp"
#include "./processOrders/orderPipeline.hpp"
#include "./limitOrderBook/Book.hpp"
#include "./limitOrderBook/Limit.hpp"
#include "./limitOrderBook/Order.hpp"
#include <iostream>
#include <vector>
#include <chrono>

int main() {
    Book* book = new Book();

    OrderPipeline orderPipeline(book);

    GenerateOrders generateOrders(book);

    generateOrders.createInitialOrders(10000, 300);

    orderPipeline.processOrdersFromFile("/home/cv1/mark/limitOrderBook/generateOrders/initialOrders.txt");

    generateOrders.createOrders(5000000);


    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    orderPipeline.processOrdersFromFile("/home/cv1/mark/limitOrderBook/generateOrders/orders.txt");

    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time taken to process orders: " << duration.count() << " milliseconds" << std::endl;

    delete book;
    return 0;
}
