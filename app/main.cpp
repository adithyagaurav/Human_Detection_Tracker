#include <iostream>
#include "../include/robot.hpp"

int main()
{
    int mode;
    double focalLength;
    std::cout<<"Select run mode : {1 : Image mode, 2 : Stream mode}";
    std::cin>>mode;
    std::cout<<std::endl;
    std::cout<<"Enter focal length : ";
    std::cin>>focalLength;
    std::cout<<std::endl;
    acme::Robot robot(focalLength);
    robot.run(mode);
}
