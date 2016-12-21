#include "image_process.h"

using namespace cv;
using namespace std;



Mat org;

//int main()
//{
//    namedWindow("img");
//    setMouseCallback("img", on_mouse_click, 0);
////     get bgr of images
//    org = imread("/home/dell/datasets/ISPRS_semantic_labeling_Vaihingen/gts_for_participants/top_mosaic_09cm_area11.tif");
//    imshow("img", org);
//    cvWaitKey(0);

//}



void on_mouse_click(int event, int x, int y, int flags, void* ustc)
{
    static Point cur_pt(-1, -1);
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        cur_pt = Point(x, y);
        cout << x << "\t" << y << endl;
        cout << int(org.at<Vec3b>(cur_pt)[0]) << "\t" << int(org.at<Vec3b>(cur_pt)[1]) << "\t" << int(org.at<Vec3b>(cur_pt)[2])  << endl;
    }
}
