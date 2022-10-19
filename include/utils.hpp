/**
 * @file utils.hpp
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
 #ifndef INCLUDE_UTILS_HPP_
 #define INCLUDE_UTILS_HPP_
 #include <iostream>
 #include <vector>
 #include "detector.hpp"

 namespace acme{
    class Utils{
        public:
        std::vector<acme::Pose> getFinalBoxes(std::vector<acme::Object> bboxes, float depth_coeff);
        void draw(cv::Mat frame, std::vector<acme::Pose> pose_bboxes);
        double calculateIoU(acme::Pose pose1, acme::Pose pose2);
    };
 }

#endif