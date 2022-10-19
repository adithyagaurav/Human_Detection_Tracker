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

 namespace acme{
    struct Object{
        int track_idx_;
        double box_x_;
        double box_y_;
        double box_h_;
        double box_w_;
        int class_idx;
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
        Detector(double image_w, double image_h, int target_id, float conf);
        ~Detector();
        private:
        int target_class_idx;
        double image_h;
        double image_w;
        float conf_thresh;
    };
 }

 #endif