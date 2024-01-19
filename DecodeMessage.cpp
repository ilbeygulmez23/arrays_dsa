// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>

// Default constructor
DecodeMessage::DecodeMessage() = default;

// Destructor
DecodeMessage::~DecodeMessage() = default;

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binaryMessage;

    for (const auto& pixel : edgePixels) {
        int i = pixel.first;
        int j = pixel.second;
        double pixelValue = image.get_data(i, j);
        int lsb = static_cast<int>(pixelValue) & 1;
        // Add the binary value to message
        binaryMessage.push_back('0' + lsb);
    }

    std::string asciiMessage;
    // Get 7-bit text each iteration
    for (size_t i = 0; i < binaryMessage.length(); i += 7) {
        std::string segment = binaryMessage.substr(i, 7);
        int decimalValue = 0;
        // Double the binary value each iteration
        for (char j : segment) {
            decimalValue = (decimalValue << 1) + (j - '0');
        }
        // Adjust the boundaries
        if (decimalValue <= 32) {
            decimalValue += 33;
        } else if (decimalValue >= 127) {
            decimalValue = 126;
        }
        // Convert ASCII to char
        asciiMessage += static_cast<char>(decimalValue);
    }

    return asciiMessage;
}


