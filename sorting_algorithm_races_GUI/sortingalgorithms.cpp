#include "sortingalgorithms.h"
#include <QThread>
#include <algorithm>

void delayAndUpdate(SortingVisualizer* visualizer, int delay, int index) {
    visualizer->setBarColor(index, Qt::red);  // Ustawia czerwony kolor dla aktualnie sortowanego elementu
    visualizer->updateVisualization();

    if (delay > 0) {
        QThread::msleep(delay);
    }

    visualizer->setBarColor(index, Qt::blue);  // Przywraca domyœlny kolor po opóŸnieniu
}

void SortingAlgorithms::quickSort(QVector<int>& numbers, SortingVisualizer* visualizer) {
    for (int i = 0; i < numbers.size() - 1; ++i) {
        for (int j = 0; j < numbers.size() - i - 1; ++j) {
            delayAndUpdate(visualizer, visualizer->getDelay(), j);
            if (numbers[j] > numbers[j + 1]) {
                std::swap(numbers[j], numbers[j + 1]);
                delayAndUpdate(visualizer, visualizer->getDelay(), j);
            }
        }
    }
    visualizer->updateVisualization();
}

void SortingAlgorithms::heapSort(QVector<int>& numbers, SortingVisualizer* visualizer) {
    std::make_heap(numbers.begin(), numbers.end());
    for (int i = numbers.size() - 1; i > 0; --i) {
        std::swap(numbers[0], numbers[i]);
        delayAndUpdate(visualizer, visualizer->getDelay(), 0);
        std::make_heap(numbers.begin(), numbers.begin() + i);
    }
    visualizer->updateVisualization();
}

void SortingAlgorithms::stableSort(QVector<int>& numbers, SortingVisualizer* visualizer) {
    // Niestandardowa implementacja stable sort przez wstawianie
    for (int i = 1; i < numbers.size(); ++i) {
        int key = numbers[i];
        int j = i - 1;

        // Poruszamy siê wstecz, aby znaleŸæ miejsce wstawienia elementu kluczowego
        while (j >= 0 && numbers[j] > key) {
            numbers[j + 1] = numbers[j];
            delayAndUpdate(visualizer, visualizer->getDelay(), j);  // Podœwietlanie elementów przesuwanych
            j--;
        }
        numbers[j + 1] = key;
        delayAndUpdate(visualizer, visualizer->getDelay(), j + 1);  // Podœwietlenie miejsca wstawienia
    }
    visualizer->updateVisualization();
}
