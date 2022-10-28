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
                                std::vector<acme::Object> bboxes) {

    int count = 0;
    for (auto& it : bboxes) {
        if (it.class_name == "person") {
            count = count + 1;
            it.track_idx_ = count;
        }
    }
    
    std::cout << "Track IDs assigned" << std::endl;
    return bboxes;
}

acme::Tracker::Tracker() {
}

acme::Tracker::~Tracker() {
}
