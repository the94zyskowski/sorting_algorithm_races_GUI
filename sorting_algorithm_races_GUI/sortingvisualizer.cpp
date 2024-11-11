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
    colors = QVector<QColor>(numbers.size(), Qt::blue);
    update();
}

void SortingVisualizer::startSorting(void (*sortingFunction)(QVector<int>&, SortingVisualizer*)) {
    this->sortingFunction = sortingFunction;
    isPaused = false;

    QtConcurrent::run([=]() {
        QElapsedTimer timer;
        timer.start();

        sortingFunction(numbers, this);

        qint64 duration = timer.elapsed();
        QMetaObject::invokeMethod(this, "updateVisualization", Qt::QueuedConnection);
        emit sortingFinished(duration);
        });
}

void SortingVisualizer::pauseSorting() {
    isPaused = true;
}

void SortingVisualizer::resumeSorting(void (*sortingFunction)(QVector<int>&, SortingVisualizer*)) {
    if (isPaused) {
        isPaused = false;
        updateVisualization();  // Resume updating
    }
    else {
        startSorting(sortingFunction);  // Start if not already running
    }
}

void SortingVisualizer::setDelay(int delay) {
    this->delay = delay;
}

int SortingVisualizer::getDelay() const {
    return delay;
}

void SortingVisualizer::setBarColor(int index, QColor color) {
    if (index >= 0 && index < colors.size()) {
        colors[index] = color;
    }
}

void SortingVisualizer::resetColors() {
    colors.fill(Qt::blue);
}

void SortingVisualizer::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    int barWidth = width() / numbers.size();

    for (int i = 0; i < numbers.size(); ++i) {
        painter.setBrush(colors[i]);
        int barHeight = numbers[i];
        painter.drawRect(i * barWidth, height() - barHeight, barWidth - 1, barHeight);
    }
}

void SortingVisualizer::updateVisualization()
{
    if (!isPaused) {
        QMetaObject::invokeMethod(this, "repaint", Qt::QueuedConnection);
        timer->start(delay);
    }
}
