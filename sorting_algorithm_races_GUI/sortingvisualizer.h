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

    int getDelay() const;
    void setDelay(int delay);

    void setBarColor(int index, QColor color);  // Ustawia kolor konkretnego s³upka
    void resetColors();  // Resetuje kolory wszystkich s³upków do domyœlnego niebieskiego

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void updateVisualization();

signals:
    void sortingFinished(qint64 duration);

private:
    QVector<int> numbers;
    QVector<QColor> colors;  // Kolory dla ka¿dego s³upka
    QTimer* timer;
    int delay;
    void (*sortingFunction)(QVector<int>&, SortingVisualizer*);
};

#endif // SORTINGVISUALIZER_H
