/**
 * @file tracker.cpp
 * @author 
 * Navigator : Rishabh Singh ( )
 * Driver : Adithya Singh (agsingh@umd.edu)
 * UML Design Keeper : Divyansh Agarwal ( )
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 #include "../include/tracker.hpp"

 std::vector<acme::Object> acme::Tracker::updateTracker(std::vector<acme::Object> bboxes){
    acme::Object object1{1, 12.0, 10.0, 30.0, 20.0, 1};
    acme::Object object2{2, 32.0, 27.0, 25.0, 15.0, 1};
    tracks_.push_back(object1);
    tracks_.push_back(object2);
    return tracks_;
 }