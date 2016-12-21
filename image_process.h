#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <sstream>

#include <map>

#include <ctime>
#include <cstdlib>

cv::Mat transform(std::string filename);
void on_mouse_click(int event, int x, int y, int flags, void* ustc);
void cropImage(std::string train, std::string trainannot, int num, int dst_w, int dst_h, std::string savePath);
int randint(int a, int b);
#endif // IMAGE_PROCESS_H
