/*
 * project file : CS112_A3_Part1_S1,S2_20230470_20230602_20230344.cpp
 * Mahmoud Hesham AbdElhafeez 20230602 : Did filter rotate image, invert image, add frame to image and blur image. bonus: infrared filter
 * Yahia Diaa Eldien Mohammed 20230470 : Did filter brightness, grayscale, edge detection, merge two images. bonus: purple filter. orange filter: additional not in assignment.
 * Mohamed Esam AbdElmonem 20230344 : Did filter flip image, crop image, resize image and black and white filter. bonus: add sunlight.
 *
 * This project is a photo editor program.
 * The code is divided between two classes: FrontEnd and EditImage.
 * FrontEnd is responsible for taking inputs from the user and printing outputs and running the program.
 * EditImage is responsible for manipulating the image.
 *
 * algorithm :
 *
 * Rotate image:
 * rotating image by 90 degrees by creating new image with exchanging the height and width of the image
 * copying the pixels from the original image to the new image and return the new image
 * rotation of any other degree is made by rotating the image 90 degrees multiple times
 *
 * Invert image:
 * Inverting the image by creating a new image with the same size as the original image
 * Exchanging each pixel value with its complement
 * and return the new image
 *
 * Flip image:
 * Iterate through the first half of the image's width.
 * For each pixel in the row, swap it with the corresponding pixel on the opposite side of the image.
 * Repeat this process for all colors in the pixel.
 * Return the flipped image.
 *
 * grayscale:
 * For each pixel in the image, calculate the average of the red, green, and blue values.
 * Set all three color channels of the pixel to this average value to convert the image to grayscale.
 * Return the grayscale image.
 *
 * Brightness:
 *  Low brightness:
 *      For each pixel in the image, reduce the brightness by dividing the red, green, and blue values by 2.
 *      If any of the color values become negative, set them to 0.
 *      Return the image with reduced brightness.
 *
 *  High brightness:
 *      For each pixel in the image, increase the brightness by multiplying the red, green, and blue values by 1.5.
 *      If any of the color values exceed 255, set them to 255.
 *      Return the image with increased brightness.
 *
 *  Add frame:
 *      Create a new image with the same size as the original image.
 *      Calculate the thickness of the frame (size_frame) based on the size of the input image.
 *      Loop through each pixel in the input image:
 *          If the pixel is on the border of the image, change its color to the specified frame_color.
 *          Otherwise, copy the color of the pixel from the input image to the corresponding pixel in the res_img.
 *      If the frame_type is "fancy":
 *          Add three circles at the corners of the image with different sizes and colors.
 *      Return the resulting image res_img.
 *
 *  blur:
 *      For each pixel in the image, calculate the average of the surrounding pixels.
 *      calculating the average of the surrounding pixels using prefix sum matrix
 *      Set all three color channels of the pixel to this average value to blur the image.
 *      Return the blurred image.
 *
 *   infrared:
 *      Create a new image called res_img with the same width and height as the input image.
 *      Convert the input image to grayscale and store it in a new image called gray_img.
 *      Invert the colors of the grayscale image and store the result in a new image called inverted.
 *      Loop through each pixel in the input image:
 *          Set the green and blue channels of the res_img to the corresponding channels of the inverted image.
 *          Set the red channel of the res_img to 255 (maximum intensity).
 *      Return the resulting image res_img.
 *
 *  crop:
 *      Accept the coordinates (x, y) of the top-left corner of the cropping area, as well as the width and height of the desired cropped area.
 *      Create a new blank image with dimensions equal to the width and height of the cropping area.
 *      Iterate through each pixel in the cropping area of the original image.
 *      Copy the corresponding pixel values from the original image to the new cropped image.
 *      Save the cropped image to the specified file path.
 *
 *  resize:
 *      Accept the original image, new width, new height, and save path as input parameters.
 *      Create a new blank image with dimensions equal to the new width and height.
 *      Calculate the scaling factors for width and height.
 *      Iterate over each pixel in the new image:
 *      Calculate the corresponding pixel coordinates in the original image using the scaling factors.
 *      Copy the pixel values from the original image to the new image.
 *      Save the resized image to the specified file path.
 *
 *  black and white:
 *      Calculate Threshold:
 *          Iterate through each pixel in the image.
 *          Sum up the values of all color channels.
 *          Divide the sum by the total number of pixels (width * height * 3) to get the average pixel value. This is the threshold.
 *      Convert to Black and White:
 *          Calculate the threshold.
 *          Iterate through each pixel in the image.
 *          Calculate the average intensity by summing up the values of all color channels and dividing by 3.
 *          If the average intensity is less than the threshold, set the pixel value to 0 (black), otherwise set it to 255 (white).
 *          Save the modified image.
 *
 *  Add sunlight:
 *      Calculate the average brightness of the image.
 *      Determine the sunlight strength based on the average brightness.
 *      For each pixel in the image:
 *          a. Increase the red channel value by 15.
 *          b. Increase the green channel value by 40.
 *          c. Decrease the blue channel value by 15.
 *          d. Ensure that each channel value stays within the range [0, 255].
 *      Save the resulting image.
 *
 *  purple function:
 *      Create a new image result with the same dimensions as the input image.
 *      Copy each pixel from image to result.
 *      Define a purpleStrength variable.
 *      Iterate over each pixel in the image:
 *          If the green channel value of the pixel is greater than or equal to half of purpleStrength:
 *          Reduce the green channel value by 20%.
 *          Otherwise, set the green channel value to 0.
 *
 *
 *
*/
#include "Image_Class.h"
#include <iomanip>
#include <limits>
#include <vector>
#include <cmath>
using namespace std;

