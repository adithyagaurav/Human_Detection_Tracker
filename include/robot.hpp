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
 #include <opencv2/opencv.hpp>
 #include <opencv2/core/core.hpp>
 #include <opencv2/imgcodecs.hpp>


 namespace acme{

 class Robot{
    public:
    void run(int mode);
    void processImage(std::string image_path);
    void processStream();
    Robot(double focalLength);
    ~Robot();
    private:
    acme::Detector detector_;
    std::vector<acme::Pose> poses;
    float depth_coeff_;
    float focal_length_;
    std::vector<acme::Object> objects;
    acme::Tracker tracker_;
 };
}

#endif