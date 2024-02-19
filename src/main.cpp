#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

void InvertColors(
    cv::Mat& image,
    size_t start, 
    size_t end
) {
    for (size_t i = start; i != end; ++i) 
    {
        for (size_t j = 0; j != image.cols; ++j) 
        {
            // pointer to current pixel
            uchar* pixel = image.ptr<uchar>(i, j);

            // invert each channel
            pixel[0] = 255 - pixel[0];
            pixel[1] = 255 - pixel[1];
            pixel[2] = 255 - pixel[2];
        }
    }
}

int main()
{
    cv::Mat image = cv::imread("F:\\examples\\images\\2.png");
    if (image.empty())
    {
        std::cout << "Couldn't read the image!\n";
        return 1;
    }
    
    // get number of threads from system and reserve vector of them
    size_t n = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(n);

    // give tasks for each thread
    for (size_t i = 0; i != n; ++i)
    {
        size_t start = (image.rows / n) * i;
        size_t end = (i != n - 1) ? start + (image.rows / n) : image.rows;

        threads.push_back(std::thread(InvertColors, image, start, end));
    }

    // wait for all threads is done
    for (auto& thread : threads) 
    {
        thread.join();
    }

    // see inverted image
    cv::imshow("image", image);
    cv::waitKey(0);

    // save image
    if (cv::imwrite("F:\\examples\\inverted\\2_inverted.png", image)) 
    {
        std::cout << "Image has saved!\n";
    }
    else 
    {
        std::cout << "Couldn't save the image!\n";
    }

	return 0;
}
