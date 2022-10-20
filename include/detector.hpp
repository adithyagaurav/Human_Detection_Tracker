/**
 * @file detector.hpp
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

 #ifndef INCLUDE_DETECTOR_HPP_
 #define INCLUDE_DETECTOR_HPP_
 #include<iostream>
 #include<vector>
 #include <opencv2/opencv.hpp>
 #include <opencv2/core/core.hpp>
 #include <opencv2/imgcodecs.hpp>
 #include <opencv2/dnn/dnn.hpp>
 #include <opencv2/dnn/shape_utils.hpp>


 namespace acme{
    struct Object{
        int track_idx_;
        double box_x_;
        double box_y_;
        double box_h_;
        double box_w_;
        std::string class_name;
    };

    struct Pose{
        int track_idx_;
        double box_x_;
        double box_y_;
        double box_h_;
        double box_w_;
        double box_z_;
        std::string class_name_;
        std::vector<std::string> all_classes;
    };


    class Detector{
        public:
        void initModel();
        std::vector<acme::Object> detect(cv::Mat frame);
        void preProcess(const cv::Mat &frame);
        std::vector<acme::Object> postProcess(cv::Size &s);
        Detector();
        Detector(double imageW, double imageH, std::vector<std::string> targetClasses, float conf);
        ~Detector();
        private:
        std::vector<cv::Mat> outputs_;
        std::vector<std::string> allClasses_;
        std::vector<std::string> targetClasses_;
        cv::dnn::Net net_;
        double imgH_;
        double imgW_;
        float confThresh_;
        float nmsThresh_;
    };
 }

 #endif