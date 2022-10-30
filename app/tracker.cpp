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
* @file tracker.cpp
* @author Rishabh Singh 
* @author  Adithya Singh
* @author Divyansh Agarwal
* @brief Class implementation for Tracker class
* @version 0.1
* @date 2022-10-20
* 
* @copyright Copyright (c) 2022
* 
*/

#include "../include/tracker.hpp"

std::vector<acme::Object> acme::Tracker::updateTracker(
                                std::vector<acme::Object> bboxes, int frame_id) {
    // Create container to hold objects
    std::vector<acme::Object> new_objs;
    acme::Utils utils_obj;
    double max_score;
    double score;
    std::cout<<frame_id<<std::endl;
    // For first frame
    if (frame_id == 0) {
        int count = 0;
        // Iterate over each bounding box
        for (auto& it : bboxes) {
            if (it.class_name == "person") {
                count = count + 1;
                // Assign ID
                it.track_idx_ = count;
                // Store object with updated track ID
                new_objs.push_back(it);
                std::cout<<count<<std::endl;
            }
        }
        // Update track for all bboxes
        tracks_ = new_objs;
    }
    else {
        // For each frame after first frame
        std::cout<<"FINDING TRACKS"<<std::endl;
        // Iterate over each bounding box
        for (auto new_box : bboxes){
            max_score = INT_MIN;
            // Check valid class
            if (new_box.class_name!="person"){
                std::cout<<"INVALID CLASS"<<std::endl;
                continue;
            }
            // Compute IoU with each track in previous frame
            for (auto old_box:tracks_){
                score = utils_obj.calculateIoU(new_box, old_box);
                // Assign ID of object with highest IoU score to current frame bbox
                if (score>max_score) {
                    max_score = score;
                    new_box.track_idx_ = old_box.track_idx_;
                }
                if (max_score == INT_MIN){
                    new_box.track_idx_ = rand()%10 + 20;
                }
            }
            // Store new bounding box
            new_objs.push_back(new_box);

        }
        // Update tracks for current frame
        tracks_ = new_objs;
    }
    return tracks_;
}

acme::Tracker::Tracker() {
}

acme::Tracker::~Tracker() {
}
