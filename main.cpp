
#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

constexpr uint WIDTH = 32;
constexpr uint HEIGHT = 32;

int main() {
  cv::Mat mat;
  mat.create(HEIGHT, WIDTH, CV_32F);

  // Make a glider
  //mat.at(y, x) = 1;
  mat.at<float>(1, 2) = 1;
  mat.at<float>(2, 3) = 1;
  mat.at<float>(3, 1) = 1;
  mat.at<float>(3, 2) = 1;
  mat.at<float>(3, 3) = 1;

  cv::imshow("Mat", mat);
  cv::waitKey();

  return 0;
}
