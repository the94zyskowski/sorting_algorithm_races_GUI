#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sorting_algorithm_races_GUI.h"
#include "sortingvisualizer.h"  // Adding a new widget for visualization
#include <set>
#include <QLocale>

void create_pool(std::vector<int>& v, int size);

class sorting_algorithm_races_GUI : public QMainWindow
{
    Q_OBJECT

public:
    sorting_algorithm_races_GUI(QWidget* parent = nullptr);
    ~sorting_algorithm_races_GUI();

private slots:
    void on_startButton_clicked();  // Slot for Start button
    void on_resetButton_clicked();  // Slot for Reset button
    void on_speedSlider_valueChanged(int value);  // Slot for speed slider

private:
    Ui::sorting_algorithm_races_GUIClass ui;
    SortingVisualizer* visualizer1;  // Three widgets for visualization
    SortingVisualizer* visualizer2;
    SortingVisualizer* visualizer3;
};
