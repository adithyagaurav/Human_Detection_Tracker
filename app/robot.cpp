/**
 * @file robot.cpp
 * @author 
 * Navigator : Rishabh Singh ( )
 * Driver : Adithya Singh (agsingh@umd.edu)
 * UML Design Keeper : Divyansh Agarwal ( )
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 #include "../include/robot.hpp"
 #include "../include/detector.hpp"
 

 acme::Robot::Robot(float focal_length){
    double image_w_ = 416;
    double image_h_ = 416;
    int target_id = 1;
    float conf = 0.75;
    float depth_coeff_ = 0.7
    acme::Detector detector_;
    std::vector<acme::Object> objects = {};
    std::vector<acme::Pose> poses = {};
    float focal_length_= focal_length;
    acme::Tracker tracker_;
 }

 void acme::Robot::run(int mode){
   std::cout<<"Run mode "<<mode<<std::endl;
 }

 void acme::Robot::processImage(std::string image_path){
   std::cout<<"Image Mode running "<<std::endl;
 }

 std::vector<acme::Object> acme::Robot::processStream(){
   acme::Object object1{1, 12.0, 10.0, 30.0, 20.0, 1};
   acme::Object object2{1, 32.0, 27.0, 25.0, 15.0, 1};
   objects.push_back(object1);
   objects.push_back(object2);
   return objects;
 }