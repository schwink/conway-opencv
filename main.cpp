
#include <iostream>
#include <sstream>
#include <string>

#include <opencv2/opencv.hpp>

constexpr uint WIDTH = 8;
constexpr uint HEIGHT = 8;

int main() {
  cv::Mat mat = cv::Mat::zeros(HEIGHT, WIDTH, CV_8U);

  // Make a glider
  //mat.at(y, x) = 1;
  mat.at<uchar>(1, 2) = 1;
  mat.at<uchar>(2, 3) = 1;
  mat.at<uchar>(3, 1) = 1;
  mat.at<uchar>(3, 2) = 1;
  mat.at<uchar>(3, 3) = 1;

  //cv::imshow("Generation 0", mat);
  //cv::waitKey();

  std::cout << "Generation 0" << std::endl;
  std::cout << mat << std::endl;

  for (int i = 1; i < 5; i++) {
    cv::Mat previous = mat;

    uint8_t filter[3][3] = {
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1},
    };
    cv::Mat sum;
    cv::filter2D(
		 previous,
		 sum,
		 -1,
		 cv::Mat(3, 3, CV_8U, &filter),
		 cv::Point(-1, -1),
		 0,
		 cv::BORDER_CONSTANT);

    // std::cout << "Generation " << i << " sum" << std::endl;
    // std::cout << sum << std::endl;

    // If 2 or 3 live neighbors, stay alive
    cv::Mat stay_alive;
    // If > 3, set to 0
    cv::threshold(sum, stay_alive, 3, 0, cv::THRESH_TOZERO_INV);
    // If > 1, set to 1
    cv::threshold(stay_alive, stay_alive, 1, 1, cv::THRESH_BINARY);
    // std::cout << "Generation " << i << " cells to stay alive" << std::endl;
    // std::cout << stay_alive << std::endl;
    // std::cout << (previous & stay_alive) << std::endl;

    // If 3 live neighbors, come alive
    cv::Mat become_alive;
    // If > 3, set to 0
    cv::threshold(sum, become_alive, 3, 0, cv::THRESH_TOZERO_INV);
    // If > 2, set to 1
    cv::threshold(become_alive, become_alive, 2, 1, cv::THRESH_BINARY);
    // std::cout << "Generation " << i << " cells to come alive" << std::endl;
    // std::cout << become_alive << std::endl;
    // std::cout << ((become_alive ^ previous) & become_alive) << std::endl;

    mat = (previous & stay_alive) | ((become_alive ^ previous) & become_alive);

    //std::ostringstream label;
    //label << "Generation " << i;
    //cv::imshow(label.str(), mat);
    //cv::waitKey();

    std::cout << "Generation " << i << std::endl;
    std::cout << mat << std::endl;
  }

  return 0;
}
