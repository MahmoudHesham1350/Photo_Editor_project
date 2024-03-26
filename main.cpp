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


};

class FrontEnd: public EditImage {
private:
    Image img;

    void load_img() {
        cout << "Enter image name with  any of the following\n"
                "extensions (.jpg, .bmp, .png, .tga):";

        string img_name;
        cin >> img_name;
        img.loadNewImage(img_name);
        cout << "Image loaded successfully" << endl;
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

    Image do_operation() {
        take_operation();
        int operation = take_choice(1, 3);
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

        }}

public:

    void run() {
        program_menu();
        load_img();
        Image res_img = do_operation();
        save_img(res_img);
    }


};


int main() {
    FrontEnd front;
    front.run();

    return 0;
}
