#pragma once

#include <QtWidgets>
#include <bits/stdc++.h>
#include "ui_MyWindow.h"
#include "Calculation.h"

namespace Ui {
    class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyWindow(QWidget* parent = nullptr);
    ~MyWindow();
    void Submit_Button1_Clicked();
    void Submit_Button2_Clicked();
    void Exit_Button_Clicked();

private:
    Ui::MyWindowClass ui;

    QLabel* Info_Label;
    QLabel* Put_In_Label;
    QLabel* Put_Out_Label;
    QLabel* Put_Out_Labe2;

    QLineEdit* Put_In_Line_Edit;
    QLineEdit* Put_Out_Line_Edit1;
    QLineEdit* Put_Out_Line_Edit2;
    
    QPushButton* Submit_Button1;
    QPushButton* Submit_Button2;
    QPushButton* Exit_Button;
};