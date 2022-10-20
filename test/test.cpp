#include <gtest/gtest.h>

#include "../include/robot.hpp"
#include "../include/tracker.hpp"
 #include "../include/utils.hpp"
 #include "../include/detector.hpp"
 #include <opencv2/opencv.hpp>
 #include <opencv2/core/core.hpp>
 #include <opencv2/imgcodecs.hpp>

int focal_length = 1;
acme::Robot robot(focal_length);
double img_h = 416;
double img_w = 416;
float conf = 0.2;
std::vector<std::string> classes_ = {"person"};
acme::Detector detector(img_h, img_w, classes_, conf);
acme::Tracker tracker;
acme::Utils utils_object;
TEST(run, test_case1){
  
  
  int mode = 1;
  ASSERT_NO_THROW(robot.run(mode));
  mode = 2;
  ASSERT_NO_THROW(robot.run(mode));
  mode = 2;
  ASSERT_NO_THROW(robot.run(mode));
}

TEST(processImage, test_case_2){
  std::string img_path = "../data/image3.jpg";
  ASSERT_NO_THROW(robot.processImage(img_path));

}

TEST(processStream, test_case_3){
  ASSERT_NO_THROW(robot.processStream());
}

TEST(detect, test_case_4){
  cv::Mat img = cv::imread("../data/image3.jpg");
  std::vector<acme::Object> output = detector.detect(img);
  ASSERT_EQ(static_cast<int>(output.size()), 3);
}

TEST(preProcess, test_case_5){
  cv::Mat img = cv::imread("../data/image3.jpg");
  
  ASSERT_NO_THROW(detector.preProcess(img));
}

TEST(postProcess, test_case_6){
  cv::Size s = cv::Size(416, 416);
  ASSERT_EQ(static_cast<int>(detector.postProcess(s).size()), 3);
}

TEST(updateTracker, test_case_7){
  cv::Mat img = cv::imread("../data/image3.jpg");
  std::vector<acme::Object> output = detector.detect(img);
  ASSERT_EQ(static_cast<int>(tracker.updateTracker(output).size()), output.size());
}

TEST(draw, test_case_8){
  cv::Mat img = cv::imread("../data/image3.jpg");
  cv::Mat resizeImg;
  cv::resize(img, resizeImg, cv::Size(416, 416));
  std::vector<acme::Object> output = detector.detect(img);
  cv::Size insize = cv::Size(416, 416);
  cv::Size outsize = img.size();
  ASSERT_NO_THROW(utils_object.draw(img, output, insize, outsize));
}

TEST(getFinalBoxes, test_case_9){
  cv::Mat img = cv::imread("../data/image3.jpg");
  std::vector<acme::Object> output = detector.detect(img);
  float depth_coeff = 0.7;
  ASSERT_EQ(static_cast<int>(utils_object.getFinalBoxes(output, depth_coeff).size()), output.size());
}

TEST(calculateIoU, test_case_10){
  acme::Pose pose1;
  acme::Pose pose2;
  ASSERT_EQ(utils_object.calculateIoU(pose1, pose2), 0.8);
}