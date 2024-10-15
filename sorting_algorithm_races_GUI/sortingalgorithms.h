#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include <QVector>
#include "sortingvisualizer.h"

namespace SortingAlgorithms {
    void quickSort(QVector<int>& numbers, SortingVisualizer* visualizer);
    void heapSort(QVector<int>& numbers, SortingVisualizer* visualizer);
    void stableSort(QVector<int>& numbers, SortingVisualizer* visualizer);
}

#endif // SORTINGALGORITHMS_H