class EditImage: protected Image {

private:

    Image rotate_img_90(Image &main_img) {
        // Create a new image with swapped width and height
        Image res_img(main_img.height, main_img.width);
        // Iterate through the pixels of the main image
        for (int height = 0; height < main_img.height; height++) {
            for (int width = 0; width < main_img.width; width++) {
                // Rotate the pixel values and assign them to the new image
                for (int color = 0; color < 3; color++) {
                    res_img(height, width, color) = main_img(width, main_img.height - 1 - height, color);
                }}}
        // Return the rotated image
        return res_img;
    }

    void change_colors(Image &res_img, int width, int height, int color) {
        int red = 0;
        int green = 0;
        int blue = 0;
        switch (color) {
            case 1:  // color red
                red = 150;
                break;
            case 2:  // color green
                green = 120;
                break;
            case 3:  // color blue
                blue = 180;
                break;
            case 4:  // color black
                red = 0;
                green = 0;
                blue = 0;
                break;
            case 5:  // color white
                red = 255;
                green = 255;
                blue = 255;
                break;
            default:
                break;
        }

        res_img(width, height, 0) = red;
        res_img(width, height, 1) = green;
        res_img(width, height, 2) = blue;

    }

    bool check_circle_corners(Image &main_img, int width, int height, double ratio) {
        int x = width;
        int y = height;
        int x_dif = main_img.width - x;
        int y_dif = main_img.height - y;

        double r_sq = main_img.width * main_img.height * ratio;
        // Check if the point lies within the quarter circles in the corners
        if (sq(x) + sq(y) < r_sq ||            // Top-left quarter circle
            (sq(x_dif) + sq(y) < r_sq) ||     // Top-right quarter circle
            (sq(x) + sq(y_dif) < r_sq) ||     // Bottom-left quarter circle
            (sq(x_dif) + sq(y_dif) < r_sq)    //Bottom-right quarter circle
                )
        {
            return true; // Inside one of the quarter circles
        } else {
            return false; // Not inside any of the quarter circles
        }
    }


