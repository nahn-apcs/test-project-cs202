#include <stdexcept>
#include <iostream>
#include <fstream>

#include <Application.hpp>
#include <ResourceID.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

int main () {
    
    try {
        Application app;
        app.run();
    } 
    catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}