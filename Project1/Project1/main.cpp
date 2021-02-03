
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
using namespace std;



Mat src_gray, detected_edges, half_img;

//캐니의 쓰레쉬홀드
int canny_lowThreshold = 42;
int canny_highThreshold = 68;
int H_threshold = 10;


static void CannyThreshold(int, void*)
{
    vector<Vec2f> lines;

    Canny(half_img, detected_edges, canny_lowThreshold, canny_highThreshold, 3);
    HoughLines(detected_edges, lines, CV_PI / 180, H_threshold,0,0);
    //라인 긋는거 찾아봐야함
    /*
    while (int i=lines.size())
    {
        line(src_gray, lines[i][0], lines[i][1], COLOR_BLUE, 2);
        i--;
    }
    */

    imshow("Canny Edge", detected_edges);

}


int main(int argc, char** argv)
{

    src_gray = imread("capture3.jpg", IMREAD_GRAYSCALE); // Load an image
    if (src_gray.empty())
    {
        std::cout << "파일을 찾을 수가 없다.\n" << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }

    //그레이스케일 된 화면 먼저 출력
    namedWindow("Canny Edge", WINDOW_AUTOSIZE);
    namedWindow("Canny Edge", WINDOW_AUTOSIZE);
    imshow("grayed", src_gray);

    //반으로 갈라서 아래쪽 ROI 설정
    half_img = src_gray(Rect(0,src_gray.rows/2,src_gray.cols,src_gray.rows/2));

    
    createTrackbar("Min Threshold:", "Canny Edge", &canny_lowThreshold, 1000, CannyThreshold);
    createTrackbar("Max Threshold:", "Canny Edge", &canny_highThreshold, 1000, CannyThreshold);
    createTrackbar("H_threshold:", "Canny Edge", &H_threshold, 1000, CannyThreshold);
    CannyThreshold(0, 0);


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