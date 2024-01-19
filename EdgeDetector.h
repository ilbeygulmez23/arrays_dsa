#ifndef EDGE_DETECTOR_H
#define EDGE_DETECTOR_H

#include "ImageMatrix.h"

class EdgeDetector {
public:

    EdgeDetector();
    ~EdgeDetector();

    std::vector<std::pair<int, int>> detectEdges(const ImageMatrix &input_image);
};

#endif // EDGE_DETECTOR_H
