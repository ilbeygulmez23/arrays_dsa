#include "Convolution.h"

// Default constructor 
Convolution::Convolution() = default;

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad)
        : stride(stride_val), padding(pad) {

    kernelHeight = kh;
    kernelWidth = kw;

    // Allocate memory
    kernel = new double*[kh];
    for (int i = 0; i < kh; ++i) {
        kernel[i] = new double[kw];
        for (int j = 0; j < kw; ++j) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}


// Destructor
Convolution::~Convolution() {
    if (kernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }
}


// Copy constructor
Convolution::Convolution(const Convolution &other) {
    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;

    // Allocate memory
    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
    }

    // Deep Copy
    for (int i = 0; i < kernelHeight; ++i) {
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }

    stride = other.stride;
    padding = other.padding;
}


// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this; // Self-assignment check
    }

    // Deallocate old memory
    for (int i = 0; i < kernelHeight; ++i) {
        delete[] kernel[i];
    }
    delete[] kernel;

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;

    // Allocate memory
    kernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kernelWidth];
    }

    // Deep Copy
    for (int i = 0; i < kernelHeight; ++i) {
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = other.kernel[i][j];
        }
    }

    stride = other.stride;
    padding = other.padding;

    return *this;
}



// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int inputHeight = input_image.get_height();
    int inputWidth = input_image.get_width();

    // Calculate output height and width
    int outputHeight = ((inputHeight - kernelHeight + 2 * padding) / stride) + 1;
    int outputWidth = ((inputWidth - kernelWidth + 2 * padding) / stride) + 1;

    ImageMatrix convolvedImage(outputHeight, outputWidth);

    //Convolve
    for (int i = 0; i < outputHeight; ++i) {
        for (int j = 0; j < outputWidth; ++j) {
            double convolvedValue = 0.0;

            // Iterate the kernel
            for (int m = 0; m < kernelHeight; ++m) {
                for (int n = 0; n < kernelWidth; ++n) {
                    int inputRowIndex = i * stride + m - padding;
                    int inputColIndex = j * stride + n - padding;

                    // Validate the indexes
                    if (inputRowIndex >= 0 && inputRowIndex < inputHeight && inputColIndex >= 0 && inputColIndex < inputWidth) {
                        double inputValue = input_image.get_data(inputRowIndex, inputColIndex);
                        convolvedValue += inputValue * kernel[m][n];
                    }
                }
            }
            convolvedImage.setData(i, j,convolvedValue);
        }
    }

    return convolvedImage;
}

