#include "EdgeDetector.h"
#include "Convolution.h"
#include <cmath>
// Default constructor
EdgeDetector::EdgeDetector() = default;

// Destructor
EdgeDetector::~EdgeDetector() = default;

std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix &input_image) {

    int height = input_image.get_height();
    int width = input_image.get_width();

    std::vector<std::pair<int, int>> edge_pixels;

    // Allocate memory Gx
    auto** Gx = new double*[3];
    for (int i = 0; i < 3; ++i) {
        Gx[i] = new double[3];
    }
    // Allocate memory for Gy
    auto** Gy = new double*[3];
    for (int i = 0; i < 3; ++i) {
        Gy[i] = new double[3];
    }

    // Define the sobel operators
    Gx[0][0] = -1.0;
    Gx[0][1] = 0.0;
    Gx[0][2] = 1.0;
    Gx[1][0] = -2.0;
    Gx[1][1] = 0.0;
    Gx[1][2] = 2.0;
    Gx[2][0] = -1.0;
    Gx[2][1] = 0.0;
    Gx[2][2] = 1.0;

    Gy[0][0] = -1.0;
    Gy[0][1] = -2.0;
    Gy[0][2] = -1.0;
    Gy[1][0] = 0.0;
    Gy[1][1] = 0.0;
    Gy[1][2] = 0.0;
    Gy[2][0] = 1.0;
    Gy[2][1] = 2.0;
    Gy[2][2] = 1.0;

    Convolution convolutionX(Gx,3,3,1,true);
    Convolution convolutionY(Gy,3,3,1,true);

    ImageMatrix Ix = convolutionX.convolve(input_image);
    ImageMatrix Iy = convolutionY.convolve(input_image);

    double magnitude_sum = 0.0;

    // Calculate the average magnitude
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            double magnitude = sqrt(Ix.get_data(i,j) * Ix.get_data(i,j) + Iy.get_data(i,j) * Iy.get_data(i,j));
            magnitude_sum += magnitude;
        }
    }

    // Calculate the average magnitude - threshold
    double threshold = magnitude_sum / ((height - 1) * (width - 1));


    // Detect edges using the average magnitude as the threshold
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {

            double magnitude = sqrt(Ix.get_data(i,j) * Ix.get_data(i,j) + Iy.get_data(i,j) * Iy.get_data(i,j));

            if (magnitude > threshold) {
                edge_pixels.emplace_back(i, j);
            }
        }
    }
    for(int i = 0 ; i < 3 ; ++i){
        delete[] Gx[i];
        delete[] Gy[i];
    }
    delete[] Gx;
    delete[] Gy;


    return edge_pixels;
}
