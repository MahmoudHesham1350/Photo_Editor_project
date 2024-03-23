#include "Image_Class.h"
using namespace std;

class EditImage: private Image {

private:
    static void copy_img(Image &img_from, Image &img_to) {
        for (int width = 0; width < img_from.width; width++){
            for (int height = 0; height < img_from.height; height++) {
                for (int color = 0; color < 3; color++){
                    img_to(width, height, color) = img_from(width, height, color);
                }}}
    }

public:

    void invert_img(Image &main_img) {
        Image res_img(main_img.width, main_img.height);
        for (int width = 0; width < main_img.width; width++){
            for (int height = 0; height < main_img.height; height++) {
                for (int color = 0; color < 3; color++){
                    main_img(width, height, color) = 255 - main_img(width, height, color);
                }}}
    }

    };



int main() {
    EditImage Edit;
    Image img("arrow.jpg");
    Edit.invert_img(img);

    img.saveImage("result.jpg");

    return 0;
}
