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
 * @file robot.cpp
 * @author Rishabh Singh 
 * @author  Adithya Singh
 * @author Divyansh Agarwal
 * @brief Class implementation for Robot
 * @version 0.1
 * @date 2022-10-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/robot.hpp"
#include <string>


acme::Robot::Robot(double focal_length) {
  // Set the constants
  double image_w_ = 416;
  double image_h_ = 416;
  float conf = 0.4;
  depth_coeff_ = 10;
  std::vector<std::string> targetClasses{"person"};

  // Create Detector class object
  acme::Detector detector(image_w_, image_h_, targetClasses, conf);
  detector_ = detector;

  // Set focal length
  float focal_length_ = focal_length;

  // Create tracker class object
  acme::Tracker tracker_;
}

acme::Robot::~Robot() {
}

void acme::Robot::run(int mode) {
    std::cout << "Run mode " << mode << std::endl;

    // Run image mode if mode is 1 and stream mode if mode is 2
    if (mode == 1) {
        std::string imagePath = "../data/image3.jpg";
        processImage(imagePath);
    } else if (mode == 2) {
        processStream();
    } else {
        std::cout << "Invalid mode" << std::endl;
    }
}

void acme::Robot::processImage(std::string imagePath) {
    // Read input image
    cv::Mat img = cv::imread(imagePath);

    // Resize input image
    cv::Mat resizeImg;
    cv::Size insize = cv::Size(416, 416);
    cv::Size outsize = img.size();
    cv::resize(img, resizeImg, insize);
    std::cout << "Image Mode running " << std::endl;

    // Prcocess image through detector
    std::vector<acme::Object> output = detector_.detect(resizeImg);

    // Create Utils class object
    acme::Utils utils_;
    std::vector<acme::Pose> final_output = utils_.getFinalBoxes(output, depth_coeff_);
    // Draw output on image
    utils_.draw(img, final_output, insize, outsize, false);

    // Display detection information
    std::cout << "Total objects found : " << output.size() << std::endl;
    std::cout << "Image size : " << img.size().width << " x "
    << img.size().height << std::endl;
}

void acme::Robot::processStream() {
    
    // std::string filename = "../data/test_video.mp4";
    std::string filename = "/home/ubuntu/PMRO/ENPM808X/midterm/Human_Detection_Tracker/data/test_video.mp4";

    cv::VideoCapture cap;
    cap.open(filename, cv::CAP_FFMPEG);
    cv::Mat frame;
    cap>>frame;
    std::vector<acme::Object> output;
    std::vector<acme::Pose> final_output;
    cv::Mat resizeFrame;
    cv::Size insize = cv::Size(416, 416);
    cv::Size outsize = frame.size();
    acme::Utils utils_;
    int counter=0;
    while(frame.size().width!=0)
    {
        cap >> frame;
        cv::resize(frame, resizeFrame, insize);
        output = detector_.detect(resizeFrame);
        output = tracker_.updateTracker(output, counter);
        final_output = utils_.getFinalBoxes(output, depth_coeff_);
        utils_.draw(frame, final_output, insize, outsize, true);
        counter++;
        std::cout<<"Frame processed : "<<counter<<std::endl;

    }
    if (!cap.isOpened()){
        std::cerr<<"UNABLE TO OPEN CAMERA"<<std::endl;
    }

}
