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
};



int main() {
    EditImage Edit;
    Image img("arrow.jpg");
    Image res = Edit.rotate_img(img, 270);


    res.saveImage("result.jpg");

    return 0;
}
