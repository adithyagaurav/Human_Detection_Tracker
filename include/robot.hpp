/******************************************************************************
 * MIT License
 * 
 * Copyright (c) 2021 Adithya Singh, Rishabh Singh, Divyansh Agarwal
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 ******************************************************************************/

/**
/**
 * @file robot.hpp
 * @author Rishabh Singh 
 * @author  Adithya Singh
 * @brief Class declaration for Robot
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
#include <string>
#include "../include/tracker.hpp"
#include "../include/utils.hpp"
#include "../include/detector.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

/**
 * @brief Namespace acme to specify project attributes
 * 
 */
namespace acme {
/**
    * @brief Main Driver class of the god to run human detection
    in image and stream mode, and perform pose estimation
    * 
    */
class Robot {
 public:
        /**
            * @brief Entry Function for code to select 
            * image mode or stream mode
            * 
            * @param mode 
            */
        void run(int mode);
        /**
            * @brief Function to perform Human detection on a single image
            * 
            * @param image_path 
            */
        void processImage(std::string image_path);
        /**
            * @brief Function to perform Human detection on stream
            * 
            */
        void processStream();
        /**
            * @brief Construct a new Robot object
            * 
            * @param focalLength 
            */
        explicit Robot(double focalLength);
        ~Robot();

 private:
        // Detector class object to access its methods
        acme::Detector detector_;

        // Vector container to store transformed poses
        std::vector<acme::Pose> poses;

        // Depth coefficent to compute depth
        float depth_coeff_;

        // Focal length to compute depth
        float focal_length_;

        // Vector container to store objects
        std::vector<acme::Object> objects;

        // Tracker class object to access its methods
        acme::Tracker tracker_;
};
}  // namespace acme

#endif  // INCLUDE_ROBOT_HPP_
