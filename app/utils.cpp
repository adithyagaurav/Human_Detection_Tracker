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
* @file utils.cpp
* @author Rishabh Singh 
* @author  Adithya Singh
* @author Divyansh Agarwal
* @brief Class implementation for Utils
* @version 0.1
* @date 2022-10-20
* 
* @copyright Copyright (c) 2022
* 
*/

#include "../include/utils.hpp"

std::vector<acme::Pose> acme::Utils::getFinalBoxes(
                  std::vector<acme::Object> &bboxes, float depth_coeff) {
    // Stub implementation
    std::vector<acme::Pose> output;
    acme::Pose pose1{1, 12.0, 10.0, 30.0, 20.0, 5.0, "person"};
    acme::Pose pose2{2, 32.0, 27.0, 25.0, 15.0, 6.0, "person"};
    acme::Pose pose3{2, 32.0, 27.0, 25.0, 15.0, 6.0, "person"};
    output.push_back(pose1);
    output.push_back(pose2);
    output.push_back(pose3);
    return output;
}

void acme::Utils::draw(cv::Mat frame, std::vector<acme::Object> &obj_bboxes,
               cv::Size insize, cv::Size outsize, bool display) {
    // Create copy of frame
    cv::Mat out_frame = frame.clone();
    // Set bbox and label color
    cv::Scalar color = cv::Scalar(0, 255, 0);
    // Store top left and bottom right points
    cv::Point tl;
    cv::Point br;
    // For each bbox
    for (int i = 0; i < obj_bboxes.size(); i++) {
        // Resize top left point
        tl = cv::Point((obj_bboxes[i].box_x_ / insize.width)*outsize.width,
                        (obj_bboxes[i].box_y_ / insize.height)*outsize.height);
        // Resize top right point
        br = cv::Point(
        (obj_bboxes[i].box_x_ +
        obj_bboxes[i].box_w_)*outsize.width / insize.width,
        (obj_bboxes[i].box_y_ +
        obj_bboxes[i].box_h_)*outsize.height / insize.height);
        // Draw rectangle
        cv::rectangle(out_frame, tl, br, color, 1);

        cv::Point label_tl = cv::Point(tl.x, abs(tl.y - 10));
        std::string label_text = std::to_string(obj_bboxes[i].track_idx_);
        cv::putText(out_frame, label_text, label_tl, cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);
    }
    if (display==true){
        cv::imshow("Output", out_frame);
        cv::waitKey(1);
    } else {
    // Save image
        cv::imwrite("../data/out.jpg", out_frame);
    }
}

double acme::Utils::calculateIoU(acme::Pose &pose1, acme::Pose &pose2) {
    // Stub implementation
    std::cout << " IoU is : 0.8" << std::endl;
    return 0.8;
}
