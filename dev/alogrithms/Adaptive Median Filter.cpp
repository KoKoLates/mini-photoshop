#include <iostream>
#include <algorithms>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

uchar adaptiveProcess(const Mat &src, int row, int col, int kernalSize, int maxSize)
{
    vector<uchar>pixels;
    for(int i = -kernalSize / 2; i <= kernalSize / 2; i++)
    {
        for(int j = -kernalSize / 2; j <= kernalSize / 2; j++)
        {
            pixels.push_back(src.at<uchar>(a + row, b + col);
        }
    }
    sort(pixels.begin(), pixels.end());
    auto min = pixels[0];
    auto max = pixels[kernalSize * kernalSize - 1];
    auto med = pixels[kernalSize * kernalSize / 2];
    auto point = src.at<uchar>(row, col);
    if(med > min && med < max)
    {
        if(point > min && point < max) return point;
        else return med;
    }
    else
    {
        kernalSize += 2;
        if(kernalSize < maxSize) return adaptiveProcess(src, row, kernalSize, maxSize);
        else return med;
    }
}
                             
Mat AdaptiveMedianFilter(Mat src)
{
    Mat dst;
    int minSize = 3, maxSize = 7; //set the max and min size of filter window
    copyMakeBorder(src, dst, maxSize/2, maxSize/2, maxSize/2, maxSize/2, BORDER_REFLECT);
    int rows = dst.rows, cols = dst.cols;
    for(int i = maxSize / 2; i < rows - maxSize/2; i++)
    {
        for(int j = maxSize / 2; j < cols * dst.channels() - maxSize/2; j++)
        {
            dst.at<uchar>(i, j) = adaptiveProcess(dst, i, j, minSize, maxSize); 
        }
    }
    return dst;
}
                             
int main(void)
{
    Mat src = imread("filePath");
    Mat dst = AdaptiveMedianFilter(src);
    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
    return 
}
                            