    void add_circle_corners(Image &res_img, int color, double ratio) {
        for (int width = 0; width < res_img.width; width++) {
            for (int height = 0; height < res_img.height; height++) {
                if (check_circle_corners(res_img, width, height, ratio)) {
                    change_colors(res_img, width, height, color);
                }
            }}}

    vector<vector<vector<int>>> summed_table(const Image &img) {
        int width = img.width;
        int height = img.height;

        vector<vector<vector<int>>> table(width, vector<vector<int>>(height, vector<int>(3)));

        // compute the first row
        for (int col = 0; col < width; col++) {
            table[col][0][0] = img(col, 0, 0);
            table[col][0][1] = img(col, 0, 1);
            table[col][0][2] = img(col, 0, 2);
            if (col > 0) {
                for (int color = 0; color < 3; color++) {
                    table[col][0][color] += table[col - 1][0][color];
                }
            }
        }

        // compute the first column
        for (int row = 1; row < height; row++) {
            table[0][row][0] = img(0, row, 0);
            table[0][row][1] = img(0, row, 1);
            table[0][row][2] = img(0, row, 2);
            for (int color = 0; color < 3; color++) {
                table[0][row][color] += table[0][row - 1][color];
            }
        }

        for (int col = 1; col < width; col++) {
            for (int row = 1; row < height; row++) {
                for (int color = 0; color < 3; color++) {
                    table[col][row][color] = img(col, row, color) + table[col - 1][row][color] + table[col][row - 1][color] - table[col - 1][row - 1][color];
                }
            }
        }

        return table;
    }

    int calculateThreshold(Image &image) {
        int total_sum = 0;
        int total_pixels = image.width * image.height * 3; // Total number of color channels
        // Calculate sum of all pixel values
        for (int width = 0; width < image.width; width++) {
            for (int height = 0; height < image.height; height++) {
                for (int colour = 0; colour < 3; colour++) {
                    total_sum += image.getPixel(width, height, colour);
                }
            }
        }
        // Calculate and return the average pixel value
        return total_sum / total_pixels;
    }

    // Define a function to calculate the average brightness of the image
    unsigned int calculateAverageBrightness(const Image &image) {
        unsigned int totalBrightness = 0;
        int numPixels = image.width * image.height * image.channels;
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    totalBrightness += image.getPixel(i, j, k);
                }
            }
        }
        return totalBrightness / numPixels;
    }

