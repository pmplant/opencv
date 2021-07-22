#include <opencv2/opencv.hpp>
#include <iostream>

auto readImage(const std::string &path) -> cv::Mat
{
    auto mat = cv::imread(path, cv::IMREAD_ANYCOLOR);
    if (!mat.data)
    {
        auto ss = std::stringstream();
        ss << "failed to load image " << path << std::endl;
        throw std::runtime_error(ss.str());
    }
    return mat;
}

auto matToString(const cv::Mat &mat) -> std::string
{
    auto ss = std::stringstream();
    ss << mat.cols << " " << mat.rows;
    return ss.str();
}

auto main(int argc, char **argv) -> int
{
    if (argc < 2)
    {
        std::cerr << "usage ResizeImage <ImagePath>" << std::endl;
        return EXIT_FAILURE;
    }
    auto file_path = cv::String(argv[1]);
    auto image = readImage(file_path);
    cv::imshow("original", image);
    std::cout << "original " << matToString(image) << std::endl;
    auto new_size = cv::Size(image.cols / 2, image.rows / 2);
    auto resized_image = cv::Mat();
    // cv::resize(image, resized_image, new_size, cv::INTER_LINEAR);
    cv::resize(image, resized_image, cv::Size(), 0.5, 0.5);
    cv::imshow("resized", resized_image);
    std::cout << "resized " << matToString(resized_image) << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
}