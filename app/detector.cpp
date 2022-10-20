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
#include <vector>

 acme::Detector::Detector(double imgW, double imgH, std::vector<std::string> targets, float conf){
    imgH_ = imgH;
    imgW_ = imgW;
    targetClasses_ = targets;
    confThresh_ = conf;
    float nmsThresh_=0.2;
    acme::Detector::initModel();
 }
 
 acme::Detector::Detector(){

 }
 acme::Detector::~Detector(){
   
 }

 void acme::Detector::initModel(){
    std::cout<<"Loaded Model"<<std::endl;
    net_ = cv::dnn::readNet("../model/yolov4-tiny.cfg", "../model/yolov4-tiny.weights");
    net_.setPreferableBackend(0);
    net_.setPreferableTarget(0);
    
    allClasses_ = {"person", "bicycle", "car", "motorbike", "aeroplane", 
    "bus", "train", "truck", "boat", "traffic light", "fire hydrant", 
    "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", 
    "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack", 
    "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", 
    "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", 
    "surfboard", "tennis racket", "bottle", "wine glass", "cup", "fork", 
    "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange", 
    "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", 
    "sofa", "pottedplant", "bed", "diningtable", "toilet", "tvmonitor",
     "laptop", "mouse", "remote", "keyboard", "cell phone", "microwave", 
     "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", 
    "scissors", "teddy bear", "hair drier", "toothbrush"};

    cv::Mat temp = cv::Mat::zeros(cv::Size(416,416), CV_8UC3);
    acme::Detector::preProcess(temp);
 }

 void acme::Detector::preProcess(const cv::Mat &frame){
   cv::Mat blob;
   if (!frame.empty()){
      blob=cv::dnn::blobFromImage(frame, 1/255.0, cv::Size(imgW_, imgH_), cv::Scalar(), true, false);
      net_.setInput(blob);
      outputs_.clear();
      net_.forward(outputs_, net_.getUnconnectedOutLayersNames());
   }
   else{
      std::cout<<"Image invalid";
   }
 }

 std::vector<acme::Object> acme::Detector::postProcess(cv::Size &s){
   std::vector<acme::Object> detections;
   std::vector<std::string> class_names;
   std::vector<float> confidences;
   std::vector<cv::Rect> bboxes;
   std::vector<int> indices;

   for (cv::Mat &out:outputs_){
      std::cout<<"***"<<std::endl;
      auto *data = reinterpret_cast<float*>(out.data);
      for (int i=0 ; i<out.rows; i++, data+=out.cols){
         int xCenter = static_cast<int>(data[0]*s.width);
         int yCenter = static_cast<int>(data[1]*s.height);
         cv::Mat scores = out.row(i).colRange(5, out.cols);
         cv::Point classIdPoint;
         double confidence;
         cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
         if (confidence > confThresh_){
            
            int classId = classIdPoint.x;
            std::string className = allClasses_[classId];
            
            auto iter = std::find(targetClasses_.begin(), targetClasses_.end(), className);
            if ( iter != targetClasses_.end() ) {
               xCenter = std::max(0, xCenter);
               yCenter =  std::max(0, yCenter);

               /// get detected bbox width
               int width = static_cast<int>(data[2]*s.width);

               /// get detected bbox height
               int height = static_cast<int>(data[3]*s.height);

               /// calculate x - top left coordinate
               int xLeft = xCenter - width / 2;

               /// calculate y - top left coordinate
               int yTop = yCenter - height / 2;

               /// create a cv::Rect object
               cv::Rect bbox(xLeft, yTop, width, height);

               /// store the class names in a vector
               class_names.push_back(className);

               /// store the confidences in a vector
               confidences.push_back(static_cast<float>(confidence));

               /// store the bbox in a vector
               bboxes.push_back(bbox);
            }
      }
   }
}
cv::dnn::NMSBoxes(bboxes, confidences, confThresh_, nmsThresh_, indices);
std::cout<<indices.size();
for ( int index : indices ) {
   cv::Rect bbox = bboxes[index];
   double conf = static_cast<double>(confidences[index]);
   std::string name = class_names[index];
   std::cout<<"Class found: "<<name<<std::endl;

   /// create Detection object
   acme::Object box{0, bbox.x, bbox.y, bbox.height, bbox.width, name};

   /// store the Detection objects in a vector
   detections.push_back(box);
}
return detections;
}


 std::vector<acme::Object> acme::Detector::detect(cv::Mat frame){
    std::vector<acme::Object> output;
    std::vector<cv::Mat> detections;
    acme::Detector::preProcess(frame);
    cv::Size size = frame.size();
    output = acme::Detector::postProcess(size);
    return output;
 }