protected:

    static double sq(int num){
        return num*num;
    }

    Image invert_img(Image &main_img) {
        // Create a new image with the same dimensions
        Image res_img(main_img.width, main_img.height);
        // Iterate through the pixels of the main image
        for (int width = 0; width < main_img.width; width++) {
            for (int height = 0; height < main_img.height; height++) {
                // Invert the color values and assign them to the new image
                for (int color = 0; color < 3; color++) {
                    res_img(width, height, color) = 255 - main_img(width, height, color);
                }}}
        // Return the inverted image
        return res_img;
    }


    Image rotate_img(Image &main_img, int rotation = 90) {
        // The rotation is achieved by calling the rotate_img_90 function multiple times based on the desired angle

        // Rotate the image by 90 degrees
        if (rotation == 90) {
            return rotate_img_90(main_img);
        }
        // Rotate the image by 180 degrees
        Image rotated_img_180 = rotate_img_90(main_img);
        if (rotation == 180) {
            return rotate_img_90(rotated_img_180);
        }
        // Rotate the image by 270 degrees
        Image rotated_img_270 = rotate_img_90(rotated_img_180);
        if (rotation == 270) {
            return rotate_img_90(rotated_img_270);
        }
        else {
            return main_img;
        }
    }


    Image flip_img_horizontally(Image &image) {
        Image res_img(image.width, image.height);
        int temp;
        for (int width = 0; width < image.width / 2; width++) { // Iterate only half width
            for (int height = 0; height < image.height; height++) {
                // Swap pixels horizontally
                for(int colour = 0; colour < 3; colour++) {
                    temp = image.getPixel(width, height, colour);
                    res_img.setPixel(width, height, colour, image.getPixel(image.width - 1 - width, height, colour));
                    res_img.setPixel(image.width - 1 - width, height, colour, temp);
                }}}
        return res_img;
    }


    Image flip_img_vertically(Image &image) {
        Image res_img(image.width, image.height);
        int temp;
        for (int height = 0; height < image.height / 2; height++) { // Iterate only half height
            for (int width = 0; width < image.width; width++) {
                // Swap pixels vertically
                for(int colour = 0; colour < 3; colour++) { // Loop through each color channel (assuming RGB)
                    temp = image.getPixel(width, height, colour); // Store the current pixel value in temp
                    res_img.setPixel(width, height, colour, image.getPixel(width, image.height - 1 - height, colour)); // Replace current pixel with corresponding pixel from the other side
                    res_img.setPixel(width, image.height - 1 - height, colour, temp); // Replace corresponding pixel from the other side with temp
                }}}
        return res_img;
    }

    Image gray(const Image &image){
        Image res_img(image.width, image.height);
        // Iterate through each pixel in the image
        for(int i = 0 ; i < image.width ; i++){
            for (int j = 0 ; j < image.height ; j ++){
                unsigned int avg = 0 ;
                // Calculate the average of the RGB values
                for (int k = 0; k < 3; ++k) {
                    avg += image(i , j , k);
                }
                avg /= 3 ;
                // Set all RGB values to the average to grayscale the image
                for (int k = 0; k < 3; ++k) {
                    res_img(i , j , k) = avg;
                }}}
        // Return the grayscale image
        return res_img;
    }

    Image low_brightness(Image &image){
        Image res_img(image.width, image.height);
        // Iterate through each pixel in the image
        for(int i = 0 ; i < image.width ; i++){
            for (int j = 0 ; j < image.height ; j ++){
                // Iterate through each color channel (red, green, blue)
                for (int k = 0; k < 3; ++k) {
                    // Reduce the color value by dividing it by 2
                    res_img(i,j,k) = image(i,j,k) * 1/2;
                    // If the color value becomes negative, set it to 0
                    if (image(i,j,k) < 0){
                        res_img(i,j,k) = 0 ;
                    }}}}
        return res_img;
    }

    Image high_brightness(Image &image){
        // Iterate through each pixel in the image
        for(int i = 0 ; i < image.width ; i++){
            for (int j = 0 ; j < image.height ; j ++){
                // Iterate through each color channel (red, green, blue)
                for (int k = 0; k < 3; ++k){
                    if(image(i,j,k) * 3/2 > 255){
                    // If the color value multiplied by 1.5 exceeds 255, set it to 255
                        image(i,j,k) = 255 ;
                    }
                    else {
                        // Otherwise, increase the color value by multiplying it by 1.5
                        image(i,j,k) = image(i,j,k) * 3/2;
                    }}}}
        return image;
    }


    Image add_frame(Image &main_img, int frame_color, const string& frame_type = "default") {
        Image res_img(main_img.width, main_img.height);
        int size_frame = max(main_img.width, main_img.height)/60; // getting a thickness of the frame relative to the size of the image
        for (int width = 0; width < main_img.width; width++) {
            for (int height = 0; height < main_img.height; height++) {

                if (width < size_frame || width > main_img.width - size_frame ||
                    height < size_frame || height > main_img.height - size_frame) {
                    change_colors(res_img, width, height, frame_color);
                }
                else {
                    for (int color = 0; color < 3; color++) {
                        res_img(width, height, color) = main_img(width, height, color);
                    }
                }
        }}

        if (frame_type == "fancy") {
            add_circle_corners(res_img, frame_color, 0.005);
            add_circle_corners(res_img, 5, 0.002);
            add_circle_corners(res_img, 4, 0.0005);
        }

        return res_img;
    }


    Image blur_img(const Image &img, int matrix_size) {
        vector<vector<vector<int>>> prefix_sum = summed_table(img);

        Image res_image(img.width, img.height);

        for(int width = 0; width < img.width; width++){
            for(int height = 0; height < img.height; height++){
                for(int color = 0; color < 3; color++){

                    int start_width = max(0, width-matrix_size + 1);
                    int end_width = min(img.width-1, width);
                    int start_height = max(0, height-matrix_size + 1);
                    int end_height = min(img.height-1, height);
                    double num_pixels = (end_width-start_width + 1) * (end_height-start_height + 1);

                        double color_avg = (prefix_sum[width][height][color]
                                            - prefix_sum[width][max(0, height-matrix_size)][color]
                                            - prefix_sum[max(0, width-matrix_size)][height][color]
                                            + prefix_sum[max(0, width-matrix_size)][max(0, height-matrix_size)][color])
                                           / num_pixels;

                        res_image(width, height, color) = color_avg;

            }}}

        return res_image;
    }


    Image crop_image(Image& image1, int x, int y, int width, int height) {

        // Create a new image with specified dimensions
        Image cropped_image(width, height);

        // Copy pixels from original image to cropped image
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int colour = 0; colour < 3; colour++) {
                    cropped_image.setPixel(i, j, colour, image1.getPixel(x + i, y + j, colour));
                }}}
        return cropped_image;

    }


    Image convertToBlackAndWhite(Image &image) {
        int threshold = calculateThreshold(image); // Calculate the threshold based on the image's average intensity

        Image res_image(image.width, image.height); // Create a new image with the same dimensions as the original
        // Convert the image to black and white using the calculated threshold
        for (int width = 0; width < image.width; width++) {
            for (int height = 0; height < image.height; height++) {
                // Calculate the average intensity of the pixel
                int pixel_intensity = 0;
                for (int colour = 0; colour < 3; colour++) {
                    pixel_intensity += image.getPixel(width, height, colour);
                }
                pixel_intensity /= 3;

                // Set pixel to black or white based on the threshold
                int new_value = (pixel_intensity < threshold) ? 0 : 255;
                for (int colour = 0; colour < 3; colour++) {
                    res_image.setPixel(width, height, colour, new_value);
                }
            }
        }

        return res_image;
    }


    Image merge_image(Image &image1, Image &image2) {
        // Iterate over the dimensions of the smaller image
        unsigned int min_width = std::min(image1.width, image2.width);
        unsigned int min_height = std::min(image1.height, image2.height);
        Image mergedImage(min_width, min_height);
        for (int i = 0; i < min_width; ++i) {
            for (int j = 0; j < min_height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    // Calculate the average of corresponding pixels from both images
                    mergedImage(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }

        // Save the merged image
        // resizeImageNearestNeighbor(mergedImage, min_width,min_height);
        return mergedImage;
    }


    Image EdgeDetection(Image & main_img) {
        Image grayImage = gray(main_img);
        Image edgeImage(grayImage.width, grayImage.height);
        for (int i = 1; i < grayImage.width - 1; ++i) {
            for (int j = 1; j < grayImage.height - 1; ++j) {
                // Apply Sobel operator on grayscale image
                int gx = (grayImage(i+1, j-1, 0) + 2*grayImage(i+1, j, 0) + grayImage(i+1, j+1, 0)) - (grayImage(i-1, j-1, 0) + 2*grayImage(i-1, j, 0) + grayImage(i-1, j+1, 0));
                int gy = (grayImage(i-1, j+1, 0) + 2*grayImage(i, j+1, 0) + grayImage(i+1, j+1, 0)) - (grayImage(i-1, j-1, 0) + 2*grayImage(i, j-1, 0) + grayImage(i+1, j-1, 0));
                int magnitude = sqrt(gx*gx + gy*gy);

                // Edge thresholding
                if (magnitude > 128)
                    edgeImage(i, j, 0) = 255; // White
                else
                    edgeImage(i, j, 0) = 0; // Black
            }
        }
        return edgeImage;
    }


    Image resize_img(const Image& image1, int new_width, int new_height) {
        // Create a new image with specified dimensions
        Image resized_image(new_width, new_height);
        // Calculate scaling factors
        float x_scale = (float)image1.width / new_width;
        float y_scale = (float)image1.height/ new_height;

        for (int x = 0; x< new_width; x++) {
            for (int y = 0; y < new_height; y++) {
                // Corresponding pixel in original image
                int orig_x = x * x_scale;
                int orig_y = y * y_scale;

                // Copy pixel values to resized image
                for (int colour = 0; colour < 3; colour++) {
                    resized_image.setPixel(x, y, colour, image1.getPixel(orig_x, orig_y, colour));
                }}}

        return resized_image;
    }


    Image infrared(Image&image){
        Image res_img(image.width, image.height);
        Image gray_img = gray(image);
        Image inverted = invert_img(gray_img);
        for (int width = 0; width < image.width; width++) {
            for (int height = 0; height < image.height; height++) {
                res_img(width, height, 1) = inverted(width, height, 1);
                res_img(width, height, 2) = inverted(width, height, 2);
                res_img(width, height, 0) = 255;
            }}

        return res_img;
    }


    Image purple(const Image &image){

        Image result(image.width,image.height);
        for(int i = 0; i<image.width;i++){
            for(int  j = 0 ; j<image.height;j++){
                for(int k = 0 ; k<image.channels ; k++){
                    result(i,j,k)= image(i,j,k);
                }
            }
        }
        unsigned int purpleStrength = 15;
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                //image(i, j, 0) =image(i, j, 0) + purpleStrength; // Increase red channel
                if (result(i, j, 1) >= purpleStrength / 2) {
                    result(i, j, 1) = result(i, j, 1)*0.8;
                } else {
                    result(i, j, 1) = 0; // Ensure it doesn't become negative
                }

                //image(i, j, 2) =     image(i, j, 2) + purpleStrength; // Increase blue channel
//                for(int k = 0 ; k<3; k++){
//                    result(i,j,k) = image(i,j,k);
//                }
            }
        }
        return result ;
    }


    Image orange(const Image &image){
        Image result(image.width,image.height);
        for(int i = 0; i<image.width;i++){
            for(int  j = 0 ; j<image.height;j++){
                for(int k = 0 ; k<image.channels ; k++){
                    result(i,j,k)= image(i,j,k);
                }
            }
        }
        unsigned int purpleStrength = 15;
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                //image(i, j, 0) =image(i, j, 0) + purpleStrength; // Increase red channel
                if (result(i, j, 1) >= purpleStrength / 2) {
                    result(i, j, 1) = result(i, j, 1)*0.6;
                } else {
                    result(i, j, 1) = 0; // Ensure it doesn't become negative
                }
                if (image(i, j, 2) >= purpleStrength / 2) {
                    result(i, j, 2) = image(i, j, 1)*0;
                } else {
                    result(i, j, 1) = 0; // Ensure it doesn't become negative
                }
                //image(i, j, 2) =     image(i, j, 2) + purpleStrength; // Increase blue channel

            }}
        return result ;
    }


    Image addSunlight(const Image &image) {
        Image result(image.width, image.height);

        unsigned int averageBrightness = calculateAverageBrightness(image);


        unsigned int sunlightStrength = sqrt(averageBrightness) / 2;

        // Apply sunlight effect
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                int red = image.getPixel(i, j, 0) + 15;
                int green = image.getPixel(i, j, 1) + 40;
                int blue = image.getPixel(i, j, 2) - 15;
                // Ensure pixel values don't exceed 255 or fall below 0
                red = red > 255 ? 255 : (red < 0 ? 0 : red);
                green = green > 255 ? 255 : (green < 0 ? 0 : green);
                blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);


                result.setPixel(i, j, 0, red);
                result.setPixel(i, j, 1, green);
                result.setPixel(i, j, 2, blue);
            }
        }

        return result;
    }

};

