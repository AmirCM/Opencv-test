
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    //std::cout << "Hello World!\n";
    string  path = "SamplePhotos\\", type = ".bmp" , file_name = "Bitmap";
    Mat template_img = imread("template.bmp");
    Mat gray_template_img;

    cvtColor(template_img, gray_template_img, COLOR_BGR2GRAY);

    namedWindow("img", WINDOW_AUTOSIZE);
    for (int i = 9; i < 10; i++) {
        Mat img = imread(path + file_name + to_string(i) + type);
        
        if (!img.data) {
            std::cout << "Img not loaded!!!";
            continue;
        }

        Mat gray_img;
        Mat laplacian;
        cvtColor(img, gray_img, COLOR_BGR2GRAY);
        Laplacian(gray_img, laplacian, CV_8U);
        
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(laplacian, contours, hierarchy, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++) {
            Rect box = boundingRect(contours[i]);
            
            if (box.area() > ((long int)img.cols * (long int)img.rows) * 0.1) {
                cout << "(" << box.height << " , " << box.width << ") --> (" << box.x << " , " << box.y << ")" << endl;
                rectangle(img, box, Scalar(0, 255, 0), 10);
            }
        }
        resize(img, img, Size(), 0.5, 0.5, INTER_NEAREST);
        
        imshow("img", img);
        waitKey(0);
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
