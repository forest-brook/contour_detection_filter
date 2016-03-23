// Uses the strings.
#include <string>

// Uses the standard input and output routines.
#include <stdio.h>

// Uses the data conversion functions.
#include <stdlib.h>

// Uses the application options.
#include <getopt.h>

// Uses the image filter data.
#include "image_filter/image_filter_data.h"
#include "image_filter/image_filter_tool.h"

// Uses the image stream data.
#include "image_stream/image_stream_data.h"
#include "image_stream/image_stream_tool.h"


int main
(
    int argc,
    char * argv []
)
{
    bool result = true;

    // Set the default values.

    bool print_help;
    bool process_image;
    std::string input_image_path;
    int median_filter_size;
    std::string filtered_image_path;
    std::string contours_image_path;
    double edge_linking_threshold;
    double strong_edge_threshold;
    if (result)
    {
        print_help = false;
        process_image = true;
        input_image_path = "input_image.jpeg";
        median_filter_size = 5;
        edge_linking_threshold = 20.0;
        strong_edge_threshold = 50.0;
        filtered_image_path = "filtered_image.jpeg";
        contours_image_path = "contours_image.jpeg";
    }

    // Apply the application options.

    if (result)
    {
        struct option long_options [] =
            {
                {"input_image", required_argument, 0, 'i'},
                {"median_filter_size", required_argument, 0, 'm'},
                {"filtered_image", required_argument, 0, 'f'},
                {"edge_linking_threshold", required_argument, 0, 'a'},
                {"strong_edge_threshold", required_argument, 0, 'b'},
                {"contours_image", required_argument, 0, 'o'},
                {"help", no_argument, 0, 'h'},
                {0, 0, 0, 0}
            };

        int c;
        int option_index = 0;

        while (1)
        {
            c =
                getopt_long
                (
                    argc,
                    argv,
                    "i:m:f:a:b:o:h",
                    long_options,
                    &option_index
                );

            if (c == -1)
                break;

            switch (c)
            {
            case 'i':
                input_image_path = optarg;
                break;
            case 'm':
                median_filter_size = atoi(optarg);
                break;
            case 'f':
                filtered_image_path = optarg;
                break;
            case 'a':
                edge_linking_threshold = atof(optarg);
                break;
            case 'b':
                strong_edge_threshold = atof(optarg);
                break;
            case 'o':
                contours_image_path = optarg;
                break;
            case 'h':
                print_help = true;
                process_image = false;
                break;
            default:
                printf("Error:\nReceived the invalid option \"%s\".\n", argv[option_index]);
                print_help = true;
                process_image = false;
                break;
            }
        }
    }

    // Check the options.

    if (result)
    {
        // Check the median filter size.

        if
        (
            median_filter_size <= 0 ||
            (median_filter_size & 1) == 0
        )
        {
            printf("Error:\nMedian filter aperture size median_filter_size must be odd and greater than 1.\n");
            result = false;
        }

        // Check the strong edge threshold.

        if (strong_edge_threshold < 0.0)
        {
            printf("Error:\nStrong edge threshold value is invalid.\n");
            result = false;
        }

        // Check the edge linking threshold.

        if
        (
            edge_linking_threshold < 0.0 ||
            strong_edge_threshold < edge_linking_threshold
        )
        {
            printf("Error:\nEdge linking threshold is invalid.\n");
            result = false;
        }

        // Process the errors.

        if (!result)
        {
            print_help = true;
            process_image = false;
        }

        result = true;
    }

    // Print the help.

    if (result)
    {
        if (print_help)
        {
            printf("Usage: contour_detection_filter [OPTION]\n");
            printf("Filters the input image and detects the contours.\n");
            printf("\n");
            printf("  -i, --input_image IMAGE_PATH          specifies input image file IMAGE_PATH\n");
            printf("                                          (default \"input_image.jpeg\")\n");
            printf("  -m, --median_filter_size SIZE         changes the median filter aperture\n");
            printf("                                          SIZE (default 5)\n");
            printf("  -f, --filtered_image IMAGE_PATH       specifies the file IMAGE_PATH\n");
            printf("                                          to write the filtered image\n");
            printf("                                          (default \"filtered_image.jpeg\")\n");
            printf("  -a, --edge_linking_threshold VALUE    specifies edge linking threshold\n");
            printf("                                          VALUE (default 20)\n");
            printf("  -b, --strong_edge_threshold VALUE     specifies strong edge threshold\n");
            printf("                                          VALUE (default 50)\n");
            printf("  -o, --contours_image IMAGE_PATH       specifies the file IMAGE_PATH\n");
            printf("                                          to write the contours image\n");
            printf("                                          (default \"contours_image.jpeg\")\n");
            printf("  -h, --help                            display this help and exit\n");
            printf("\n");
        }
    }

    // Process the specified image.

    if (result)
    {
        if (process_image)
        {
            // Print the state.

            if (result)
            {
                printf("input_image = \"%s\"\n", input_image_path.c_str());
                printf("median_filter_size = %d\n", median_filter_size);
                printf("filtered_image = \"%s\"\n", filtered_image_path.c_str());
                printf("edge_linking_threshold = %0.3f\n", edge_linking_threshold);
                printf("strong_edge_threshold = %0.3f\n", strong_edge_threshold);
                printf("contours_image = \"%s\"\n", contours_image_path.c_str());
            }

            // Initialize the image stream data.

            image_stream_data stream_data;
            if (result)
            {
                stream_data.input_image_path = input_image_path;
                stream_data.filtered_image_path = filtered_image_path;
                stream_data.contours_image_path = contours_image_path;
            }

            // Initialize the image filter data.

            image_filter_data filter_data;
            if (result)
            {
                filter_data.median_filter_size = median_filter_size;
                filter_data.edge_linking_threshold = edge_linking_threshold;
                filter_data.strong_edge_threshold = strong_edge_threshold;
            }

            // Load the input image.

            if (result)
            {
                image_stream_tool stream_tool;
                result = stream_tool.load_input_image(stream_data);

                if (result)
                    printf("Image \"%s\" was loaded successfully.\n", stream_data.input_image_path.c_str());
                else
                    printf("Error:\n%s\n", stream_data.error_message.c_str());
            }

            // Filter the image.

            if (result)
            {
                image_filter_tool filter_tool;
                result =
                    filter_tool.apply_median_filter
                    (
                        filter_data,
                        stream_data.input_image
                    );

                if (result)
                    printf("Image was filtered successfully.\n");
                else
                    printf("Error:\n%s\n", filter_data.error_message.c_str());
            }

            // Detect the contours.

            if (result)
            {
                image_filter_tool filter_tool;
                result = filter_tool.detect_contours(filter_data);

                if (result)
                    printf("%d contours were detected.\n", (int) filter_data.contours.size());
                else
                    printf("Error:\n%s\n", filter_data.error_message.c_str());
            }

            // Save the filtered image.

            if (result)
            {
                image_stream_tool stream_tool;
                result =
                    stream_tool.save_filtered_image
                    (
                        stream_data,
                        filter_data
                    );

                if (result)
                    printf("Filtered image \"%s\" was saved successfully.\n", stream_data.filtered_image_path.c_str());
                else
                    printf("Error:\n%s\n", stream_data.error_message.c_str());
            }

            // Save the contours image.

            if (result)
            {
                image_stream_tool stream_tool;
                result =
                    stream_tool.save_contours_image
                    (
                        stream_data,
                        filter_data
                    );

                if (result)
                    printf("Contours image \"%s\" was saved successfully.\n", stream_data.contours_image_path.c_str());
                else
                    printf("Error:\n%s\n", stream_data.error_message.c_str());
            }
        }
    }

    return result ? 0 : 1;
}
