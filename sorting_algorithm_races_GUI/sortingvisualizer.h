#ifndef SORTINGVISUALIZER_H
#define SORTINGVISUALIZER_H

#include <QWidget>
#include <QVector>
#include <QTimer>

class SortingVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit SortingVisualizer(QWidget* parent = nullptr);
    void setNumbers(const QVector<int>& numbers);
    void startSorting(void (*sortingFunction)(QVector<int>&, SortingVisualizer*));

    // Getter and setter for delay
    int getDelay() const;        // Getter
    void setDelay(int delay);    // Setter

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void updateVisualization();

private:
    QVector<int> numbers;
    QTimer* timer;
    int delay;  // We can control it with getter and setter
    void (*sortingFunction)(QVector<int>&, SortingVisualizer*);
};

#endif // SORTINGVISUALIZER_H
