#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    cv::VideoCapture vid;
    std::string file_path;
    if (argc < 2)
    {
        file_path = "Webcam";
        vid = cv::VideoCapture(cv::CAP_ANY);
    }
    else
    {
        file_path = argv[1];
        vid = cv::VideoCapture(file_path);
    }
    if (!vid.isOpened())
    {
        std::cerr << "Failed to open video " << file_path << std::endl;
        return EXIT_FAILURE;
    }
    int fps = vid.get(cv::CAP_PROP_FPS);
    std::cout << "FPS " << fps << std::endl;
    int frame_count = vid.get(cv::CAP_PROP_FRAME_COUNT);
    std::cout << "Frame Count " << frame_count << std::endl;

    int delay_per_frame = 1000 / fps;
    auto frame = cv::Mat();
    while (vid.isOpened())
    {
        bool is_success = vid.read(frame);
        if (!is_success)
        {
            std::cerr << "Video source disconnected" << std::endl;
            break;
        }
        cv::imshow(file_path, frame);
        auto key = cv::waitKey(delay_per_frame);
        if (key == 'q')
        {
            std::cout << "Stopping the video" << std::endl;
            break;
        }
    }
    cv::destroyAllWindows();
    vid.release();
    return EXIT_SUCCESS;
}