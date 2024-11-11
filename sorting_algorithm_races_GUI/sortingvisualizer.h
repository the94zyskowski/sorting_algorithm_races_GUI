#ifndef SORTINGVISUALIZER_H
#define SORTINGVISUALIZER_H

#include <QWidget>
#include <QVector>
#include <QTimer>
#include <QColor>

class SortingVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit SortingVisualizer(QWidget* parent = nullptr);
    void setNumbers(const QVector<int>& numbers);
    void startSorting(void (*sortingFunction)(QVector<int>&, SortingVisualizer*));
    void pauseSorting();       // Pauses the sorting process
    void resumeSorting(void (*sortingFunction)(QVector<int>&, SortingVisualizer*));  // Resumes the sorting process
    int getDelay() const;
    void setDelay(int delay);

    void setBarColor(int index, QColor color);
    void resetColors();

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void updateVisualization();

signals:
    void sortingFinished(qint64 duration);

private:
    QVector<int> numbers;
    QVector<QColor> colors;
    QTimer* timer;
    int delay;
    bool isPaused = false;  // Tracks pause state
    void (*sortingFunction)(QVector<int>&, SortingVisualizer*);
};

#endif // SORTINGVISUALIZER_H
