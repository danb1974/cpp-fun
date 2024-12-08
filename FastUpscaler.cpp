#include <iostream>
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>

std::vector<uint8_t> inputImage(640 * 400, 0);
std::vector<uint8_t> outputImage(1280 * 800, 0);

uint16_t off(uint16_t row, uint16_t col) {
    return row * 640 + col;
}

void testUpscaling1(std::vector<uint8_t> &src, std::vector<uint8_t> &dst) {
    for (int16_t row = 0; row < 400; row++) {
        bool isFinalRow = row == 400 - 1;
        for (uint16_t col = 0; col < 640; col++) {
            bool isFinalCol = col == 640 - 1;

            uint8_t pixel1 = src[off(row, col)];
            uint8_t pixel2 = isFinalCol ? pixel1 : src[off(row, col + 1)];
            uint8_t pixel3 = isFinalRow ? pixel1 : src[off(row + 1, col)];
            uint8_t pixel4 = (isFinalRow || isFinalCol) ? pixel1 : src[off(row + 1, col + 1)];

            dst[off(row * 2, col * 2)] = pixel1;
            dst[off(row * 2, col * 2 + 1)] = (pixel1 + pixel2) / 2;
            dst[off(row * 2 + 1, col * 2)] = (pixel1 + pixel3) / 2;
            dst[off(row * 2 + 1, col * 2 + 1)] = (pixel1 + pixel2 + pixel3 + pixel4) / 4;
        }
    }
}

void testUpscaling2(std::vector<uint8_t> &src, std::vector<uint8_t> &dst) {
    uint8_t *srcRow1 = &src[0];
    uint8_t *srcRow2 = &src[640];
    uint8_t *dstRow1 = &dst[0];
    uint8_t *dstRow2 = &dst[1280];

    for (int16_t row = 0; row < 400; row++) {
        bool isFinalRow = (row == 400 - 1);

        for (uint16_t col = 0; col < 640; col++) {
            bool isFinalCol = (col == 640 - 1);

            uint8_t pixel1 = *srcRow1;
            uint8_t pixel2 = isFinalCol ? pixel1 : *(srcRow1 + 1);
            uint8_t pixel3 = isFinalRow ? pixel1 : *srcRow2;
            uint8_t pixel4 = (isFinalRow || isFinalCol) ? pixel1 : *(srcRow2 + 1);

            *dstRow1 = pixel1;
            *(dstRow1 + 1) = (pixel1 + pixel2) / 2;
            *dstRow2 = (pixel1 + pixel3) / 2;
            *(dstRow2 + 1) = (pixel1 + pixel2 + pixel3 + pixel4) / 4;

            srcRow1++;
            srcRow2++;
            dstRow1 += 2;
            dstRow2 += 2;
        }

        dstRow1 += 1280;
        dstRow2 += 1280;
    }
}

void testUpscaling3(std::vector<uint8_t> &src, std::vector<uint8_t> &dst) {
    uint8_t *srcRow1 = &src[0];
    uint8_t *srcRow2 = &src[640];
    uint8_t *dstRow1 = &dst[0];
    uint8_t *dstRow2 = &dst[1280];

    uint8_t pixel1;
    uint8_t pixel2;
    uint8_t pixel3;
    uint8_t pixel4;

    for (int16_t row = 0; row < 400 - 1; row++) {
        for (uint16_t col = 0; col < 640 - 1; col++) {
            pixel1 = *srcRow1++;
            pixel2 = *srcRow1;
            pixel3 = *srcRow2++;
            pixel4 = *srcRow2;

            *dstRow1++ = pixel1;
            *dstRow1++ = (pixel1 + pixel2) / 2;
            *dstRow2++ = (pixel1 + pixel3) / 2;
            *dstRow2++ = (pixel1 + pixel2 + pixel3 + pixel4) / 4;
        }

        // not last row but last col
        pixel1 = *srcRow1++;
        pixel3 = *srcRow2++;
        *dstRow1++ = pixel1;
        *dstRow1++ = pixel1;
        *dstRow2++ = (pixel1 + pixel3) / 2;
        *dstRow2++ = (pixel1 + pixel3) / 2;

        dstRow1 += 1280;
        dstRow2 += 1280;
    }

    // last row but not last col
    for (uint16_t col = 0; col < 640 - 1; col++) {
        pixel1 = *srcRow1++;
        pixel2 = *srcRow1;

        *dstRow1++ = pixel1;
        *dstRow1++ = (pixel1 + pixel2) / 2;
        *dstRow2++ = pixel1;
        *dstRow2++ = (pixel1 + pixel2) / 2;
    }

    // last row last col
    pixel1 = *srcRow1++;
    *dstRow1++ = pixel1;
    *dstRow1++ = pixel1;
    *dstRow2++ = pixel1;
    *dstRow2++ = pixel1;
}

//

auto startTime = std::chrono::high_resolution_clock::now();

void start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void stop() {
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);
    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;
}

int main() {
    std::cout << "Hello!" << std::endl;

    cv::Mat img = cv::imread("data/abbey_road_zebra_640_400.jpg", cv::IMREAD_GRAYSCALE);
    std::memcpy(inputImage.data(), img.data, inputImage.size());

    // start();
    // for (int i = 0; i < 1000; i++) {
    //     testUpscaling1(inputImage, outputImage);
    // }
    // stop();

    // start();
    // for (int i = 0; i < 1000; i++) {
    //     testUpscaling2(inputImage, outputImage);
    // }
    // stop();

    // start();
    // for (int i = 0; i < 1000; i++) {
    //     testUpscaling3(inputImage, outputImage);
    // }
    // stop();

    cv::Mat inputMat = cv::Mat(400, 640, CV_8UC1, inputImage.data());
    cv::imshow("Input Image", inputMat);

    testUpscaling2(inputImage, outputImage);
    cv::Mat outputMat2 = cv::Mat(800, 1280, CV_8UC1, outputImage.data());
    cv::imshow("Output Image 2", outputMat2);

    testUpscaling3(inputImage, outputImage);
    cv::Mat outputMat3 = cv::Mat(800, 1280, CV_8UC1, outputImage.data());
    cv::imshow("Output Image 3", outputMat3);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
