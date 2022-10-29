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
* @file tracker.hpp
* @author Rishabh Singh 
* @author  Adithya Singh
* @author Divyansh Agarwal
* @brief Class declaration for tracker class
* @version 0.1
* @date 2022-10-16
* 
* @copyright Copyright (c) 2022
* 
*/
#ifndef INCLUDE_TRACKER_HPP_
#define INCLUDE_TRACKER_HPP_
#include <iostream>
#include <vector>
#include <limits.h>
#include "../include/detector.hpp"
#include "../include/utils.hpp"

namespace acme {
/**
 * @brief Tracker class declaration
 * 
 */
class Tracker {
 public:
    /**
        * @brief Function to update tracks of objects
        * 
        * @param bboxes 
        * @return std::vector<acme::Object> 
        */
    std::vector<acme::Object> updateTracker(std::vector<acme::Object> bboxes, int frame_id);
    /**
        * @brief Construct a new Tracker object
        * 
        */
    Tracker();
    /**
        * @brief Destroy the Tracker object
        * 
        */
    ~Tracker();
 private:
    // Vector container to store tracks
    std::vector<acme::Object> tracks_;
};
}  // namespace acme

#endif  // INCLUDE_TRACKER_HPP_
