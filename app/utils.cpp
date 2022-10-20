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
    acme::Pose pose3{2, 32.0, 27.0, 25.0, 15.0, 6.0, "person"};
    output.push_back(pose1);
    output.push_back(pose2);
    output.push_back(pose3);
    return output;
 }

 void acme::Utils::draw(cv::Mat frame, std::vector<acme::Object> obj_bboxes, cv::Size insize, cv::Size outsize){
   cv::Mat out_frame = frame.clone();
   cv::Scalar color = cv::Scalar(0, 0, 255);
   cv::Scalar l_color = cv::Scalar::all(255);
   cv::Point tl;
   cv::Point br;
   for (int i=0 ; i<obj_bboxes.size();i++){
      tl = cv::Point((obj_bboxes[i].box_x_/insize.width)*outsize.width, (obj_bboxes[i].box_y_/insize.height)*outsize.height);
      br = cv::Point((obj_bboxes[i].box_x_+obj_bboxes[i].box_w_)*outsize.width/insize.width, (obj_bboxes[i].box_y_+obj_bboxes[i].box_h_)*outsize.height/insize.height);
      cv::rectangle(out_frame, tl, br, color, 1);
   }
   cv::imwrite("../data/out.jpg", out_frame);
 }

 double acme::Utils::calculateIoU(acme::Pose pose1, acme::Pose pose2){
    std::cout<<" IoU is : 0.8"<<std::endl;
    return 0.8;
 }