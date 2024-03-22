#include "Image_Class.h"
using namespace std;

class EditImage: private Image {

private:


public:

    void invert_img(Image &main_img) {
        Image res_img(main_img.width, main_img.height);

        for (int wedith = 0; wedith < main_img.width; wedith++){
            for (int height = 0; height < main_img.height; height++) {
                for (int color = 0; color < 3; color++){
                    main_img(wedith, height, color) = 255 - main_img(wedith, height, color);
                }}}
    }


};



int main() {
    EditImage Editor;
    Image img("arrow.jpg");

    Editor.invert_img(img);
    img.saveImage("invert.jpg");

    return 0;
}
