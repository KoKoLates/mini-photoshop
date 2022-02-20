# Edge Detection

By realizing the calculus of the derivatives in an image, ones could easily notice that in an edge, the pixel intensity changes in a notorious way. A good way to express changes is by using derivatives. A high change in gradient indicates a major change in the image. Assume we have a 1D image. An edge is shown by the jump in intensity in the plot, The edge jump can be seen more easily if we take the first derivative (actually, here appears as a maximum value). <br/><br/>
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/origins.PNG)
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/derivative.PNG) <br/>

So far, from the explanation above, we can deduce that a method to detect edges or sharpening the object borders in an image can be performed by locating pixel locations where the gradient is higher than its neighbors (or to generalize, higher than a threshold).

* Main Include
```cpp
#include <opencv2/imgproc/imgproc.hpp>
```

## Sobel Operator
The Sobel Operator is a discrete differentiation operator. It computes an approximation of the gradient of an image intensity function. Besides, the Sobel Operator combines the Gaussian smoothing and the application of first derivation. <br/><br/>

Assuming it is the grayscale value function of the two-dimensional image, the grayscale change gradient is a the vector of slope change (slope), then the gradient of the image is defined as : *G<sub>x</sub>* Gradient value in the horizontal direction and *G<sub>y</sub>* Gradient value in the vertical direction. <br/>

![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/x%20gradient.PNG)
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/y%20gradient.PNG) <br/>
  
At each point of the image we calculate an approximation of the gradient in that point by combining both results above.
  
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/sobel%20equation.PNG)
```cpp
cv::Sobel(InputArray src, OutputArray dst, int ddeth, int dx, int dy, int ksize = 3, double scale = 1, double delta = 0, int borderType = BORDER_DEFAULT)
```
The Sobel operators combine Gaussian smoothing and differentiation, so the result is more or less resistant to the noise. Most often, the function is called with (xorder = 1, yorder = 0, ksize = 3) or (xorder = 0, yorder = 1, ksize = 3) to calculate the first x or y image derivative.
```
src        | input image.
dst        | output image of the same size and the same number of channels as src.
ddepth     | output image depth; in the case of 8-bit input images it will result in truncated derivatives.
dx         | order of the derivative x.
dy         | order of the derivative y.
ksize      | size of the extended Sobel kernel; it must be odd number.
scale      | optional scale factor for the computed derivative values; by default, no scaling is applied.
delta      | optional delta value that is added to the results prior to storing them in dst.
borderType | pixel extrapolation method.
```

* **Prewitt's Operator** <br/>
Prewitt operator is similar to the Sobel operator and is used for detecting vertical and horizontal edges in images. However, unlike the Sobel, Prewitt operator doesn't place any emphasis on the pixels that are closer to the center of the mask. <br/>
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/prewitt%20x.PNG)
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/prewitt%20y.PNG)
  
## Scharr Operator
When the size of the kernel is `3`, the Sobel kernel shown above may produce noticeable inaccuracies (after all, Sobel is only an approximation of the derivative). OpenCV addresses this inaccuracy for kernels of size 3 by using the `Scharr()` function. The weight of adjacent pixels is larger, so the accuracy is higher than the standard Sobel function and it could calculate more detailing gradient changes.
```cpp
cv::Scharr(InputArray src, OutputArray dst, int ddepth, int dx, int dy, double scale = 1, double delta = 0, int borderType = BORDER_DEFAULT)
```
The function computes the first x or y spatial image derivative using the Scharr operator. It's give more accurate results than the 3×3 Sobel operation, and is equivalent to :
```cpp
cv::Sobel(src, dst, ddepth, dx, dy, CV_SCHARR, scale, delta, borderType)
```
*  parameter
```
src        | input image.
dst        | output image of the same size and the same number of channels as src.
ddepth     | output image depth, see combinations
dx         | order of the derivative x.
dy         | order of the derivative y.
scale      | optional scale factor for the computed derivative values; by default, no scaling is applied.
delta      | optional delta value that is added to the results prior to storing them in dst.
borderType | pixel extrapolation method.
```
  
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/scharr%20x.PNG)
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/scharr%20y.PNG)

## Laplacin Operator
In the edge area, the pixel intensity shows a jump or a high variation. Getting the first derivative of the intensity, we observed that an edge is characterized by a maximum. And if getting in second derivative, it would observe that it's zero. So, we can also use this criterion to detect edges in an image. However, note that zeros will not only appear in edges, it can also appear in other meaningless locations; that is, the Laplacian operator is very sensitive to noise. To correct it, the image often Gaussian smoothed before apply Laplacian filter.

(they can actually appear in other meaningless locations); this can be solved by applying filtering where needed. <br/>

![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/second%20derivative.PNG) <br/>

From the explanation above, it could deduce that the second derivative cne use to detect edeges. And because the image is 2D, it would need to take the derivative in both dimensions; therefore, the Laplacian operator comes handys. <br/>

![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/laplacian.PNG)
```cpp
cv::Laplacian(InputArray src, OutputArray dst, int ddepth, int ksize = 1, double scale = 1, double delta = 0, int borderType = BORDER_DEFAULT)
```
* parameter
```
src        | Source image.
dst        | Destination image of the same size and the same number of channels as src .
ddepth     | Desired depth of the destination image.
ksize      | Aperture size used to compute the second-derivative filters. The size must be positive and odd.
scale      | Optional scale factor for the computed Laplacian values. By default, no scaling is applied.
delta      | Optional delta value that is added to the results prior to storing them in dst.
borderType | Pixel extrapolation method.
```
When `ksize == 1`, the Laplacian is computed by filtering the image with the following 3×3 aperture : <br/>
![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/laplacian%20ksize%201.PNG)

## Canny Operator
The Canny algorithm aims to satisfy three main criteria : **Low error rate** meaning a good detection of only existent edges; **Good localization** means the distance between edge pixels detected and real edge pixels have to be minimized; **Minimal response** said that only one detector response per edge. <br/><br/>

For Canny edges detector, the first step is to filter out any noise, the Gaussian filter is used for this purpose and the kernal of `size = 5` might be used for general. Then, find the intensity gradient of the image by computing Sobel or Prewitt operator. Get the gradient strength and direction, the direction is rounded to one of four possible angle, namely 0, 45, 90 or 135 : <br/>

![image](https://github.com/KoKoLates/Photoshop-Demo/blob/main/Algorithm/Sharpening/images/canny%20equation.PNG) <br/>

Next, ***Non-maximum*** suppression is applied. This removes pixels that are not considered to be part of an edge. Hence, only thin lines, candidate edges, will be remained. The final step of Canny edges detector is **Hysteresis**. Canny does that with two threshold : upper and lower : 
1. If a pixel gradient is higher than the upper threshold, the pixel is accepted as an edge.
2. If a pixel gradinet is below the lower threshold, then rejected.
3. If the pixel gradient is between the two thresholds, then it will be accepted only if it is connected to a pixel that is above the upper threshold.
Canny operator's recommended ***upper-lower*** ratio between `2:1` and `3:1`.
```cpp
cv::Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize = 3, bool L2gradient = false)
```
* parameter
```
image        | 8-bit input image.
edges        | output edge map; single channels 8-bit image, which has the same size as image .
threshold1   | first threshold for the hysteresis procedure.
threshold2   | second threshold for the hysteresis procedure.
apertureSize |aperture size for the Sobel operator.
L2gradient   | a flag, indicating whether a more accurate L2 norm should be used to calculate the image gradient magnitude (L2gradient = true),
             | or whether the default L1 norm is enough (L2gradient = false).
```

