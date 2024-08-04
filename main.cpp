#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "mixer_processor.h"
#include <thread>
#include <array>
#include "timing.h"



#define APPLY_LOW_PASS_FILTER true // low pass filter the noise Set to false to disable low-pass filtering

#define NUM_OF_NOISE_FRAMES  30

#define FULLSCREEN_MODE false // Set to false for windowed mode

#define SHOW_TIMING true // Show timing on screen

#define NOISE_WEIGHT .8 // 0.5 // Adjust this value as needed (e.g., 0.33 for 1/3)

#define OUTPUT_GAIN 1.8 // Adjust this value for output gain of the final image




int main()
{
    std::string imageFile1 = "/home/jim/Desktop/PiTests/images/image.jpg";  // path/to/your/first/image.jpg"; // Path to your first image file
    std::string imageFile2 = "/home/jim/Desktop/PiTests/images/image2.jpg"; // path/to/your/second/image.jpg"; // Path to your second image file

    std::array<cv::Mat, 6> imageArray;

    imageArray[0] = loadImage(imageFile1);
    imageArray[1] = loadImage(imageFile2);

    cv::Mat img1 = imageArray[0];
    cv::Mat img2 = imageArray[1];
    cv::Mat transformedImg;

 
    // generate noise
    std::vector<cv::Mat> noiseFrames = generateNoiseFrames(img1.cols, img1.rows, NUM_OF_NOISE_FRAMES, APPLY_LOW_PASS_FILTER);
    //  Create the parabolic lookup table for gamma correction
    cv::Mat lut = createParabolicLUT();

    if (FULLSCREEN_MODE)
    {
        cv::namedWindow("Blended Image Playback", cv::WINDOW_NORMAL);
        cv::setWindowProperty("Blended Image Playback", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN); // Set window to fullscreen
    }


    // Calculate the weight of the blended image
    const float imageBlendWeight = .5;

    float fade_time = 3.00;

    while (true)
    {
        blendImagesAndNoise(img1, img2, noiseFrames, transformedImg, lut, imageBlendWeight, NOISE_WEIGHT, OUTPUT_GAIN);

        cv::imshow("Blended Image Playback", transformedImg);

        // Check for escape key press
        int key = cv::waitKey(1);
        if (key == 27)
        { // ASCII code for the escape key
            break;
        }

        Loop_Timing(SHOW_TIMING);

    }

    return 0;
}