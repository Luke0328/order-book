#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "time.h"

#include "book.hpp"
#include "limit.hpp"
#include "order.hpp"

#define MSG_LIMIT 100

using namespace order_book;

int main(int argc, char** argv) {
    (void) argc;
    std::string fn = argv[1];

    std::ifstream file;
    file.open(fn);

    order_book::Book book;

    std::string line;
    std::vector<std::string> order_fields(6);
    std::string field;

    int msg_count = 0;
    while (getline(file, line)) {
        std::cout << line << std::endl;
        std::stringstream ss(line);

        for (int i = 0; i < 6; i++) {
            getline(ss, field, ',');
            order_fields[i] = field;
        }

        int event_type;

        order_book::OrderInfo order_info;

        order_info.eventTime = std::stoi(order_fields[0]);
        event_type = std::stoi(order_fields[1]);
        order_info.idNumber = std::stoi(order_fields[2]);
        order_info.shares = std::stoi(order_fields[3]);
        order_info.limit = std::stoi(order_fields[4]);
        order_info.buyOrSell = std::stoi(order_fields[5]) == 1; // 1 for buy, -1 for sell
        order_info.entryTime = time(NULL);
        
        switch (event_type) {
            case 1:
                std::cout << "ADD" << std::endl;
                book.Add(order_info);
                break;
            case 3:
                std::cout << "DELETE" << std::endl;
                book.Delete(order_info.idNumber);
                break;
            case 4:
                std::cout << "EXECUTE" << std::endl;
                book.Execute(order_info.buyOrSell);
                break;
            default:
                break;
        }
        msg_count++;
    }

    std::cout << msg_count << " messages added to order book." << std::endl;
    std::cout << std::endl;

    book.Print();

    file.close();
    return 0;
}