class FrontEnd: private EditImage {
private:
    Image img;

    string load_img() {
        string img_name;
        cin >> img_name;
            try {
                img.loadNewImage(img_name);
                cout << "Image loaded successfully" << endl;
                return img_name;
            }
            catch (invalid_argument const &e) {
                cerr << e.what() << endl;
            }
        return load_img();
    }


    bool valid_output(const string& output_name) {
        if (output_name.find(".jpg") != string::npos) {
            return true;
        }
        if (output_name.find(".bmp") != string::npos) {
            return true;
        }
        if (output_name.find(".png") != string::npos) {
            return true;
        }
        if (output_name.find(".tga") != string::npos) {
            return true;
        }
        return false;
    }

    void save_img(Image &res_img) {
        string img_name;
        cin >> img_name;
        if(valid_output(img_name)){
            res_img.saveImage(img_name);
            cout << "Image saved successfully" << endl;
            return;
        }
        else {
            cerr << "Invalid image name" << endl;
            cerr << "Try name with valid extension" << endl;
            save_img(res_img);
        }
    }

    void program_menu(){
        cout << "Welcome to Photo Editor" << endl;
        cout << "First we need to load an image" << endl;
        cout << "Please make sure image has same directory as project file" << endl;
    }

    void take_operation(){
        cout << "Filters menu" << endl;
        cout << "1) Rotate image" << endl;
        cout << "2) Invert image" << endl;
        cout << "3) Flip image" << endl;
        cout << "4) Grayscale Filter" << endl;
        cout << "5) brightness Filter" << endl;
        cout << "6) Add frame" << endl;
        cout << "7) Blur image" << endl;
        cout << "8) Crop image" << endl;
        cout << "9) Black and white Filter" << endl;
        cout << "10) Merge two images "<< endl ;
        cout << "11) Edge detection "<< endl;
        cout << "12) Resize image" << endl;
        cout << "13) Infrared Filter" << endl;
        cout << "14) Purple filter" << endl;
        cout << "15) Add Sunlight" << endl;
        cout << "16) Orange filter" << endl;
    }

