#include "MyWindow.h"

MyWindow::MyWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Info_Label = new QLabel("Put in the expression", this);
    Info_Label->setGeometry(QRect(QPoint(50, 50), QSize(200, 20)));

    Put_In_Label = new QLabel("Expression:  ", this);
    Put_In_Label->setGeometry(QRect(QPoint(50, 80), QSize(200, 20)));
        
    Put_Out_Label = new QLabel("Postfix:     ", this);
    Put_Out_Label->setGeometry(QRect(QPoint(50, 110), QSize(200, 20)));

    Put_Out_Labe2 = new QLabel("Calculation: ", this);
    Put_Out_Labe2->setGeometry(QRect(QPoint(50, 140), QSize(200, 20)));

    Put_In_Line_Edit = new QLineEdit(this);
    Put_In_Line_Edit->setGeometry(QRect(QPoint(180, 80), QSize(200, 20)));
    Put_In_Line_Edit->setMaxLength(20);

    Put_Out_Line_Edit1 = new QLineEdit(this);
    Put_Out_Line_Edit1->setGeometry(QRect(QPoint(180, 110), QSize(200, 20)));
    Put_Out_Line_Edit1->setMaxLength(20);

    Put_Out_Line_Edit2 = new QLineEdit(this);
    Put_Out_Line_Edit2->setGeometry(QRect(QPoint(180, 140), QSize(200, 20)));
    Put_Out_Line_Edit2->setMaxLength(20);     

    Submit_Button1 = new  QPushButton("Put Out Postfix And Calculate", this);
    Submit_Button1->setGeometry(QRect(QPoint(50, 200), QSize(200, 50)));
    connect(Submit_Button1, &QPushButton::clicked, this, &MyWindow::Submit_Button1_Clicked);

    Submit_Button2 = new  QPushButton("Put Out Calculate", this);
    Submit_Button2->setGeometry(QRect(QPoint(300, 200), QSize(200, 50)));
    connect(Submit_Button2, &QPushButton::clicked, this, &MyWindow::Submit_Button2_Clicked);

    Exit_Button = new QPushButton("Exit", this);
    Exit_Button->setGeometry(QRect(QPoint(550, 200), QSize(200, 50)));
    connect(Exit_Button, &QPushButton::clicked, this, &MyWindow::Exit_Button_Clicked);
}

MyWindow::~MyWindow()
{}

void MyWindow::Submit_Button1_Clicked()
{
    QString Put_In = Put_In_Line_Edit->text();
    std::string s = Put_In.toStdString();
    QString Postfix,Answer;
    if (Check_Arithmetic_Expressions(s) == 0)
    {
        Postfix = "";
        Answer = "Error Expression";
    }
    else
    {
        Postfix = QString::fromStdString(Arithmetic_Expressions_To_Postfix(s));
        Answer = QString::fromStdString(Calculation_Arithmetic_Expressions(s));
    }
    Put_Out_Line_Edit1->setText(Postfix);
    Put_Out_Line_Edit2->setText(Answer);
}

void MyWindow::Submit_Button2_Clicked()
{
    QString Put_In = Put_In_Line_Edit->text();
    std::string s = Put_In.toStdString();
    QString Answer;
    if (Check_Arithmetic_Expressions(s) == 0)
        Answer = "Error Expression";
    else Answer = QString::fromStdString(Calculation_Arithmetic_Expressions(s));
    Put_Out_Line_Edit1->clear();
    Put_Out_Line_Edit2->setText(Answer);
}

void MyWindow::Exit_Button_Clicked()
{
    this->close();
}