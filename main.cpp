#include "Image_Class.h"
using namespace std;

class EditImage: protected Image {

private:
    static void copy_img(Image &img_from, Image &img_to) {
        for (int width = 0; width < img_from.width; width++){
            for (int height = 0; height < img_from.height; height++) {
                for (int color = 0; color < 3; color++){
                    img_to(width, height, color) = img_from(width, height, color);
                }}}
    }

    Image rotate_img_90(Image &main_img) {
        Image res_img(main_img.height, main_img.width);
        for(int height = 0; height < main_img.height; height++){
            for(int width = 0; width < main_img.width; width++){
                for(int color = 0; color < 3; color++){
                    res_img(height, width, color) = main_img(width, main_img.height - 1 - height, color);
                }}}
        return res_img;
    }

public:

    Image invert_img(Image &main_img) {
        Image res_img(main_img.width, main_img.height);
        for (int width = 0; width < main_img.width; width++){
            for (int height = 0; height < main_img.height; height++) {
                for (int color = 0; color < 3; color++){
                    res_img(width, height, color) = 255 - main_img(width, height, color);
                }}}
        return res_img;
    }


    Image rotate_img(Image &main_img, int rotation = 90) {
        if (rotation == 90){
            return rotate_img_90(main_img);
        }
        Image rotated_img_180 = rotate_img_90(main_img);
        if (rotation == 180){
            return rotate_img_90(rotated_img_180);
        }
        Image rotated_img_270 = rotate_img_90(rotated_img_180);
        if (rotation == 270){
            return rotate_img_90(rotated_img_270);
        }
    }


    void flip_img_horizontally(Image &image) {
        int temp;
        for (int width = 0; width < image.width / 2; width++) { // Iterate only half width
            for (int height = 0; height < image.height; height++) {
                // Swap pixels horizontally
                for(int colour = 0; colour < 3; colour++) {
                    temp = image.getPixel(width, height, colour);
                    image.setPixel(width, height, colour, image.getPixel(image.width - 1 - width, height, colour));
                    image.setPixel(image.width - 1 - width, height, colour, temp);
                }}}}


    void flip_img_vertically(Image &image) {
        int temp;
        for (int height = 0; height < image.height / 2; height++) { // Iterate only half height
            for (int width = 0; width < image.width; width++) {
                // Swap pixels vertically
                for(int colour = 0; colour < 3; colour++) { // Loop through each color channel (assuming RGB)
                    temp = image.getPixel(width, height, colour); // Store the current pixel value in temp
                    image.setPixel(width, height, colour, image.getPixel(width, image.height - 1 - height, colour)); // Replace current pixel with corresponding pixel from the other side
                    image.setPixel(width, image.height - 1 - height, colour, temp); // Replace corresponding pixel from the other side with temp
                }}}}


};


int main() {
    return 0;
}
