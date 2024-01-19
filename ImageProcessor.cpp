// ImageProcessor.cpp

#include "ImageProcessor.h"
#include "EdgeDetector.h"
#include <iostream>

// Default constructor
ImageProcessor::ImageProcessor() = default;

// Destructor
ImageProcessor::~ImageProcessor() = default;

std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix& img) {
    return decoder.decodeFromImage(img,EdgeDetector().detectEdges(img));
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix& img, const std::string& message) {
    return encoder.encodeMessageToImage(img, message,EdgeDetector().detectEdges(img));
}
