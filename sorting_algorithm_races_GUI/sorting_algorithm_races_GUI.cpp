#include "sorting_algorithm_races_GUI.h"
#include <QRandomGenerator>
#include "sortingalgorithms.h"

// Generates a set of unique random numbers to be used in sorting visualizations
void create_pool(std::vector<int>& v, int size) {
    std::set<int> unique_numbers;
    while (v.size() < size) {
        int x = rand() % size;
        if (unique_numbers.insert(x).second) {
            v.push_back(x);
        }
    }
}

sorting_algorithm_races_GUI::sorting_algorithm_races_GUI(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Initialize visualizer widgets
    visualizer1 = new SortingVisualizer(this);
    visualizer2 = new SortingVisualizer(this);
    visualizer3 = new SortingVisualizer(this);

    // Add visualizer widgets to UI layouts
    ui.verticalLayout_1->addWidget(visualizer1);
    ui.verticalLayout_2->addWidget(visualizer2);
    ui.verticalLayout_3->addWidget(visualizer3);

    // Connect sorting completion signals to label updates
    connect(visualizer1, &SortingVisualizer::sortingFinished, this, [&](qint64 duration) {
        ui.labelQuickSortTime->setText("Quick Sort time: " + QLocale().toString(duration) + " ms.");
        });

    connect(visualizer2, &SortingVisualizer::sortingFinished, this, [&](qint64 duration) {
        ui.labelHeapSortTime->setText("Heap Sort time: " + QLocale().toString(duration) + " ms.");
        });

    connect(visualizer3, &SortingVisualizer::sortingFinished, this, [&](qint64 duration) {
        ui.labelStableSortTime->setText("Stable Sort time: " + QLocale().toString(duration) + " ms.");
        });

    // Set default delay and synchronize slider with delay value
    int defaultDelay = 50;
    ui.speedSlider->setValue(defaultDelay);
    visualizer1->setDelay(defaultDelay);
    visualizer2->setDelay(defaultDelay);
    visualizer3->setDelay(defaultDelay);

    on_resetButton_clicked();
}

sorting_algorithm_races_GUI::~sorting_algorithm_races_GUI()
{}

void sorting_algorithm_races_GUI::toggleSorting() {
    // Toggle between starting and pausing sorting on each visualizer
    if (isSorting) {
        visualizer1->pauseSorting();
        visualizer2->pauseSorting();
        visualizer3->pauseSorting();
        ui.startButton->setText("Start");
    }
    else {
        visualizer1->resumeSorting(SortingAlgorithms::quickSort);
        visualizer2->resumeSorting(SortingAlgorithms::heapSort);
        visualizer3->resumeSorting(SortingAlgorithms::stableSort);
        ui.startButton->setText("Stop");
    }
    isSorting = !isSorting;
}

void sorting_algorithm_races_GUI::on_startButton_clicked()
{
    toggleSorting();
}

void sorting_algorithm_races_GUI::on_resetButton_clicked() {
    // Create a new set of random numbers for each reset
    std::vector<int> numbers;
    create_pool(numbers, 100);

    QVector<int> qnumbers;
    for (int num : numbers) {
        qnumbers.append(num);
    }

    // Reset each visualizer with the new number set
    visualizer1->setNumbers(qnumbers);
    visualizer2->setNumbers(qnumbers);
    visualizer3->setNumbers(qnumbers);

    visualizer1->resetColors();
    visualizer2->resetColors();
    visualizer3->resetColors();

    // Ensure UI reflects reset state
    visualizer1->updateVisualization();
    visualizer2->updateVisualization();
    visualizer3->updateVisualization();

    isSorting = false;
    ui.startButton->setText("Start");
}

void sorting_algorithm_races_GUI::on_speedSlider_valueChanged(int value)
{
    int delay = 100 - value;
    visualizer1->setDelay(delay);
    visualizer2->setDelay(delay);
    visualizer3->setDelay(delay);
}
