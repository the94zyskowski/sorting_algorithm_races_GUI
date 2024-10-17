#include "sorting_algorithm_races_GUI.h"
#include <QRandomGenerator>
#include "sortingalgorithms.h"  // File with sorting algorithms

void create_pool(std::vector<int>& v, int size) {
    std::set<int> unique_numbers;
    int x{ 0 };
    while (v.size() < size) {
        x = rand() % size;
        if (unique_numbers.find(x) == unique_numbers.end()) {
            v.push_back(x);
            unique_numbers.insert(x);
        }
    }
}

sorting_algorithm_races_GUI::sorting_algorithm_races_GUI(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Inicjalizujemy trzy wizualizatory sortowania
    visualizer1 = new SortingVisualizer(this);
    visualizer2 = new SortingVisualizer(this);
    visualizer3 = new SortingVisualizer(this);

    // Dodajemy widgety do layoutów w UI
    ui.verticalLayout_1->addWidget(visualizer1);
    ui.verticalLayout_2->addWidget(visualizer2);
    ui.verticalLayout_3->addWidget(visualizer3);

    // £¹czymy sygna³y wizualizatorów z odpowiednimi funkcjami do aktualizacji etykiet
    connect(visualizer1, &SortingVisualizer::sortingFinished, this, [&](qint64 duration) {
        ui.labelQuickSortTime->setText("Quick Sort time: " + QLocale().toString(duration) + " ms.");
        });

    connect(visualizer2, &SortingVisualizer::sortingFinished, this, [&](qint64 duration) {
        ui.labelHeapSortTime->setText("Heap Sort time: " + QLocale().toString(duration) + " ms.");
        });

    connect(visualizer3, &SortingVisualizer::sortingFinished, this, [&](qint64 duration) {
        ui.labelStableSortTime->setText("Stable Sort time: " + QLocale().toString(duration) + " ms.");
        });


    on_resetButton_clicked();  // Generujemy losowe liczby na pocz¹tek
}

sorting_algorithm_races_GUI::~sorting_algorithm_races_GUI()
{}

void sorting_algorithm_races_GUI::on_startButton_clicked()
{
    // Starting sorting algorithms
    visualizer1->startSorting(SortingAlgorithms::quickSort);
    visualizer2->startSorting(SortingAlgorithms::heapSort);
    visualizer3->startSorting(SortingAlgorithms::stableSort);
}

void sorting_algorithm_races_GUI::on_resetButton_clicked() {
    // Resetting all three visualizers with unique numbers
    std::vector<int> numbers;
    create_pool(numbers, 100);  // Generating 100 unique numbers

    // Manually creating QVector<int> from std::vector<int>
    QVector<int> qnumbers;
    for (int num : numbers) {
        qnumbers.append(num);
    }

    // Setting numbers in each visualizer
    visualizer1->setNumbers(qnumbers);
    visualizer2->setNumbers(qnumbers);
    visualizer3->setNumbers(qnumbers);

    // Refreshing the visualization after reset
    visualizer1->updateVisualization();
    visualizer2->updateVisualization();
    visualizer3->updateVisualization();
}

void sorting_algorithm_races_GUI::on_speedSlider_valueChanged(int value)
{
    // Setting animation speed for each visualizer
    visualizer1->setDelay(1000 - value);
    visualizer2->setDelay(1000 - value);
    visualizer3->setDelay(1000 - value);
}
