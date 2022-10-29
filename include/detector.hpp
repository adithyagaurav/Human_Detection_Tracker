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
 * @file detector.hpp
 * @author Divyansh Agarwal
 * @author Rishabh Singh ( )
 * @author Adithya Singh (agsingh@umd.edu)
 * @brief Include to declare Detector class
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
#include<string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>


namespace acme {
/**
    * @brief Structure for human detection
    * 
    */
struct Object {
    int track_idx_;
    double box_x_;
    double box_y_;
    double box_h_;
    double box_w_;
    std::string class_name;
};

/**
 * @brief Structure to store pose of each object
 * 
 */
struct Pose {
    int track_idx_;
    double box_x_;
    double box_y_;
    double box_h_;
    double box_w_;
    double box_z_;
    std::string class_name_;
};

/**
 * @brief Class to handle detection operations
 * 
 */
class Detector {
 public:
    /**
     * @brief Function to load model, set parameters and test dummy image
     * 
     */
    void initModel();
    /**
     * @brief Function to detect object in image
     * 
     * @param frame 
     * @return std::vector<acme::Object> 
     */
    std::vector<acme::Object> detect(cv::Mat frame);
    /**
     * @brief Function to run pre processing operations
     * 
     * @param frame 
     */
    void preProcess(const cv::Mat &frame);
    /**
     * @brief Function to refine model detections
     * 
     * @param s 
     * @return std::vector<acme::Object> 
     */
    std::vector<acme::Object> postProcess(const cv::Size &s);
    /**
     * @brief Construct a new Detector object
     * 
     */
    Detector();
    /**
     * @brief Construct a new Detector object
     * 
     * @param imageW 
     * @param imageH 
     * @param targetClasses 
     * @param conf 
     */
    Detector(double imageW, double imageH,
            const std::vector<std::string> &targetClasses, float conf);
    ~Detector();

 private:
    // Vector container to store outputs from preprocessing function
    std::vector<cv::Mat> outputs_;

    // Vector container to store class names
    std::vector<std::string> allClasses_;

    // Vector container to store required class names
    std::vector<std::string> targetClasses_;

    // Create neural network object
    cv::dnn::Net net_;

    // Specify image dimensions and detection thresholds
    double imgH_;
    double imgW_;
    float confThresh_;
    float nmsThresh_;
};
}  // namespace acme

#endif  // INCLUDE_DETECTOR_HPP_
