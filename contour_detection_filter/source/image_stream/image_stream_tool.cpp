#include "image_stream_tool.h"

// Uses the opencv library.
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// Uses the image filter data.
#include "image_filter/image_filter_data.h"

// Uses the image stream data.
#include "image_stream_data.h"


// Loads the input image.
bool image_stream_tool::load_input_image
(
    image_stream_data & data
)
{
    bool result = true;

    // Initialize the state.

    if (result)
    {
        data.error_code = 0;
        data.error_message.clear();
    }

    // Load the specified image.

    if (result)
    {
        data.input_image = cv::imread(data.input_image_path.c_str());
        result = !data.input_image.empty();
    }

    // Process the errors.

    if (!result)
    {
        data.error_code = 1;
        data.error_message = "Failed to load the image \"";
        data.error_message += data.input_image_path;
        data.error_message += "\".";
    }

    return result;
}

// Saves the filtered image.
bool image_stream_tool::save_filtered_image
(
    image_stream_data & data,
    image_filter_data & filter_data
)
{
    bool result = true;

    // Initialize the state.

    if (result)
    {
        data.error_code = 0;
        data.error_message.clear();
    }

    // Save the filtered image.

    if (result)
    {
        result =
            cv::imwrite
            (
                data.filtered_image_path.c_str(),
                filter_data.filtered_image
            );
    }

    // Process the errors.

    if (!result)
    {
        data.error_code = 1;
        data.error_message = "Failed to save the filtered image \"";
        data.error_message += data.filtered_image_path;
        data.error_message += "\".";
    }

    return result;
}

// Saves the filtered image.
bool image_stream_tool::save_contours_image
(
    image_stream_data & data,
    image_filter_data & filter_data
)
{
    bool result = true;

    // Initialize the state.

    if (result)
    {
        data.error_code = 0;
        data.error_message.clear();
    }

    // Copy the input image.

    if (result)
    {
        data.input_image.copyTo(data.contours_image);
        result = !data.contours_image.empty();
    }

    // Draw the detected contours.

    if (result)
    {
        cv::drawContours
        (
            data.contours_image,
            filter_data.contours,
            -1,
            cv::Scalar(0, 0, 255),
            2
        );
    }

    // Save the contours image.

    if (result)
    {
        result =
            cv::imwrite
            (
                data.contours_image_path.c_str(),
                data.contours_image
            );
    }

    // Process the errors.

    if (!result)
    {
        data.error_code = 1;
        data.error_message = "Failed to save the contours image \"";
        data.error_message += data.contours_image_path;
        data.error_message += "\".";
    }

    return result;
}

// Clears the image stream data.
bool image_stream_tool::clear
(
    image_stream_data & data
)
{
    bool result = true;

    // Initialize the state.

    if (result)
    {
        data.error_code = 0;
        data.error_message.clear();
    }

    // Deallocate the input image buffer.

    if (result)
        data.input_image = cv::Mat();

    // Deallocate the contours image buffer.

    if (result)
        data.contours_image = cv::Mat();

    return result;
}


