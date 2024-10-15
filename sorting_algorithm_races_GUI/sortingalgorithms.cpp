#include "sortingalgorithms.h"
#include <QThread>
#include <algorithm>  // Required for STL

void delayAndUpdate(SortingVisualizer* visualizer, int delay) {
    visualizer->updateVisualization();
    if (delay > 0) {
        QThread::msleep(delay);  // Rest only when delay > 0
    }
}

void SortingAlgorithms::quickSort(QVector<int>& numbers, SortingVisualizer* visualizer) {
    std::sort(numbers.begin(), numbers.end(), [&](int a, int b) {
        bool result = a < b;
        delayAndUpdate(visualizer, visualizer->getDelay());  // Updating UI during sorting
        return result;
        });
    visualizer->updateVisualization();  // Extra refresh after finishing
}

void SortingAlgorithms::heapSort(QVector<int>& numbers, SortingVisualizer* visualizer) {
    std::make_heap(numbers.begin(), numbers.end());
    delayAndUpdate(visualizer, visualizer->getDelay());

    std::sort_heap(numbers.begin(), numbers.end(), [&](int a, int b) {
        bool result = a < b;
        delayAndUpdate(visualizer, visualizer->getDelay());
        return result;
        });
    visualizer->updateVisualization();  // Extra refresh after finishing
}

void SortingAlgorithms::stableSort(QVector<int>& numbers, SortingVisualizer* visualizer) {
    std::stable_sort(numbers.begin(), numbers.end(), [&](int a, int b) {
        bool result = a < b;
        delayAndUpdate(visualizer, visualizer->getDelay());
        return result;
        });
    visualizer->updateVisualization();  // Extra refresh after finishing
}
