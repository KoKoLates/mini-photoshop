#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void BoxFilter(const Mat &src, Mat &dst, int ksize)
{
    //only process single or three channels' images
    CV_Assert(src.channels() == 1 || src.channels() == 3);
  
    //construct the kernal
    double *matrix = new double [ksize];
    double sum = 0;
    int origin = ksize/2;
    for(int i = 0; i < ksize; i++)
    {
        double g = 1.0;
        sum += g;
        matrix[i] = g;
    }
    for(int i = 0; i < ksize; i++) matrix[i] /= sum;
  
    //preparation
    int border = ksize/2;
    copyMakeBorder(src, dst, border, border, border, border, BORDER_CONSTANT);
    int channels = dst.channels, rows = dst.rows - border, cols = dst.cols - border;
    
    //horizontal
    for(int i = border; i < rows; i++)
    {
        for(int j = border; j < cols; j++)
        {
            double sum[3] = 0;
            for(int k = -border; k <= border; k++)
            {
                if(channels == 1) sum[0] += matrix[border + k]*dst.at<uchar>(i, j + k);
                else
                {
                    Vec3b bgr = dst.at<Vec3b>(i, j + k);
                    sum[0] += matrix[border + k]*bgr[0];
                    sum[1] += matrix[border + k]*bgr[1];
                    sum[2] += matrix[border + k]*bgr[2];
                }
            }
          
            for(int k = 0; k < channels; k++)
            {
                if(sum[k] < 0) sum[k] = 0;
                else if(sum[k] > 255) sum[k] = 255;
            }
          
            if(channels == 1) dst.at<Vec3b>(i, j) = static_cast<uchar>(sum[0]);
            else
            {
                Vec3b bgr = {static_cast<uchar>(sum[0]), static_cast<uchar>(sum[1]), static_cast<uchar>(sum[2])};
                dst.at<Vec3b>(i, j) = bgr;
            }
        }
    }
  
    //vertical
    for(int i = border; i < rows; i++)
    {
        for(int j = border; j < cols; j++)
        {
            double sum[3] = 0;
            for(int k = -border; k <= border; k++)
            {
                if(channels == 1) sum[0] += matrix[border + k]*dst.at<uchar>(i + k, j);
                else
                {
                    Vec3b bgr = dst.at<Vec3b>(i + k, j);
                    sum[0] += matrix[border + k]*bgr[0];
                    sum[1] += matrix[border + k]*bgr[1];
                    sum[2] += matrix[border + k]*bgr[2];
                }
            }
          
            for(int k = 0; k < channels; k++)
            {
                if(sum[k] < 0) sum[k] = 0;
                else if(sum[k] > 255) sum[k] = 255;
            }
          
            if(channels == 1) dst.at<Vec3b>(i, j) = static_cast<uchar>(sum[0]);
            else
            {
                Vec3b bgr = {static_cast<uchar>(sum[0]), static_cast<uchar>(sum[1]), static_cast<uchar>(sum[2])};
                dst.at<Vec3b>(i, j) = bgr;
            }
        }
    }
    delete [] matrix;
}

int main(void)
{
    Mat src = imread("filePath");
    Mat dst(src.rows, src. cols, CV_8UC3);
    BoxFilter(src, dst, 5);
    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
  
    retrun 0;  
}
