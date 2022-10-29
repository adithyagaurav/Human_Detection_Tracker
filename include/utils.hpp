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
* @file utils.hpp
* @author Rishabh Singh 
* @author  Adithya Singh
* @author Divyansh Agarwal
* @brief Class declaration for Utils
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
#include "../include/detector.hpp"
#include "../include/tracker.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

namespace acme {
/**
 * @brief Class for helper functions
 * 
 */
class Utils {
 public:
    /**
     * @brief Get the Final Boxes object
     * 
     * @param bboxes 
     * @param depth_coeff 
     * @return std::vector<acme::Pose> 
     */
    std::vector<acme::Pose> getFinalBoxes(std::vector<acme::Object>
                                        &bboxes, float depth_coeff);
    /**
     * @brief Draw object bounding boxes on Image
     * 
     * @param frame 
     * @param pose_bboxes 
     * @param insize 
     * @param outsize 
     */
    void draw(cv::Mat frame, std::vector<acme::Pose> &pose_bboxes,
            cv::Size insize, cv::Size outsize, bool display);
    /**
     * @brief Calculate IoU
     * 
     * @param pose1 
     * @param pose2 
     * @return double 
     */
    double calculateIoU(acme::Object &pose1, acme::Object &pose2);
};
}  // namespace acme

#endif  // INCLUDE_UTILS_HPP_
