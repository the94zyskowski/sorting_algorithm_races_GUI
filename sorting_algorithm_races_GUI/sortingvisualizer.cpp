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
    colors = QVector<QColor>(numbers.size(), Qt::blue);  // Inicjalizacja kolorów na niebiesko
    update();
}

void SortingVisualizer::startSorting(void (*sortingFunction)(QVector<int>&, SortingVisualizer*)) {
    this->sortingFunction = sortingFunction;

    QtConcurrent::run([=]() {
        QElapsedTimer timer;
        timer.start();

        sortingFunction(numbers, this);

        qint64 duration = timer.elapsed();
        QMetaObject::invokeMethod(this, "updateVisualization", Qt::QueuedConnection);
        emit sortingFinished(duration);
        });
}

void SortingVisualizer::setDelay(int delay) {
    this->delay = delay;
}

int SortingVisualizer::getDelay() const {
    return delay;
}

// Ustawia kolor dla konkretnego s³upka
void SortingVisualizer::setBarColor(int index, QColor color) {
    if (index >= 0 && index < colors.size()) {
        colors[index] = color;
    }
}

// Resetuje wszystkie kolory do domyœlnego niebieskiego
void SortingVisualizer::resetColors() {
    colors.fill(Qt::blue);
}

// Rysowanie s³upków z uwzglêdnieniem ich kolorów
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
    QMetaObject::invokeMethod(this, "repaint", Qt::QueuedConnection);
    timer->start(delay);
}
