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

 
 using namespace cv;
 acme::Robot::Robot(double focal_length){
    double image_w_ = 416;
    double image_h_ = 416;
    int target_id = 1;
    float conf = 0.2;
    float depth_coeff_ = 0.7;
    std::vector<std::string> targetClasses{"person"};
    acme::Detector detector(image_w_, image_h_, targetClasses, conf);
    detector_ = detector;
    std::vector<acme::Object> objects = {};
    std::vector<acme::Pose> poses = {};
    float focal_length_= focal_length;
    acme::Tracker tracker_;
 }

 acme::Robot::~Robot(){

 }

 void acme::Robot::run(int mode){
   std::cout<<"Run mode "<<mode<<std::endl;
   if (mode == 1) {
    std::string imagePath = "../data/image3.jpg";
    processImage(imagePath);
   }
   else if (mode==2){
    processStream();
   }
   else {
    std::cout<<"Invalid mode"<<std::endl;
   }
 }

 void acme::Robot::processImage(std::string imagePath){
   cv::Mat img = cv::imread(imagePath, IMREAD_COLOR);
   cv::Mat resizeImg;
   cv::Size insize = cv::Size(416, 416);
   cv::Size outsize = img.size();
   cv::resize(img, resizeImg, insize);
   std::cout<<"Image Mode running "<<std::endl;
   std::vector<acme::Object> output = detector_.detect(resizeImg);
   acme::Utils utils_;
   utils_.draw(img , output, insize, outsize);
   std::cout<<"Total objects found : "<<output.size()<<std::endl;
   std::cout<<"Image size : "<<img.size().width<<" x "<<img.size().height<<std::endl;
 }

 void acme::Robot::processStream(){
  std::cout<<"Processing stream"<<std::endl;

 }