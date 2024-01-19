#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    // Declare and allocate memory for blurring kernel
    kernelHeight = 3;
    kernelWidth = 3;
    blurringKernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        blurringKernel[i] = new double[kernelWidth];
    }
    // Box blur
    for(int i = 0; i < kernelHeight ; ++i)
        for(int j = 0 ; j < kernelWidth ; ++j)
            blurringKernel[i][j] = 1.0/9.0;
}

// Destructor
ImageSharpening::~ImageSharpening() {

    if (blurringKernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] blurringKernel[i];
        }
        delete[] blurringKernel;
    }
}

// Perform image sharpening
ImageMatrix ImageSharpening::sharpen(const ImageMatrix &input_image, double k) {
    // Blurring
    Convolution convolution(blurringKernel, kernelHeight, kernelWidth, 1, true);

    ImageMatrix blurred_image = convolution.convolve(input_image);

    // Sharpening using k
    ImageMatrix sharpened_image = input_image + ((input_image - blurred_image) * k);

    return sharpened_image;
}
