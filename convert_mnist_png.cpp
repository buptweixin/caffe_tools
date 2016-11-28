#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<string>
#include<fstream>
#include<stdint.h>
#include<vector>
#include<sstream>


using namespace cv;
using namespace std;


uint32_t swap_endian(uint32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

void read_mnist(string image_filename, string label_filename, vector<int>& vlabel, vector<Mat>& vec)
{
    // open file
    std::ifstream image_file(image_filename.c_str(), std::ios::in | std::ios::binary);
    std::ifstream label_file(label_filename.c_str(), std::ios::in | std::ios::binary);
    if(!image_file)
    {
        cerr << "Unable open file ";
        return;
    }

    if(!label_file)
    {
        cerr << "Unable open file " << label_filename;
        return;
    }
    // Reading the magic and meta data
    uint32_t magic;
    uint32_t num_items;
    uint32_t num_labels;
    uint32_t rows;
    uint32_t columns;

    image_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if (magic != 2051)
    {
        cerr << "Incorrect iamge file magic";
        return;
    }
    label_file.read(reinterpret_cast<char*>(&magic), 4);
    magic = swap_endian(magic);
    if (magic != 2049)
    {
        cerr << "Incorrect iamge file magic";
        return;
    }
    image_file.read(reinterpret_cast<char*>(&num_items), 4);
    num_items = swap_endian(num_items);
    label_file.read(reinterpret_cast<char*>(&num_labels), 4);
    num_labels = swap_endian(num_labels);
    if (num_items != num_labels)
    {
        cerr << "The number of images are not equal to labels";
    }
    image_file.read(reinterpret_cast<char*>(&rows), 4);
    rows = swap_endian(rows);
    image_file.read(reinterpret_cast<char*>(&columns), 4);
    columns = swap_endian(columns);
    for (int i = 0; i< num_items; ++i)
    {
        Mat tp = Mat::zeros(rows, columns, CV_8UC1);
        for ( int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c)
            {
                unsigned char tmp = 0;
                image_file.read((char*)&tmp, sizeof(tmp));
                tp.at<uchar>(r, c) = (int)tmp;
            }
        vec.push_back(tp);
    }
    for(int i = 0; i< num_labels; ++i)
    {
        unsigned char tmp = 0;
        label_file.read((char*)&tmp, sizeof(tmp));
        vlabel.push_back((int)tmp);
    }
}

void save_as_png(vector<Mat>& vec, string prefix, string phase)
{
    string path = prefix + "/images/" + phase;
    for (int i = 0; i < vec.size(); ++i)
    {
        ostringstream oss;
        oss << path + "/"<< i << ".png";
        string filename = oss.str();
        cout << filename;
        imwrite(filename, vec[i]);
    }
}

void save_labels(vector<int>& labels, string prefix, string phase)
{
    string path = prefix + "/labels/"  + "mnist_" + phase +".txt";
    ofstream out(path.c_str());
    if (!out)
    {
        cerr << "Open " << path << "failed." << endl;
    }
    for (vector<int>::iterator iter = labels.begin(); iter != labels.end(); ++iter)
    {
        out << *iter << endl;
    }
    out.close();
}

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        cerr << "Use " << argv[0] << ":" << endl;
        cout << "USE_MNIST /path/to/mnist_data /path/to/save" << endl;
        return -1;
    }
    vector<Mat> mVec;
    vector<int> labels;
    string data_dir(argv[1]);
    string prefix(argv[2]);
    read_mnist(data_dir + "/train-images-idx3-ubyte", data_dir + "/train-labels-idx1-ubyte", labels, mVec);
    save_as_png(mVec, prefix, "train");
    save_labels(labels, prefix, "train");
    vector<Mat> mVec2;
    vector<int> labels2;
    read_mnist(data_dir + "/t10k-images-idx3-ubyte", data_dir + "/t10k-labels-idx1-ubyte", labels2, mVec2);
    cout << "data dir:" << data_dir;
    save_as_png(mVec2, prefix, "test");
    save_labels(labels2, prefix, "test");
    return 0;
}
