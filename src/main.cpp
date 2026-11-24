#include "core/application.h"

#include <iostream>

int main(){
    Application application;

    if(!application.Initialize()){
        std::cout << "Application initialize failed" << std::endl;
        return -1;
    }

    application.Run();

    application.Shutdow();

    return 0;
}
