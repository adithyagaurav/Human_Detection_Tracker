/**
 * @file tracker.hpp
 * @author 
 * Navigator : Rishabh Singh ( )
 * Driver : Adithya Singh (agsingh@umd.edu)
 * @brief 
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
 #include "detector.hpp"

namespace acme{
 class Tracker{
    public:
    std::vector<acme::Object> updateTracker(std::vector<acme::Object> bboxes);
    Tracker();
    ~Tracker();
    private:
    std::vector<acme::Object> tracks_;
 };
}

#endif