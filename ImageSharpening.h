#ifndef IMAGESHARPENING_H
#define IMAGESHARPENING_H

#include "ImageMatrix.h"
#include "Convolution.h"

class ImageSharpening {
public:
    ImageSharpening();
    ~ImageSharpening();

    ImageMatrix sharpen(const ImageMatrix &input_image, double k);

private:
    double** blurringKernel;
    int kernelHeight;
    int kernelWidth;
};

#endif // IMAGESHARPENING_H
