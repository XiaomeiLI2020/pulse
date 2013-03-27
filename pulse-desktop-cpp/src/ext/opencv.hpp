#ifndef EXT_OPENCV_HPP
#define	EXT_OPENCV_HPP

#include <iostream>
#include <opencv2/core/core.hpp>

using std::cout;
using std::endl;

namespace cv {

const Scalar BLACK    (  0,   0,   0);
const Scalar RED      (255,   0,   0);
const Scalar GREEN    (  0, 255,   0);
const Scalar BLUE     (  0,   0, 255);
const Scalar WHITE    (255, 255, 255);

const Scalar ZERO     (0);

void detrend(InputArray _z, OutputArray _r, int lambda = 10);

void normalization(InputArray _a, OutputArray _b);

void meanFilter(InputArray _a, OutputArray _b, size_t n = 3, Size s = Size(5, 5));

void interpolate(const Rect& a, const Rect& b, Rect& c, double p);

template<typename T>
int countZeros(InputArray _a) {
    CV_DbgAssert(_a.channels() == 1
            && _a.total() == max(_a.size().width, _a.size().height));

    int count = 0;
    if (_a.total() > 0) {
        Mat a = _a.getMat();
        T last = a.at<T>(0);
        for (int i = 1; i < a.total(); i++) {
            T current = a.at<T>(i);
            if ((last < 0 && current >= 0) || (last > 0 && current <= 0)) {
                count++;
            }
            last = current;
        }
    }
    return count;
}

/**
 * Print Mat info such as rows, cols, channels, depth, isContinuous, 
 * and isSubmatrix.
 */
void printMatInfo(const string& name, InputArray _a);

/**
 * Same as printMatInfo plus the actual values of the Mat.
 * @see printMatInfo
 */
template<typename T>
void printMat(const string& name, InputArray _a,
        int rows = -1,
        int cols = -1,
        int channels = -1)
{
    printMatInfo(name, _a);

    Mat a = _a.getMat();
    if (-1 == rows) rows = a.rows;
    if (-1 == cols) cols = a.cols;
    if (-1 == channels) channels = a.channels();

    for (int y = 0; y < rows; y++) {
        cout << "[";
        for (int x = 0; x < cols; x++) {
            T* e = &a.at<T>(y, x);
            cout << "(" << e[0];
            for (int c = 1; c < channels; c++) {
                cout << ", " << e[c];
            }
            cout << ")";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

}

#endif	/* EXT_OPENCV_HPP */

