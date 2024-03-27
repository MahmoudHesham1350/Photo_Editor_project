/*
 * project file : CS112_A3_Part1_S1,S2_20230470_20230602_20230344.cpp
 * Mahmoud Hesham AbdEhafeez 20230602 : Did filters rotate image and invert image
 * Yahia Diaa Eldien Mohammed 20230470 : Did filters brightness and grayscale
 * Mohamed Esam AbdElmonem 20230344 : Did filter flip image
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
 *
*/
#include "Image_Class.h"
#include <iomanip>
#include <limits>
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

protected:

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
    }


    Image flip_img_horizontally(Image &image) {
        int temp;
        for (int width = 0; width < image.width / 2; width++) { // Iterate only half width
            for (int height = 0; height < image.height; height++) {
                // Swap pixels horizontally
                for(int colour = 0; colour < 3; colour++) {
                    temp = image.getPixel(width, height, colour);
                    image.setPixel(width, height, colour, image.getPixel(image.width - 1 - width, height, colour));
                    image.setPixel(image.width - 1 - width, height, colour, temp);
                }}}
        return image;
    }


    Image flip_img_vertically(Image &image) {
        int temp;
        for (int height = 0; height < image.height / 2; height++) { // Iterate only half height
            for (int width = 0; width < image.width; width++) {
                // Swap pixels vertically
                for(int colour = 0; colour < 3; colour++) { // Loop through each color channel (assuming RGB)
                    temp = image.getPixel(width, height, colour); // Store the current pixel value in temp
                    image.setPixel(width, height, colour, image.getPixel(width, image.height - 1 - height, colour)); // Replace current pixel with corresponding pixel from the other side
                    image.setPixel(width, image.height - 1 - height, colour, temp); // Replace corresponding pixel from the other side with temp
                }}}
        return image;
    }

    Image gray(Image &image){
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
                    image(i , j , k) = avg;
                }}}
        // Return the grayscale image
        return image;
    }

    Image low_brightness(Image &image){
        // Iterate through each pixel in the image
        for(int i = 0 ; i < image.width ; i++){
            for (int j = 0 ; j < image.height ; j ++){
                // Iterate through each color channel (red, green, blue)
                for (int k = 0; k < 3; ++k) {
                    // Reduce the color value by dividing it by 2
                    image(i,j,k) = image(i,j,k) * 1/2;
                    // If the color value becomes negative, set it to 0
                    if (image(i,j,k) < 0){
                        image(i,j,k) = 0 ;
                    }}}}
        return image;
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


};

class FrontEnd: private EditImage {
private:
    Image img;

    string load_img() {
        cout << "Enter image name with  any of the following\n"
                "extensions (.jpg, .bmp, .png, .tga):";
        string img_name;
        cin >> img_name;
            try {
                img.loadNewImage(img_name);
                cout << "Image loaded successfully" << endl;
                return img_name;
            }
            catch (invalid_argument) {
            }
        cin.clear();
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
        cout << setw(25) << "Saving image" << endl;
        cout << "Enter image name with  any of the following\n"
                "extensions (.jpg, .bmp, .png, .tga):";
        string img_name;
        cin >> img_name;
        if(valid_output(img_name)){
            res_img.saveImage(img_name);
            cout << "Image saved successfully" << endl;
            return;
        }
        else {
            cerr << "Invalid image name" << endl;

            save_img(res_img);
        }
    }

    void program_menu(){
        cout << "Welcome to Photo Editor" << endl;
        cout << "First we need to load an image" << endl;
        cout << "Please make sure image has same directory as project file" << endl;
    }

    void take_operation(){
        cout << "1) Rotate image" << endl;
        cout << "2) Invert image" << endl;
        cout << "3) Flip image" << endl;
        cout << "4) Grayscale image" << endl;
        cout << "5) brightness image" << endl;
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

    Image brightness(Image &image){
        cout << "1)High brightness"
                "2)Low brightness \n";
       int op = take_choice(1,2);
        if (op == 1){
            return high_brightness(image);
        }
        else{
            return low_brightness(image);
        }
    }

    Image do_operation() {
        take_operation();
        int operation = take_choice(1, 5);
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
                return brightness(img);
            }}
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

            else if(choice == 1){
                string img_name = load_img();

                while(true){
                    Image res_img = do_operation();
                    save_img(res_img);
                    cout << "1) Apply new filter on loaded image: " << img_name << endl <<
                         "2) Back to main menu\n";
                    int s_choice = take_choice(1,2);

                    if(s_choice== 1){
                        continue;
                    }
                    else if(s_choice==2){
                        break ;
                    }
                }
            }
        }}
};


int main() {
    FrontEnd Photo_Editor;
    Photo_Editor.run();
    return 0;
}
