#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <opencv2/core/types_c.h>

#include <cstdio>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;



Mat src_gray;
Mat dst, detected_edges;

int lowThreshold = 17;
int highThreshold = 31;


static void CannyThreshold(int, void*)
{
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, highThreshold, 3);

    imshow("Canny Edge", detected_edges);

}


int main(int argc, char** argv)
{

    src_gray = imread("capture1.jpg", IMREAD_GRAYSCALE); // Load an image
    if (src_gray.empty())
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }


    namedWindow("Canny Edge", WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold:", "Canny Edge", &lowThreshold, 1000, CannyThreshold);
    createTrackbar("Max Threshold:", "Canny Edge", &highThreshold, 1000, CannyThreshold);
    CannyThreshold(0, 0);

    std::vector<Vec2f> lines;
    for (int i = 10; i > 0; i--)
    {
        int threshold = (src_gray.rows + src_gray.cols) * i / 10;
        HoughLines(detected_edges, lines, 1, CV_PI / 180, threshold, 0, 0, 0, CV_PI);
        if (lines.size() > 1)
        {
            for (size_t i = 0; i < lines.size(); i++)
            {
                float rho = lines[i][0];
                float theta = lines[i][1];
                double a = cos(theta), b = sin(theta);
                double x0 = a * rho, y0 = b * rho;
                Point pt1(cvRound(x0 + (src_gray.rows + src_gray.cols) * (-b)),
                    cvRound(y0 + (src_gray.rows + src_gray.cols) * (a)) + src_gray.rows / 2);
                Point pt2(cvRound(x0 - (src_gray.rows + src_gray.cols) * (-b)),
                    cvRound(y0 - (src_gray.rows + src_gray.cols) * (a)) + src_gray.rows / 2);

                cv::line(src_gray, pt1, pt2, cvScalar(0, 0, 255));
            }
            break;
        }
    }

    waitKey(0);
    return 0;
}


/*

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    double alpha, beta;
    Mat src1,src2;


        src1 = imread("capture1.jpg",IMREAD_GRAYSCALE);
        src2 = src1.clone();

        Canny(src2, src2, 50, 150, 3);

        imshow("gray_scaled", src1);
        imshow("canny", src2);


        waitKey(0);

}
*/