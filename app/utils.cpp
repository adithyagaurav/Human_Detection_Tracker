/**
 * @file utils.cpp
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

 #include "../include/utils.hpp"

 std::vector<acme::Pose> acme::Utils::getFinalBoxes(std::vector<acme::Object> bboxes, float depth_coeff){
    std::vector<acme::Pose> output;
    acme::Pose pose1{1, 12.0, 10.0, 30.0, 20.0, 5.0, "person"};
    acme::Pose pose2{2, 32.0, 27.0, 25.0, 15.0, 6.0, "person"};
    output.push_back(pose1);
    output.push_back(pose2);
    return output;
 }

 void acme::Utils::draw(cv::Mat frame, std::vector<acme::Pose> pose_bboxes){
    std::cout<<"Output drawn on input image and displaying"<<std::endl;
 }

 double acme::Utils::calculateIoU(acme::Pose pose1, acme::Pose pose2){
    std::cout<<" IoU is : 0.8"<<std::endl;
    return 0.8;
 }