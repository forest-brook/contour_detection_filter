#pragma once

// Uses the strings.
#include <string>

// Uses the opencv library.
#include "opencv2/core/core.hpp"


// Image stream data.
class image_stream_data
{
public:

    image_stream_data();

    std::string input_image_path;                               // Input image path.
    std::string filtered_image_path;                            // Filtered image path.
    std::string contours_image_path;                            // Contours image path.

    cv::Mat input_image;                                        // Input image.
    cv::Mat contours_image;                                     // Contours image.

    int error_code;                                             // Error code.
    std::string error_message;                                  // Error message.
};
