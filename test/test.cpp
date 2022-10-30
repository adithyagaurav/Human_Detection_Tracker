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
 * @file test.cpp
 * @author Adithya Singh, Rishabh Singh, Divyansh Agarwal
 * @brief Unit test case implementation
 * @version 0.1
 * @date 2022-10-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <gtest/gtest.h>

#include "../include/robot.hpp"
#include "../include/tracker.hpp"
#include "../include/utils.hpp"
#include "../include/detector.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

// Declare objects and constants
int focal_length = 1;
acme::Robot robot(focal_length);
double img_h = 416;
double img_w = 416;
float conf = 0.2;
std::vector<std::string> classes_ = {"person"};
acme::Detector detector(img_h, img_w, classes_, conf);
acme::Tracker tracker;
acme::Utils utils_object;

// Run test for acme::Robot::run
TEST(run, test_case1) {
  int mode = 1;
  ASSERT_NO_THROW(robot.run(mode));
  mode = 2;
  ASSERT_NO_THROW(robot.run(mode));
  mode = 2;
  ASSERT_NO_THROW(robot.run(mode));
}

// Run test for acme::Robot::processImage
TEST(processImage, test_case_2) {
  std::string img_path = "../data/image3.jpg";
  ASSERT_NO_THROW(robot.processImage(img_path));
}

// Run test for acme::Robot::processStream
TEST(processStream, test_case_3) {
  ASSERT_NO_THROW(robot.processStream());
}

// Run test for acme::Detector::detect
TEST(detect, test_case_4) {
  cv::Mat img = cv::imread("../data/image3.jpg");
  std::vector<acme::Object> output = detector.detect(img);
  ASSERT_EQ(static_cast<int>(output.size()), 3);
}

// Run test for acme::Detector::preProcess
TEST(preProcess, test_case_5) {
  cv::Mat img = cv::imread("../data/image3.jpg");
  ASSERT_NO_THROW(detector.preProcess(img));
}

// Run test for acme::Detector::postProcess
TEST(postProcess, test_case_6) {
  cv::Size s = cv::Size(416, 416);
  ASSERT_EQ(static_cast<int>(detector.postProcess(s).size()), 3);
}

// Run test for acme::Tracker::updateTracker
TEST(updateTracker, test_case_7) {
  cv::Mat img = cv::imread("../data/image3.jpg");
  std::vector<acme::Object> output = detector.detect(img);
  ASSERT_EQ(
    static_cast<int>(tracker.updateTracker(output, 0).size()), output.size());
}

// Run test for acme::Utils::draw
TEST(draw, test_case_8) {
  cv::Mat img = cv::imread("../data/image3.jpg");
  cv::Mat resizeImg;
  cv::resize(img, resizeImg, cv::Size(416, 416));
  float depth_coeff = 0.7;
  std::vector<acme::Object> output = detector.detect(img);
  std::vector<acme::Pose> final_output = utils_object.getFinalBoxes(output, depth_coeff);
  cv::Size insize = cv::Size(416, 416);
  cv::Size outsize = img.size();
  ASSERT_NO_THROW(utils_object.draw(img, final_output, insize, outsize, false));
}

// Run test for acme::Utils::getFinalBoxes
TEST(getFinalBoxes, test_case_9) {
  cv::Mat img = cv::imread("../data/image3.jpg");
  std::vector<acme::Object> output = detector.detect(img);
  float depth_coeff = 0.7;
  ASSERT_EQ(
    static_cast<int>(
      utils_object.getFinalBoxes(output, depth_coeff).size()), output.size());
}

// Run test for acme::Utils::calculateIoU
TEST(calculateIoU, test_case_10) {
  acme::Object groundTruth{0, 121.0, 80.0, 511.0, 191.0, "person"};

  cv::Mat img = cv::imread("../data/IoUtest.jpg");
  cv::Mat resizeImg;
  cv::resize(img, resizeImg, cv::Size(416, 416));
  float depth_coeff = 0.7;
  std::vector<acme::Object> output = detector.detect(img);
  ASSERT_NEAR(0.8, utils_object.calculateIoU(groundTruth, output[0]), 0.2);
}
