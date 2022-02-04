# Smoothing Images
Smoothing, also called blurring, is a simple and frequently used image processing operation. There are many reasons for smoothing a images, and the mostly and mainly one is smoothing in order to reduce noise. To perform a smoothing operation we will apply a filter to our image. The most common type of filters are linear, in which an output pixel's value is determined as a weighted sum of input pixel values : <br/><br/>
![image](https://github.com/KoKoLates/OpenCV/blob/main/Smoothing%20Images/images/filter%20equation.PNG) <br/>

`h` is called the kernel, which is nothing more than the coefficients of the filter. It helps to visualize a filter as a window of coefficients sliding across the image.
* Main Include
```cpp
#include <opencv2/imgproc/imgproc.hpp>
```


## Normalized Box Filter
![image](https://github.com/KoKoLates/OpenCV/blob/main/Smoothing%20Images/images/Box%20Filter.PNG) <br/>
This filter is the simplest of all. Each output pixel is the mean of its kernel neighbors ( all of them contribute with equal weights ). The basic function `blur()` is based on the Normalized Box Filter : 
```cpp
cv::blur( InputArray src, OutputArray dst, Size ksize, Point archor = Point(-1,-1), int borderType = BORDER_DFFAULT)
```
* Parameter :
```
src        | input image; it can have any number of channels, which are processed independently, 
           | but the depth should be CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
dst        | output image of the same size and type as src.
ksize      | blurring kernel size.
anchor     | anchor point; default value Point(-1,-1) means that the anchor is at the kernel center.
borderType | border mode used to extrapolate pixels outside of the image.
```
The main disadvantage of the the normalized box filter is that it blurs the image while reducing noise, especially at the edges and details. And once you larger the kernal size, the more blurring while the denoising ability is enhanced.
* [Box Filter Algorithms](https://github.com/KoKoLates/OpenCV/blob/main/Smoothing%20Images/Box%20Filter.cpp)

## Gaussian Filter 
Probably the most useful filter (although not the fastest). Gaussian filtering is done by convolving each point in the input array with a Gaussian kernel and then summing them all to produce the output array. <br/><br/>
![image](https://github.com/KoKoLates/OpenCV/blob/main/Smoothing%20Images/images/Gaussian%202D.PNG) <br/>
where `μ` is the mean (the peak) and `σ2` represents the variance (per each of the variables x and y). You can notice that the pixel located in the middle would have the biggest weight. The weight of its neighbors decreases as the spatial distance between them and the center pixel increases.
```cpp
cv::Gaussian(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY = 0, int borderType = BORDER_DEFFAULT)
```
* Parameter :
```
src        | input image.
dst        | output image of the same size and type as src.
ksize      | Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd.
sigmaX     | Gaussian kernel standard deviation in X direction.
sigmaY     | Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be equal to sigmaX,
           | if both sigmas are zeros, they are computed from ksize.width and ksize.height, respectively.
borderType | pixel extrapolation method.
```
* Sigma : <br/>
The most important parameter of the generation of the Gaussian template is the standard deviation `σ`, the standard deviation represents the degree of dispersion of the data. If `σ` is small, the center coefficient of the generated template is large, and the surrounding coefficients are small, so the smoothing effect on the image is not obvious; on the contrary, if `σ` is large, the generated template The coefficients of the template are not very different. They are more similar to the mean template, and the smoothing effect on the image is more obvious. <br/><br/>
![image](https://github.com/KoKoLates/OpenCV/blob/main/Smoothing%20Images/images/sigma.PNG)
* [Gaussian Filter Algorithm](https://github.com/KoKoLates/OpenCV/blob/main/Smoothing%20Images/Gaussian%20Filter.cpp)


## Median Filter
The median filter run through each element of the signal (the image) and replace each pixel with the median of its neighboring pixels (located in a square neighborhood around the evaluated pixel). Median filter is a non-linear image processing method, which can take into account the preservation of boundary information while denoising. <br/><br/>
![image](https://github.com/KoKoLates/OpenCV/blob/main/Smoothing%20Images/images/Median%20equation.PNG) <br/>
```cpp
cv::medianBlur(InputArray src, OutputArray dst, int ksize)
```
The function smoothes an image using the median filter with the `ksize × ksize` aperture. Each channel of a multi-channel image is processed independently. Besides, the median filter uses BORDER_REPLICATE internally to cope with border pixels.
```
src   | input 1, 3 or 4-channel image; when ksize is 3 or 5, the image depth should be CV_8U, CV_16U, or CV_32F,
      | for larger aperture sizes, it can only be CV_8U.
dst   | destination array of the same size and type as src.
ksize | aperture linear size; it must be odd and greater than 1. 
```
The effect of the median filter is greatly affected by the size of the filter window, and there is a contradiction between eliminating noise and protecting the details of the image: a smaller filter window can protect some details in the image well, but it will filter the noise; on the contrary, a larger window size has a better noise filtering effect, but it will cause a certain blur to the image. According to the principle of the median filter, if the number of noise points in the filter window is greater than the number of pixels in the entire window, the median filter cannot filter the noise well.
* **[Adaptive Median Filter](https://github.com/KoKoLates/OpenCV/blob/main/Smoothing%20Images/Adaptive%20Median%20Filter.cpp)** <br/>

The Median Filter works well while the density of the noise is not very large (the probability of occurernce of noise is less than 0.2). But when the probability get higher, the effect of conventional median filter is not very well. One option is to increase the window size of the filter. Although the problem above is solved, it would cause a larger blur to the image. <br/><br/>

At this time, it is necessary to seek a alternative. That is the `Adaptive Median Filter`. In the filtering process, the adaptive median filter will change the size of the filter window according to the preset conditions, and at the same time judge whether the current pixel is noise or not according to certain conditions, and if it is, use the neighborhood median replaces; if not, then do not change it. <br/><br/>

The adaptive median filter has three main purposes : **Filter out the impulse noise**, **Smoothing other non-impulsive noise** and **Protect the details** of the image as much as possible, and avoid the thinning or roughening of the edges of the image.


## Bilateral Filter
Sometimes the filters do not only dissolve the noise, but also smooth away the edges. To avoid this, ones could use the Bilateral filter. In an analogous way as the Gaussian filter, the bilateral filter also considers the neighboring pixels with weights assigned to each of them. These weights have two components, the first of which is the same weighting used by the Gaussian filter. The second component takes into account the difference in intensity between the neighboring pixels and the evaluated one.
```cpp
cv::bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, int borderType = BORDER_DEFAULT)
```
bilateralFilter can reduce unwanted noise very well while keeping edges fairly sharp. However, it is very slow compared to most filters.
```
src        | Source 8-bit or floating-point, 1-channel or 3-channel image.
dst        | Destination image of the same size and type as src .
d          | Diameter of each pixel neighborhood that used during filtering. If it's non-positive, it is computed from sigmaSpace.
sigmaColor | Filter sigma in the color space. larger value means farther colors in the pixel neighborhood will be mixed together.
sigmaSpace | Filter sigma in the coordinate space.
           | A larger value means that farther pixels will influence each other as long as their colors are close enough.
           | When d>0, it specifies the neighborhood size regardless of sigmaSpace. Otherwise, d is proportional to sigmaSpace.
borderType | border mode used to extrapolate pixels outside of the image.
```
For simplicity, you can set the 2 sigma values to be the same. If they are small than 10, the filter will not have much effect, whereas if they are larger than 150, it will have a very (or too) strong effect and make the image look cartoonish. Besides, Large filters (d > 5) are very slow, so it is recommended to use d = 5 for real-time applications, and perhaps d = 9 for offline applications that need heavy noise filtering.



