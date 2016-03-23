#pragma once


namespace cv
{
class Mat;                                                      // Uses the image matrices.
}
class image_filter_data;                                        // Uses the image filter data.

// Image filter tool.
class image_filter_tool
{
public:

    bool apply_median_filter                                    // Applies the median filter on the specified image.
    (
        image_filter_data & data,
        cv::Mat & image
    );
    bool detect_contours                                        // Detects the contours on the specified image.
    (
        image_filter_data & data
    );
    bool clear                                                  // Clears the filter data.
    (
        image_filter_data & data
    );
};