    int take_choice(int start, int end){
        // making sure to take a valid choice  from [start, end]
        int choice;
        cout << "Enter choice from (" << start << "-" << end << "):";
        cin >> choice;
        if (cin.fail() || choice < start || choice > end) {
            cout << "Error!! invalid input." << endl;
            cin.clear(); // clear error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            return take_choice(start, end);
        }
        return choice;
    }

    int take_rotation(){
        string rotation;
        cout << "Enter rotation (90, 180, 270) degree:";
        cin >> rotation;
        if (rotation == "90" || rotation == "180" || rotation == "270"){
            return stoi(rotation);
        }
        else{
            cout << "Error!! invalid input\n Note: Enter number only" << endl;
            return take_rotation();
        }
    }

    Image flip_menu() {
        cout << "1) Horizontal flip" << endl;
        cout << "2) Vertical flip" << endl;
        int flip = take_choice(1, 2);
        if (flip == 1) {
            return flip_img_horizontally(img);
        } else {
            return flip_img_vertically(img);
        }
    }

    Image brightness(){
        cout << "1)High brightness"
                "2)Low brightness \n";
       int op = take_choice(1,2);
        if (op == 1){
            return high_brightness(img);
        }
        else{
            return low_brightness(img);
        }
    }

    Image frame_menu(){
        cout << "Choose frame color:" << endl;
        cout << "1) Red" << endl;
        cout << "2) Green" << endl;
        cout << "3) Blue" << endl;
        cout << "4) Black" << endl;
        int frame_color = take_choice(1, 4);

        cout << "Choose frame type:" << endl;
        cout << "1) Add normal frame" << endl;
        cout << "2) Add fancy frame" << endl;
        int frame = take_choice(1, 2);

        if (frame == 1) {
            return add_frame(img, frame_color);
        }
        else {
            return add_frame(img, frame_color, "fancy");
        }
    }


