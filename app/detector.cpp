/**
 * @file detector.cpp
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

 #include "../include/detector.hpp"
 #include <iostream>
 #include <opencv2/opencv.hpp>

 acme::Detector::Detector(double img_w, double img_h, int target_id, float conf){
    image_h = img_h;
    image_w = img_w;
    target_class_idx = target_id;
    conf_thresh = conf;
    acme::Detector::initModel();
 }

 void acme::Detector::initModel(){
    std::cout<<"Loaded Model"<<std::endl;
 }

 std::vector<acme::Object> detect(cv::Mat frame){
    std::vector<acme::Object> output;
    acme::Object object1{1, 12.0, 10.0, 30.0, 20.0, 1};
    acme::Object object2{1, 32.0, 27.0, 25.0, 15.0, 1};
    output.push_back(object1);
    output.push_back(object2);
    return output;
 }