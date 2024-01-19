#include "EncodeMessage.h"
#include "EdgeDetector.h"
#include <iostream>
#include <bitset>


// Default Constructor
EncodeMessage::EncodeMessage() = default;

// Destructor
EncodeMessage::~EncodeMessage() = default;

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix& img, const std::string& message, const std::vector<std::pair<int, int>>& positions) {
    ImageMatrix encodedImage = img;

    for (size_t i = 0; i < message.length(); ++i) {
        char character = message[i];
        // Convert char to ASCII
        int asciiValue = static_cast<int>(character);
        // Make it a binary segment with 7-bit chunks
        std::string binarySegment = std::bitset<7>(asciiValue - 33).to_string();

        for (int j = 0; j < 7; ++j) {
            int lsb = binarySegment[j] - '0'; // Convert the character '0' or '1' to integer 0 or 1
            int positionX = positions[i].first;
            int positionY = positions[i].second;
            double pixelValue = encodedImage.get_data(positionX, positionY);

            pixelValue = (static_cast<int>(pixelValue) & 254) | lsb;  // Clear LSB
            encodedImage.setData(positionX, positionY,pixelValue);
        }
    }

    return encodedImage;
}