    Image blur_menu(){
        cout << "Enter blur intensity" << endl;
        int blur_intensity = take_choice(3, 10);
        return blur_img(img, sq(blur_intensity));
    }

    Image crop_menu(){
        int x, y, width, height;

        // Get cropping dimensions from the user
        cout << "Enter the x and y coordinates of the upper left corner of the cropped area: ";
        cin >> x >> y;
        cout << "Enter the width and height of the cropped area: ";
        cin >> width >> height;

        // Ensure the cropping dimensions are within the bounds of the original image
        if (x < 0 || y < 0 || width <= 0 || height <= 0 || x + width > img.width || y + height > img.height) {
            cout << "Invalid cropping dimensions. Please ensure the dimensions are within the bounds of the original image." << endl;
            return crop_menu();
        }

        return crop_image(img, x, y, width, height);
    }

    Image load_new_img() {
        cout << "Enter image name with  any of the following\n"
                "extensions (.jpg, .bmp, .png, .tga):";
        string img_name;
        cin >> img_name;
        try {
            img.loadNewImage(img_name);
            cout << "Image loaded successfully" << endl;
            return img_name;
        }
        catch (invalid_argument const &e) {
            cerr << e.what() << endl;
        }
        return load_img();
    }

    Image main_merge (){
        cout<<"insert the photo which you wanna merge it with the origin "<<endl;
     Image image1 = load_new_img();
        return merge_image(image1, img);
    }

