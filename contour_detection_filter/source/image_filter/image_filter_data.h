#pragma once

// Uses the strings.
#include <string>

// Uses the vector.
#include <vector>

// Uses the opencv library.
#include "opencv2/core/core.hpp"


// Image filter data.
class image_filter_data
{
public:

    image_filter_data();

    int median_filter_size;                                     // Median filter aperture linear size.
    cv::Mat filtered_image;                                     // Filtered image.

    double edge_linking_threshold;                              // Edge linking threshold.
    double strong_edge_threshold;                               // Strong edge threshold.
    cv::Mat greyscale_image;                                    // Greyscale image.
    cv::Mat edges_image;                                        // Edges image.
    std::vector< std::vector< cv::Point > > contours;           // Contours.

    int error_code;                                             // Error code.
    std::string error_message;                                  // Error message.
};
