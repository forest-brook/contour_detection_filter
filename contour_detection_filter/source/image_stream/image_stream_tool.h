#pragma once


class image_stream_data;                                        // Uses the image stream data.
class image_filter_data;                                        // Uses the image filter data.

// Image stream tool.
class image_stream_tool
{
public:

    bool load_input_image                                       // Loads the input image.
    (
        image_stream_data & data
    );
    bool save_filtered_image                                    // Saves the filtered image.
    (
        image_stream_data & data,
        image_filter_data & filter_data
    );
    bool save_contours_image                                    // Saves the contours image.
    (
        image_stream_data & data,
        image_filter_data & filter_data
    );
    bool clear                                                  // Clears the image stream data.
    (
        image_stream_data & data
    );
};
