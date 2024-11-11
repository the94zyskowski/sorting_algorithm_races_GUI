#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sorting_algorithm_races_GUI.h"
#include "sortingvisualizer.h"
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
    void on_startButton_clicked();                // Handles Start button clicks
    void on_resetButton_clicked();                // Handles Reset button clicks
    void on_speedSlider_valueChanged(int value);  // Adjusts delay based on slider value

private:
    Ui::sorting_algorithm_races_GUIClass ui;
    SortingVisualizer* visualizer1;
    SortingVisualizer* visualizer2;
    SortingVisualizer* visualizer3;
    bool isSorting = false;  // Tracks whether sorting is currently active

    void toggleSorting();  // Toggles between starting and pausing sorting
};
