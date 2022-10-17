/**
 * @file robot.hpp
 * @author 
 * Navigator : Rishabh Singh ( )
 * Driver : Adithya Singh (agsingh@umd.edu)
 * @brief 
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 #ifndef INCLUDE_ROBOT_HPP_
 #define INCLUDE_ROBOT_HPP_

 #include <iostream>
 #include <vector>
 #include "tracker.hpp"
 #include "utils.hpp"
 #include "detector.hpp"

 namespace acme{

 class Robot{
    public:
    void run(int mode);
    void processImage(std::string image_path);
    std::vector<acme::Object> processStream();
    Robot(float focalLength);
    ~Robot();
    private:
    Detector detector_;
    Pose pose_;
    float depth_coeff_;
    float focal_length_;
    std::vector<acme::Object> objects;
    Tracker tracker_;
 };
}

#endif