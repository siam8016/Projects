#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>

class Pomodoro {
private:
    int w; 
    int b; 
    bool r; 

public:
    Pomodoro(int w1, int b1)
        : w(w1), b(b1), r(false) {}

    void start() {
        if (r) {
            std::cout << "Timer is already running!" << std::endl;
            return;
        }

        r = true;
        std::cout << "Pomodoro Has Started!" << std::endl;

        while (w > 0 && r) {
            display(w, "Focus");
            std::this_thread::sleep_for(std::chrono::seconds(1));
            w--;
        }

        if (w <= 0) {
            std::cout << "\nTime for a break!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2)); 

            while (b > 0 && r) {
                display(b, "Grab a Coffee");
                std::this_thread::sleep_for(std::chrono::seconds(1));
                b--;
            }
        }

        reset();
    }

    void stop() {
        r = false;
        std::cout << "Pomodoro Has Stopped!" << std::endl;
        reset(); 
    }

    void reset() {
        r = false;
        w = 0;
        b = 0;
    }

private:
    void display(int seconds, const std::string& activity) const {
        int minutes = seconds / 60;
        int remaining = seconds % 60;
        std::cout << "\r" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << remaining
                  << " " << activity << " " << std::flush;
    }
};

int main() {
    int w; 
    int b; 

    std::cout << "How long do you want to work? ";
    std::cin >> w;
    w *= 60; 

    std::cout << "Resting is important too; How long do you want to rest? ";
    std::cin >> b;
    b *= 60; 

    Pomodoro t(w, b);

    while (true) {
        char choice;
        std::cout << "Press 's' to start the Pomodoro session or 'q' to quit the Pomodoro App: ";
        std::cin >> choice;

        if (choice == 's') {
            t.start();
        } else if (choice == 'q') {
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
