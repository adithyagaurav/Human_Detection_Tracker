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
#include <string>

std::vector<acme::Pose> acme::Utils::getFinalBoxes(
                  std::vector<acme::Object> &bboxes, float depth_coeff) {
    // Container for holding output
    std::vector<Pose> output;
    // Iterate over each bounding box
    for (auto it : bboxes) {
        // Compute depth using lens formula
        float actual_h = 72;
        float depth = depth_coeff * it.box_h_/actual_h;
        // Initialize Pose object with depth information
        acme::Pose pose{it.track_idx_, it.box_x_, it.box_y_, it.box_h_, it.box_w_, depth, it.class_name};
        output.push_back(pose);
    }
    return output;
}

void acme::Utils::draw(cv::Mat frame, std::vector<acme::Pose> &obj_bboxes,
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
        if (display){
            cv::Point label_tl = cv::Point(tl.x, abs(tl.y - 10));
            std::string label_text = std::to_string(obj_bboxes[i].track_idx_) + 
                " (" + std::to_string(tl.x - outsize.width/2) +
                ", " + std::to_string(tl.y - outsize.height/2) +
                ", " + std::to_string((obj_bboxes[i].box_z_)) + ")";
            cv::putText(out_frame, label_text, label_tl, cv::FONT_HERSHEY_SIMPLEX, 0.3, color, 2);
        }
    }
    if (display==true){
        cv::imshow("Output", out_frame);
        cv::waitKey(1);
    } else {
    // Save image
        cv::imwrite("../data/out.jpg", out_frame);
    }
}

double acme::Utils::calculateIoU(acme::Object &obj1, acme::Object &obj2) {
    // Get minimum and maximum value fir bounding box 1
    double minx_obj1 = obj1.box_x_;
    double maxx_obj1 = obj1.box_x_ + obj1.box_w_;
    double miny_obj1 = obj1.box_y_;
    double maxy_obj1 = obj1.box_y_+ obj1.box_h_;

    // Get minimum and maximum values of bounding box 2
    double minx_obj2 = obj2.box_x_;
    double maxx_obj2 = obj2.box_x_ + obj2.box_w_;
    double miny_obj2 = obj2.box_y_;
    double maxy_obj2 = obj2.box_y_+ obj2.box_h_;

    // Calculate intersecting x and y point
    double intersection_x = std::min(maxx_obj2, maxx_obj1) - std::max(minx_obj2, minx_obj1);
    double intersection_y = std::min(maxy_obj2, maxy_obj1) - std::max(miny_obj2, miny_obj1);

    // Calculate area of bboxes
    double area1 = (maxx_obj1 - minx_obj1)*(maxy_obj1 - miny_obj1);
    double area2 = (maxx_obj2 - minx_obj2)*(maxy_obj2 - miny_obj2);

    // Calculate intersection
    double intersectionScore = intersection_x * intersection_y;
    // Calculate union
    double unionScore = area1 + area2 - intersectionScore;
    // Calculate Intersection over Union
    if ( unionScore != 0 ) {
        return intersectionScore / unionScore;
    } else { 
        return 0.0; 
    }

}
