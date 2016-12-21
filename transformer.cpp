#include "image_process.h"

using namespace std;
using namespace cv;

Mat transform(string filename)
{
    Mat img = imread(filename);
    Mat img_copy(img.size(), CV_8U, Scalar(0));
    for (int row = 0; row < img.rows; ++row)
    {
        for (int col = 0; col < img.cols; ++col)
        {
            if (img.at<Vec3b>(row, col) == Vec3b(255, 0, 0))
                *(img_copy.data + img_copy.step[0] * row + img_copy.step[1] * col) = 0;
            else if(img.at<Vec3b>(row, col) == Vec3b(0, 255, 0))
                *(img_copy.data + img_copy.step[0] * row + img_copy.step[1] * col) = 1;
            else if(img.at<Vec3b>(row, col) == Vec3b(0, 0, 255))
                *(img_copy.data + img_copy.step[0] * row + img_copy.step[1] * col) = 2;
            else if(img.at<Vec3b>(row, col) == Vec3b(255, 255, 0))
                *(img_copy.data + img_copy.step[0] * row + img_copy.step[1] * col) = 3;
            else if(img.at<Vec3b>(row, col) == Vec3b(0, 255, 255))
                *(img_copy.data + img_copy.step[0] * row + img_copy.step[1] * col) = 4;
            else if(img.at<Vec3b>(row, col) == Vec3b(255, 255, 255))
                *(img_copy.data + img_copy.step[0] * row + img_copy.step[1] * col) = 5;

        }
    }
    return img_copy;

}
