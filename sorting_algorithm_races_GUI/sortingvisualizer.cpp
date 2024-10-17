#include "sortingvisualizer.h"
#include <QPainter>
#include <QtConcurrent/QtConcurrent>
#include <QMetaObject>

SortingVisualizer::SortingVisualizer(QWidget* parent)
    : QWidget(parent), delay(10)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SortingVisualizer::updateVisualization);
}

void SortingVisualizer::setNumbers(const QVector<int>& numbers)
{
    this->numbers = numbers;
    update();
}

void SortingVisualizer::startSorting(void (*sortingFunction)(QVector<int>&, SortingVisualizer*)) {
    this->sortingFunction = sortingFunction;

    QtConcurrent::run([=]() {
        QElapsedTimer timer;
        timer.start();

        sortingFunction(numbers, this);

        qint64 duration = timer.elapsed();  // Czas trwania sortowania
        QMetaObject::invokeMethod(this, "updateVisualization", Qt::QueuedConnection);  // Dodatkowe odœwie¿enie po zakoñczeniu sortowania
        emit sortingFinished(duration);  // Emitujemy sygna³ z czasem po zakoñczeniu sortowania
        });
}

void SortingVisualizer::setDelay(int delay) {
    this->delay = delay;
}

// Getter for delay
int SortingVisualizer::getDelay() const {
    return delay;
}

// Function responsible for refreshing the visualization
void SortingVisualizer::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setBrush(Qt::blue);
    int barWidth = width() / numbers.size();

    for (int i = 0; i < numbers.size(); ++i) {
        int barHeight = numbers[i];
        painter.drawRect(i * barWidth, height() - barHeight, barWidth - 1, barHeight);
    }
}

// Refreshing the visualization only in the GUI thread
void SortingVisualizer::updateVisualization()
{
    // We use QMetaObject::invokeMethod to ensure that the GUI updates in the main thread
    QMetaObject::invokeMethod(this, "repaint", Qt::QueuedConnection);
    timer->start(delay);
}
