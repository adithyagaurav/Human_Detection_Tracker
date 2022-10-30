/******************************************************************************
 * MIT License
 * 
 * Copyright (c) 2021 Adithya Singh, Rishabh Singh, Disvyansh Agarwal
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
* @file detector.cpp
* @author Rishabh Singh 
* @author  Adithya Singh
* @brief Class implementation for Detector
* @version 0.1
* @date 2022-10-20
* 
* @copyright Copyright (c) 2022
* 
*/

#include "../include/detector.hpp"
#include <vector>

acme::Detector::Detector(double imgW, double imgH,
                        const std::vector<std::string> &targets, float conf)\
                        :imgH_(imgH), imgW_(imgW), targetClasses_(targets)\
                        , confThresh_(conf) {
    // Set the required attributes;
    nmsThresh_ = 0.2;
    // Load model and run dummy test
    acme::Detector::initModel();
}

acme::Detector::Detector() {
}

acme::Detector::~Detector() {
}

void acme::Detector::initModel() {
    std::cout << "Loaded Model" << std::endl;
    // Load model from weights and set backends and target
    net_ = cv::dnn::readNet("../model/yolov4-tiny.cfg",
                            "../model/yolov4-tiny.weights");
    net_.setPreferableBackend(0);
    net_.setPreferableTarget(0);

    // Specify all available classes
    allClasses_ = {"person", "bicycle", "car", "motorbike", "aeroplane",
    "bus", "train", "truck", "boat", "traffic light", "fire hydrant",
    "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse",
    "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack",
    "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard",
    "sports ball", "kite", "baseball bat", "baseball glove", "skateboard",
    "surfboard", "tennis racket", "bottle", "wine glass", "cup", "fork",
    "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange",
    "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair",
    "sofa", "pottedplant", "bed", "diningtable", "toilet", "tvmonitor",
    "laptop", "mouse", "remote", "keyboard", "cell phone", "microwave",
    "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase",
    "scissors", "teddy bear", "hair drier", "toothbrush"};

    // Set up dummy input and run
    cv::Mat temp = cv::Mat::zeros(cv::Size(416, 416), CV_8UC3);
    acme::Detector::preProcess(temp);
}

void acme::Detector::preProcess(const cv::Mat &frame) {
    // Set up blob
    cv::Mat blob;
    // Process if image is valid
    if ( !frame.empty() ) {
        // create blob
        blob = cv::dnn::blobFromImage(frame, 1/255.0,
                                    cv::Size(imgW_, imgH_),
                                    cv::Scalar(), true, false);
        // Create input and perform forward pass
        net_.setInput(blob);
        outputs_.clear();
        net_.forward(outputs_, net_.getUnconnectedOutLayersNames());
    } else {
        std::cout << "Image invalid";
    }
}

std::vector<acme::Object> acme::Detector::postProcess(const cv::Size &s) {
    // Vector container to store detections and attributes
    std::vector<acme::Object> detections;
    std::vector<std::string> class_names;
    std::vector<float> confidences;
    // Opencv object for bounding box
    std::vector<cv::Rect> bboxes;
    std::vector<int> indices;
    // For each bounding box
    for (cv::Mat &out : outputs_) {
        // Extract bbox data
        auto *data = reinterpret_cast<float*>(out.data);
        for (int i=0; i < out.rows; i++, data += out.cols) {
            // Unnormalize coordinates
            int xCenter = static_cast<int>(data[0]*s.width);
            int yCenter = static_cast<int>(data[1]*s.height);
            cv::Mat scores = out.row(i).colRange(5, out.cols);
            cv::Point classIdPoint;
            double confidence;
            // Find min and max confidence
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            // Only store high confidence detections
            if (confidence > confThresh_) {
                int classId = classIdPoint.x;
                std::string className = allClasses_[classId];
                auto iter = std::find(targetClasses_.begin(),
                                    targetClasses_.end(), className);
                // Only store "person" detections
                if ( iter != targetClasses_.end() ) {
                    xCenter = std::max(0, xCenter);
                    yCenter =  std::max(0, yCenter);

                    /// get detected bbox width
                    int width = static_cast<int>(data[2]*s.width);

                    /// get detected bbox height
                    int height = static_cast<int>(data[3]*s.height);

                    /// calculate x - top left coordinate
                    int xLeft = xCenter - width / 2;

                    /// calculate y - top left coordinate
                    int yTop = yCenter - height / 2;

                    /// create a cv::Rect object
                    cv::Rect bbox(xLeft, yTop, width, height);

                    /// store the class names in a vector
                    class_names.push_back(className);

                    /// store the confidences in a vector
                    confidences.push_back(static_cast<float>(confidence));

                    /// store the bbox in a vector
                    bboxes.push_back(bbox);
                }
            }
        }
    }
    // Run NMS to eliminate unnecessary detections
    cv::dnn::NMSBoxes(bboxes, confidences, confThresh_, nmsThresh_, indices);
    std::cout << indices.size();
    // For each bbox
    for ( int index : indices ) {
        // Store bbox information as object structure
        cv::Rect bbox = bboxes[index];
        // double conf = static_cast<double>(confidences[index]);
        std::string name = class_names[index];
        std::cout << "Class found: " << name << std::endl;

        /// create Detection object
        acme::Object box{0, bbox.x, bbox.y, bbox.height, bbox.width, name};

        /// store the Detection objects in a vector
        detections.push_back(box);
    }
    return detections;
}

std::vector<acme::Object> acme::Detector::detect(cv::Mat frame) {
    // Vector container for outputs and detections
    std::vector<acme::Object> output;
    // Run pre-processing step
    acme::Detector::preProcess(frame);
    cv::Size size = frame.size();
    // Run post-processing step
    output = acme::Detector::postProcess(size);
    return output;
}
