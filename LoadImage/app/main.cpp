#include <opencv2/opencv.hpp>
#include <iostream>

auto try_open(const cv::String &path, int flags) -> cv::Mat;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "usage LoadImage.out <ImagePath>\n";
        return EXIT_FAILURE;
    }
    cv::Mat img_grey = try_open(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat img_color = try_open(argv[1], cv::IMREAD_COLOR);
    cv::imshow("greyscale image", img_grey);
    cv::imshow("color image", img_color);
    cv::waitKey(0);
    cv::destroyAllWindows();
    cv::imwrite("greyscale.jpg", img_grey);
    cv::imwrite("color.jpg", img_color);
}

auto try_open(const cv::String &path, int flags) -> cv::Mat
{
    auto mat = cv::imread(path, flags);
    if (!mat.data)
    {
        std::cerr << "failed to load image " << path << "\n";
    }
    return mat;
}