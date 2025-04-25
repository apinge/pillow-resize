/*
* Copyright 2021 Zuru Tech HK Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* istributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <filesystem>
#include <sstream>

#include <CLI/CLI.hpp>
#include <magic_enum.hpp>

#include <opencv2/opencv.hpp>

#include <PillowResize/PillowResize.hpp>

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    int width = 100;
    int height = 100;
    int new_width = 10;
    int new_height = 10;

    // Construct fake image
    cv::Mat src(height, width, CV_8UC3);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            uchar val = static_cast<uchar>(i + j);
            src.at<cv::Vec3b>(i, j) = cv::Vec3b(val, val, val);
        }
    }
#ifdef PRINT_ORIGIN_IMAGE
    std::cout << "Origin image:" << std::endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            auto p = src.at<cv::Vec3b>(i, j);
            std::cout << "(" << (int)p[0] << "," << (int)p[1] << ","
                      << (int)p[2] << ") ";
        }
        std::cout << std::endl;
    }
#endif
    // Assume filter=3 represents bicubic (confirm based on your implementation)
    int filter = 3;

    // Align with PIL to process the entire image
    cv::Rect2f box(0.f, 0.f, width, height);


    cv::Mat resized =
        PillowResize::resize(src, cv::Size(new_width, new_height), filter, box);

    std::cout << "\nResized image:" << std::endl;
    for (int i = 0; i < new_height; ++i) {
        for (int j = 0; j < new_width; ++j) {
            auto p = resized.at<cv::Vec3b>(i, j);
            std::cout << "(" << (int)p[0] << "," << (int)p[1] << ","
                      << (int)p[2] << ") ";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
