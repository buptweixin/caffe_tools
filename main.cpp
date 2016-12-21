#include "image_process.h"

using namespace std;
using namespace cv;

bool is_first = true;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ifstream infile(argv[1], ios::in);
    string line;


    while(getline(infile, line))
    {
        istringstream instr(line);
        string train, trainAnnot;
        instr >> train >> trainAnnot;

        string savePath = train.substr(0, train.substr(0, train.find_last_of("/")).find_last_of("/") + 1);
        cropImage(train, trainAnnot, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), savePath);
    }


    return a.exec();
}

void cropImage(string train, string trainannot, int num, int dst_w, int dst_h, string savePath)
{
    int i = 0;
    Mat trainImg = imread(train), trainannotImg = transform(trainannot);
    if (trainImg.size() != trainannotImg.size())
        exit(-1);
    Size imgSize = trainImg.size();


    // set ROI
    Rect rect(0, 0, dst_w, dst_h);

    Mat img2save(Size(dst_w, dst_h), CV_8UC3);
    Mat img2saveAnnot(Size(dst_w, dst_h), CV_8UC3);

    while (i < num)
    {
        string filename = train.substr(train.find_last_of("/") + 1, train.size());
        string subfix = filename.substr(filename.find_last_of("."));
        int x = randint(0, imgSize.width - dst_w);
        int y = randint(0, imgSize.height - dst_h);

        rect.x = x;
        rect.y = y;
        img2save.create(Size(dst_w, dst_h), CV_8UC3);
        img2saveAnnot.create(Size(dst_w, dst_h), CV_8UC3);
        trainannotImg(rect).copyTo(img2saveAnnot);
        trainImg(rect).copyTo(img2save);

        // flip cropped image
        if (randint(0, 2) == 1)
        {
            int flipCode = randint(0, 3) - 1;
            flip(img2saveAnnot, img2saveAnnot, flipCode);
            flip(img2save, img2save, flipCode);
        }
//        if (randint(0, 2) == 1)
//        {
//            transpose(img2saveAnnot, img2saveAnnot);
//            transpose(img2save, img2save);
//        }
        string dstfile = filename.substr(filename.find_last_of("/") + 1, filename.find_last_of(".")) + (i < 10 ? "0" : "") + to_string(i) + subfix;
        imwrite(savePath + "train_cropped/" + dstfile, img2save);
        imwrite(savePath + "trainannot_cropped/" + dstfile, img2saveAnnot);
        ++i;
    }

}

int randint(int a, int b)
{
    if (is_first)
    {
        srand((unsigned)time(0));
        is_first = false;
    }
    return (rand() % (b - a)) + a;
}

