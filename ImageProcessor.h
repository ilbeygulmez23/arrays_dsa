#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "ImageMatrix.h"
#include "EdgeDetector.h"
#include "DecodeMessage.h"
#include "EncodeMessage.h"

// Class `ImageProcessor`: Used for decoding and encoding hidden messages in an image.
class ImageProcessor {
public:
    ImageProcessor();
    ~ImageProcessor();

    std::string decodeHiddenMessage(const ImageMatrix& img);
    ImageMatrix encodeHiddenMessage(const ImageMatrix& img, const std::string& message);

private:
    DecodeMessage decoder;
    EncodeMessage encoder;
};

#endif // IMAGE_PROCESSOR_H