    Image resize_menu(){
        cout << "Enter new width and height" << endl;
        int new_width, new_height;
        cin >> new_width >> new_height;
        return resize_img(img, new_width, new_height);
    }

    Image do_operation() {
        take_operation();
        int operation = take_choice(1, 16);
        switch (operation) {
            case 1:{
                int rotation = take_rotation();
                return rotate_img(img, rotation);
            }
            case 2:{
                return invert_img(img);
            }
            case 3:{
                return flip_menu();
                }
            case 4:{
                return gray(img);
            }
            case 5:{
                return brightness();
            }
            case 6:{
                return frame_menu();
            }
            case 7:{
                return blur_menu();
            }
            case 8:{
                return crop_menu();
            }
            case 9:{
                return convertToBlackAndWhite(img);
            }
            case 10:{
              return main_merge();
            }
            case 11: {
                return EdgeDetection(img);
            }
            case 12:{
                return resize_menu();
            }
            case 13:{
                return infrared(img);
            }
            case 14:{
                return purple(img);
            }
            case 15:{
                return addSunlight(img);
            }
            case 16:{
                return orange(img);
            }

            default:{
                return img;
            }
        }
    }

public:

    void run() {
        program_menu();
        while(true){
            cout <<"1) Load Image\n"
                   "2) Exit program\n";
            int choice = take_choice(1,2);

            if (choice == 2){
                break;
            }

            if(choice == 1){
                cout << endl << setw(25) << "Loading image" << endl;
                cout << "Enter image name with  any of the following\n"
                        "extensions (.jpg, .bmp, .png, .tga):";
                string img_name = load_img();

                while(true){
                    Image res_img = do_operation();

                    cout << endl << setw(25) << "Saving image" << endl;
                    cout << "Enter image name with  any of the following\n"
                            "extensions (.jpg, .bmp, .png, .tga):";
                    save_img(res_img);

                    cout << "1) Apply new filter on loaded image: " << img_name << endl <<
                         "2) Back to main menu\n";
                    int s_choice = take_choice(1,2);

                    if(s_choice== 1){
                        continue;
                    }

                    if(s_choice==2){
                        break;
                    }
                }
            }
        }
    }

};


int main() {
    FrontEnd Photo_Editor;
    Photo_Editor.run();

    return 0;
}
