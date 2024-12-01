#include <iostream>
#include <vector>

std::vector<uint8_t> inputImage(640 * 400);
std::vector<uint8_t> outputImage(640 * 400);
std::vector<uint8_t> outputImageBig(1280 * 800);

uint16_t off(uint16_t row, uint16_t col) {
    return row * 640 + col;
}

void testFunction1(__restrict std::vector<uint8_t> &src, __restrict std::vector<uint8_t> &dst) {
    for (uint16_t row = 0; row < 480; row++) {
        for (uint16_t col = 0; col < 640; col++) {
            dst[off(row, col)] = 256 - src[off(row, col)];
        }
    }
}

void testFunction2(__restrict std::vector<uint8_t> &src, __restrict std::vector<uint8_t> &dst) {
    uint8_t *srcPtr = &src[0];
    uint8_t *dstPtr = &dst[0];
    for (uint16_t row = 0; row < 480; row++) {
        for (uint16_t col = 0; col < 640; col++) {
            *dstPtr = 256 - *srcPtr;
            srcPtr++;
            dstPtr++;
        }
    }
}

void testUpscaling1(__restrict std::vector<uint8_t> &src, __restrict std::vector<uint8_t> &dst) {
    for (int16_t row = 0; row < 480; row++) {
        bool isFinalRow = row == 480 - 1;
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

void testUpscaling2(__restrict std::vector<uint8_t> &src, __restrict std::vector<uint8_t> &dst) {
    uint8_t *srcRow1 = &src[0];
    uint8_t *srcRow2 = &src[640];
    uint8_t *dstRow1 = &dst[0];
    uint8_t *dstRow2 = &dst[1280];

    for (int16_t row = 0; row < 480; row++) {
        bool isFinalRow = row == 480 - 1;
        for (uint16_t col = 0; col < 640; col++) {
            bool isFinalCol = col == 640 - 1;

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

//

std::__1::chrono::steady_clock::time_point startTime;

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

    // start();
    // for (int i = 0; i < 1000; i++) {
    //     testFunction1(inputImage, outputImage);
    // }
    // stop();

    // start();
    // for (int i = 0; i < 1000; i++) {
    //     testFunction2(inputImage, outputImage);
    // }
    // stop();

    start();
    for (int i = 0; i < 1000; i++) {
        testUpscaling1(inputImage, outputImageBig);
    }
    stop();

    start();
    for (int i = 0; i < 1000; i++) {
        testUpscaling2(inputImage, outputImageBig);
    }
    stop();

    return 0;
}
