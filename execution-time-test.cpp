#include <exception>
#include <iostream>
#include <string>
#include "circular-buffer.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <type> <number_of_elements>" << endl;
        return 1;
    }

    try {
        int type = std::stoi(argv[1]);
        int n = std::stoi(argv[2]);

        CircularDeque cd = CircularDeque(n);

        auto start = high_resolution_clock::now();
        switch (type) {
            case 0:
            {
                for (int i = 0; i < n; i++)
                    cd.push_back(42);
                break;
            }
            case 1:
            {
                for (int i = 0; i < n; i++)
                    cd.push_front(42);
                break;
            }
            default:
            {
                cout << "Error: type is not correct. It should be 0 for push_back or 1 for push_front.";
                return 1;
            }
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        cout << (elapsed.count() / n) << endl;
    } catch (const std::exception& e) {
        cout << "Error: params are not a number: " << e.what() << endl;
        return 1;
    }
}
