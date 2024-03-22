#include "Image_Class.h"
using namespace std;

class EditImage: private Image {

private:

public:
    Image invert_color(Image main_image) {
        Image res_image(main_image.width, main_image.height);
        for (int wedith = 0; wedith < main_image.width; wedith++){
            for (int height = 0; height < main_image.height; height++) {
                for (int color = 0; color < 3; color++){
                 res_image(wedith, height, color) = 255 - main_image(wedith, height, color);
                }}}
        return res_image;
    }


};



int main() {
    EditImage Editor;
    Image img("arrow.jpg");

    Image img_inverted = Editor.invert_color(img);
    img_inverted.saveImage("test.jpg");

    return 0;
}
