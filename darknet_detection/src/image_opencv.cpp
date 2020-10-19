#include "image_opencv.h"
#include <iostream>

#ifdef OPENCV
#include "utils.h"

#include <cmath>

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <atomic>

#include <opencv2/core/version.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

// includes for OpenCV >= 3.x
#ifndef CV_VERSION_EPOCH
#include <opencv2/core/types.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#endif

// OpenCV includes for OpenCV 2.x
#ifdef CV_VERSION_EPOCH
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/types_c.h>
#include <opencv2/core/version.hpp>
#endif

//using namespace cv;

using std::cerr;
using std::endl;

#ifdef DEBUG
#define OCV_D "d"
#else
#define OCV_D
#endif//DEBUG


// OpenCV libraries
#ifndef CV_VERSION_EPOCH
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_MAJOR)"" CVAUX_STR(CV_VERSION_MINOR)"" CVAUX_STR(CV_VERSION_REVISION) OCV_D
#ifndef USE_CMAKE_LIBS
#pragma comment(lib, "opencv_world" OPENCV_VERSION ".lib")
#endif    // USE_CMAKE_LIBS
#else   // CV_VERSION_EPOCH
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_EPOCH)"" CVAUX_STR(CV_VERSION_MAJOR)"" CVAUX_STR(CV_VERSION_MINOR) OCV_D
#ifndef USE_CMAKE_LIBS
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif    // USE_CMAKE_LIBS
#endif    // CV_VERSION_EPOCH

#include "http_stream.h"

#ifndef CV_RGB
#define CV_RGB(r, g, b) cvScalar( (b), (g), (r), 0 )
#endif

#ifndef CV_FILLED
#define CV_FILLED cv::FILLED
#endif

#ifndef CV_AA
#define CV_AA cv::LINE_AA
#endif

extern "C" {

    //struct mat_cv : cv::Mat {  };
    //struct cap_cv : cv::VideoCapture { };
    //struct write_cv : cv::VideoWriter {  };

    //struct mat_cv : cv::Mat { int a[0]; };
    //struct cap_cv : cv::VideoCapture { int a[0]; };
    //struct write_cv : cv::VideoWriter { int a[0]; };

// ====================================================================
// cv::Mat
// ====================================================================
    image mat_to_image(cv::Mat mat);
    cv::Mat image_to_mat(image img);
//    image ipl_to_image(mat_cv* src);
//    mat_cv *image_to_ipl(image img);
//    cv::Mat ipl_to_mat(IplImage *ipl);
//    IplImage *mat_to_ipl(cv::Mat mat);


