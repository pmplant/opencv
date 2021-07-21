#include <opencv2/opencv.hpp>
#include <iostream>

const auto mp4 = cv::VideoWriter::fourcc('m', 'p', '4', 'v');

auto main() -> int
{
    auto vid = cv::VideoCapture(cv::CAP_ANY);
    if (!vid.isOpened())
    {
        std::cerr << "failed to open video stream" << std::endl;
        return EXIT_FAILURE;
    }
    auto fps = vid.get(cv::CAP_PROP_FPS);
    std::cout << "capturing at " << fps << " fps" << std::endl;
    int ms_per_frame = 1000 / fps;
    auto frame_h = vid.get(cv::CAP_PROP_FRAME_HEIGHT);
    auto frame_w = vid.get(cv::CAP_PROP_FRAME_WIDTH);
    auto frame_size = cv::Size(frame_w, frame_h);
    auto fps_out = 10.0;
    auto recorder = cv::VideoWriter("recording.mp4", mp4, fps_out, frame_size);
    auto frame = cv::Mat();
    while (vid.isOpened())
    {
        if (!vid.read(frame))
        {
            std::cerr << "failed to read next frame" << std::endl;
            return EXIT_FAILURE;
        }
        cv::imshow("LIVE!", frame);
        recorder.write(frame);
        if (cv::waitKey(ms_per_frame) == 'q')
        {
            std::cout << "quitting video" << std::endl;
            break;
        }
    }
    cv::destroyAllWindows();
    recorder.release();
    vid.release();
    return EXIT_SUCCESS;
}