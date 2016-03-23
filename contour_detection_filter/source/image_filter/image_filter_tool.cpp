#include "image_filter_tool.h"

// Uses the opencv library.
#include "opencv2/imgproc/imgproc.hpp"

// Uses the image filter data.
#include "image_filter_data.h"


// Applies the median filter on the specified image.
bool image_filter_tool::apply_median_filter
(
    image_filter_data & data,
    cv::Mat & image
)
{
    bool result = true;

    // Initialize the state.

    if (result)
    {
        data.error_code = 0;
        data.error_message.clear();
    }

    // Apply the median filter on the input image.

    if (result)
    {
        cv::medianBlur
        (
            image,
            data.filtered_image,
            data.median_filter_size
        );
        result = !data.filtered_image.empty();
    }

    // Process the errors.

    if (!result)
    {
        data.error_code = 1;
        data.error_message = "Failed to apply the median filter on the image.";
    }

    return result;
}

// Detects the contours on the specified image.
bool image_filter_tool::detect_contours
(
    image_filter_data & data
)
{
    bool result = true;

    // Initialize the state.

    if (result)
    {
        data.contours.clear();
        data.error_code = 0;
        data.error_message.clear();
    }

    // Get the greyscale image.

    if (result)
    {
        cv::cvtColor
        (
            data.filtered_image,
            data.greyscale_image,
            CV_BGR2GRAY
        );

        result = !data.greyscale_image.empty();
    }

    // Get the edges.

    if (result)
    {
        cv::Canny
        (
            data.greyscale_image,
            data.edges_image,
            data.edge_linking_threshold,
            data.strong_edge_threshold
        );

        result = !data.edges_image.empty();
    }

    // Detect the contours.

    if (result)
    {
        cv::findContours
        (
            data.edges_image,
            data.contours,
            CV_RETR_LIST,
            CV_CHAIN_APPROX_SIMPLE
        );
    }

    // Process the errors.

    if (!result)
    {
        data.error_code = 1;
        data.error_message = "Failed to detect the contours.";
    }

    return result;
}

// Clears the filter data.
bool image_filter_tool::clear
(
    image_filter_data & data
)
{
    bool result = true;

    // Initialize the state.

    if (result)
    {
        data.error_code = 0;
        data.error_message.clear();
    }

    // Deallocate the filtered image buffer.

    if (result)
        data.filtered_image = cv::Mat();

    // Deallocate the contour detection image buffers.

    if (result)
    {
        data.greyscale_image = cv::Mat();
        data.edges_image = cv::Mat();
    }

    // Deallocate the contours buffer.

    if (result)
    {
        std::vector< std::vector< cv::Point > > t;
        data.contours.swap(t);
    }

    return result;
}


